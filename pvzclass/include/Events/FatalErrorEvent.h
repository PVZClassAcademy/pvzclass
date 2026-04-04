#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 弹出Fatal Error窗口前
	/// @param EXCEPTION_POINTERS
	/// @note 可以打印一些额外的调试信息，头文件提供了一个打印调用栈的示例
	class FatalErrorEvent : public DLLEventTemplate<0x5A4760, 7, MEM_ESP_ADD(0x24)>
	{
	public:
		FatalErrorEvent(int address) : DLLEventTemplate() { Init(address); };
		FatalErrorEvent(const char* name) : DLLEventTemplate() { Init(name); };
		FatalErrorEvent() : FatalErrorEvent("onFatalError") {};
	};
}

#ifdef _X86_

#include <DbgHelp.h>
#define MAX_NAME_LEN 1024

static bool ResolveInvoke(DWORD rawAddr, DWORD* newAddr)
{
	if (!newAddr) return false;
	if (PVZ::Memory::ReadMemory<BYTE>(rawAddr - 5) != 0xE8) return false;
	if (PVZ::Memory::ReadMemory<DWORD>(rawAddr - 4) != 2) return false;
	if (PVZ::Memory::ReadMemory<BYTE>(rawAddr) != 0xEB) return false;
	if (PVZ::Memory::ReadMemory<BYTE>(rawAddr + 1) != 0x06) return false;
	if (PVZ::Memory::ReadMemory<BYTE>(rawAddr + 2) != 0x68) return false;
	*newAddr = PVZ::Memory::ReadMemory<DWORD>(rawAddr + 3);
	if (PVZ::Memory::ReadMemory<BYTE>(rawAddr + 7) != 0xC3) return false;
	return true;
}

static void WriteStackTrace(EXCEPTION_POINTERS* lpEP, const char* outputFilename)
{
	FILE* fp = nullptr;
	fopen_s(&fp, outputFilename, "a");
	if (!fp) return;

	HANDLE process = GetCurrentProcess();
	HANDLE thread = GetCurrentThread();
	SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES);
	if (!SymInitialize(process, nullptr, true))
	{
		fprintf_s(fp, "SymInitialize failed\n");
		fclose(fp);
		return;
	}

	CONTEXT ctx = *lpEP->ContextRecord;
	STACKFRAME64 frame{};
	DWORD machine = IMAGE_FILE_MACHINE_I386;
	frame.AddrPC.Offset = ctx.Eip;
	frame.AddrPC.Mode = AddrModeFlat;
	frame.AddrFrame.Offset = ctx.Ebp;
	frame.AddrFrame.Mode = AddrModeFlat;
	frame.AddrStack.Offset = ctx.Esp;
	frame.AddrStack.Mode = AddrModeFlat;

	fputs("=== Call Stack ===\n", fp);
	char linebuf[2048] = {};
	uint8_t symbuf[sizeof(SYMBOL_INFO) + MAX_NAME_LEN] = {};
	SYMBOL_INFO* sym = reinterpret_cast<SYMBOL_INFO*>(symbuf);
	sym->SizeOfStruct = sizeof(SYMBOL_INFO);
	sym->MaxNameLen = MAX_NAME_LEN;
	IMAGEHLP_LINE64 line{};
	line.SizeOfStruct = sizeof(line);

	for (int i = 0; i < 64; i++)
	{
		bool result = StackWalk64(machine, process, thread, &frame, &ctx, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr);
		DWORD64 addr = frame.AddrPC.Offset;
		if (!result || addr == 0) break;
		DWORD64 logicAddr = addr;
		DWORD newAddr = 0;
		bool resolveResult = ResolveInvoke((DWORD)addr, &newAddr);
		if (resolveResult) logicAddr = newAddr;

		IMAGEHLP_MODULE64 mod{};
		mod.SizeOfStruct = sizeof(mod);
		const char* modName = "unknown";
		if (SymGetModuleInfo64(process, logicAddr, &mod) && mod.ModuleName[0])
			modName = mod.ModuleName;

		DWORD64 dispSym = 0;
		DWORD64 symBase = 0;
		const char* funcName = "???";
		if (SymFromAddr(process, logicAddr, &dispSym, sym))
		{
			funcName = sym->Name;
			symBase = sym->Address;
		}

		DWORD dispLine = 0;
		if (SymGetLineFromAddr64(process, logicAddr, &dispLine, &line))
		{
			if (resolveResult)
				sprintf_s(linebuf, sizeof(linebuf), "#%02d %s!%s+0x%llX  %s:%lu(+%lu)  [target=0x%08llX, invoke=0x%08llX]\n",
					i, modName, funcName, dispSym, line.FileName, line.LineNumber, dispLine, logicAddr, addr);
			else
				sprintf_s(linebuf, sizeof(linebuf), "#%02d %s!%s+0x%llX  %s:%lu(+%lu)  [0x%08llX]\n",
					i, modName, funcName, dispSym, line.FileName, line.LineNumber, dispLine, logicAddr);
		}
		else if (symBase != 0)
		{
			if (resolveResult)
				sprintf_s(linebuf, sizeof(linebuf), "#%02d %s!%s+0x%llX  [target=0x%08llX, invoke=0x%08llX]\n",
					i, modName, funcName, dispSym, logicAddr, addr);
			else
				sprintf_s(linebuf, sizeof(linebuf), "#%02d %s!%s+0x%llX  [0x%08llX]\n",
					i, modName, funcName, dispSym, logicAddr);
		}
		else
		{
			if (resolveResult)
				sprintf_s(linebuf, sizeof(linebuf), "#%02d %s!%s  [target=0x%08llX, invoke=0x%08llX]\n",
					i, modName, funcName, logicAddr, addr);
			else
				sprintf_s(linebuf, sizeof(linebuf), "#%02d %s!%s  [0x%08llX]\n",
					i, modName, funcName, logicAddr);
		}

		fputs(linebuf, fp);
	}

	SymCleanup(process);
	fclose(fp);
}

#endif // _X86_