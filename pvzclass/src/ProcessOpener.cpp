#include "ProcessOpener.h"
#include <TLHELP32.H>
LPCWSTR ProcessOpener::ProcessName = TEXT("PlantsVsZombies.exe");
LPCWSTR ProcessOpener::WindowTitle = TEXT("Plants vs. Zombies");
LPCWSTR ProcessOpener::Directory = TEXT(".");
LPCWSTR ProcessOpener::ExecuteableName = TEXT("PlantsVsZombies.exe");

DWORD ProcessOpener::OpenByProcessName(LPCWSTR processName)
{
	DWORD pid = NULL;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)return NULL;
	BOOL ret = Process32First(hProcessSnap, &pe32);
	while (ret)
	{
		if (!lstrcmp(pe32.szExeFile, processName))pid = pe32.th32ProcessID;
		ret = Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
	return pid;
}

DWORD ProcessOpener::OpenByWindowTitle(LPCWSTR processName)
{
	HWND hwnd = FindWindow(NULL, processName);
	DWORD pid = NULL;
	GetWindowThreadProcessId(hwnd, &pid);
	return pid;
}

WCHAR FilePathBuf[MAX_PATH + 1];
DWORD ProcessOpener::OpenByFilePath(LPCWSTR directory, LPCWSTR executeableName)
{
	STARTUPINFO startupInfo = { 0 };
	PROCESS_INFORMATION processInformation = { 0 };

	wcscpy_s(FilePathBuf, MAX_PATH, directory);
	wcscat_s(FilePathBuf, MAX_PATH, L"\\");
	wcscat_s(FilePathBuf, MAX_PATH, executeableName);

	BOOL ret = CreateProcess(FilePathBuf, NULL, NULL, NULL, FALSE, NULL, NULL, directory, &startupInfo, &processInformation);
	if (ret)
	{
		CloseHandle(processInformation.hProcess);
		CloseHandle(processInformation.hThread);
		return processInformation.dwProcessId;
	}
	return NULL;
}

DWORD ProcessOpener::Open()
{
	DWORD pid = OpenByProcessName(ProcessName);
	if (pid)return pid;
	pid = OpenByWindowTitle(WindowTitle);
	if (pid)return pid;
	return OpenByFilePath(Directory, ExecuteableName);
}
