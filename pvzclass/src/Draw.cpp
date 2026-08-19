#include "Draw.h"
#include <iostream>

BYTE __asm__ToString[]
{
	PUSHDWORD(0),
	MOV_ECX(0),
	INVOKE(0x404450),
	RET
};

char* Draw::ToChar(PVZ::PVZString str)
{
	auto str_address = str.GetBaseAddress();
	int size = PVZ::Memory::ReadMemory<int>(str_address + 0x18);
	DWORD address = 0;
	if (size < 16) address = str_address + 4;
	else address = PVZ::Memory::ReadMemory<DWORD>(str_address + 4);
	int len = PVZ::Memory::ReadMemory<int>(str_address + 0x14);
	char* result = new char[len + 1];
	PVZ::Memory::ReadArray<char>(address, result, len);
	result[len] = 0;
	return result;
}

BYTE __asm__StringWidth[]
{
	PUSHDWORD(0),
	MOV_ECX(0),
	INVOKE(0x58DF70),
	RET
};

void Draw::StringWidth(PVZ::PVZString str, DWORD imageFontAddress)
{
	SETARG(__asm__StringWidth, 1) = str.GetBaseAddress();
	SETARG(__asm__StringWidth, 6) = imageFontAddress;
	PVZ::Memory::Execute(STRING(__asm__StringWidth));
}

BYTE __asm__GetSharedImage[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	MOV_ECX_PTR_ADDR(0x6A9EC0),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0x10C),
	CALL_EUX(2),
	RET
};

Draw::PSharedImageRef Draw::GetSharedImage(DWORD isnewAddress, PVZ::PVZString variant, PVZ::PVZString filename)
{
	SETARG(__asm__GetSharedImage, 1) = isnewAddress;
	SETARG(__asm__GetSharedImage, 6) = variant.GetBaseAddress();
	SETARG(__asm__GetSharedImage, 11) = filename.GetBaseAddress();
	PSharedImageRef imageRef = PVZ::Memory::AllocMemoryUnsafe(0, 4);
	SETARG(__asm__GetSharedImage, 16) = imageRef;
	PVZ::Memory::Execute(STRING(__asm__GetSharedImage));
	return imageRef;
}

BYTE __asm__SharedImageRefToImage[]
{
	MOV_ECX(0),
	INVOKE(0x59A980),
	MOV_PTR_ADDR_EAX(0),
	RET
};

Draw::PImage Draw::SharedImageRefToImage(PSharedImageRef imageRef)
{
	SETARG(__asm__SharedImageRefToImage, 1) = imageRef;
	SETARG(__asm__SharedImageRefToImage, 19) = PVZ::Memory::Variable;
	return PVZ::Memory::Execute(STRING(__asm__SharedImageRefToImage));
}

BYTE __asm__FreeImage[]
{
	MOV_ESI(0),
	INVOKE(0x59A8C0),
	RET
};

void Draw::FreeImage(PSharedImageRef imageRef)
{
	SETARG(__asm__FreeImage, 1) = imageRef;
	PVZ::Memory::Execute(STRING(__asm__FreeImage));
}

BYTE __asm__DrawString[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	MOV_EAX(0),
	INVOKE(0x587120),
	RET
};

void Draw::DrawString(DWORD x, DWORD y, PVZ::PVZString str, DWORD graphics)
{
	SETARG(__asm__DrawString, 1) = y;
	SETARG(__asm__DrawString, 6) = x;
	SETARG(__asm__DrawString, 11) = str.GetBaseAddress();
	SETARG(__asm__DrawString, 16) = graphics;
	PVZ::Memory::Execute(STRING(__asm__DrawString));
}

PVZ::Font PVZ::Graphics::GetFont()
{
	return PVZ::Font(PVZ::Memory::ReadMemory<uint32_t>(BaseAddress + 0x40));
}

void PVZ::Graphics::SetColor(int red, int green, int blue, int alpha)
{
	Red = red;
	Green = green;
	Blue = blue;
	Alpha = alpha;
}

void PVZ::Graphics::SetColorizeImages(bool value)
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ECX, value)
		.mov_reg_imm(REG_EAX, BaseAddress)
		.invoke(0x586D10)
		.ret()
	);
}

void PVZ::Graphics::ClipRect(int x, int y, int width, int height)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push(height)
		.push(width)
		.push(y)
		.push(x)
		.mov_reg_imm(REG_ESI, BaseAddress)
		.invoke(0x587790)
		.ret()
	);
}

void PVZ::Graphics::DrawImage(PVZ::Image image, int x, int y)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push(y)
		.push(x)
		.mov_reg_imm(REG_EBX, image.GetBaseAddress())
		.mov_reg_imm(REG_EAX, BaseAddress)
		.invoke(0x587150)
		.ret()
	);
}

void PVZ::Graphics::DrawLine(int start_x, int start_y, int end_x, int end_y)
{
	PVZ::Memory::WriteMemoryUnsafe<double>(PVZ::Memory::Variable, start_y);
	PVZ::Memory::WriteMemory<DWORD>(0x5870A4, PVZ::Memory::Variable);
	PVZ::Memory::Execute(AsmBuilder()
		.push(end_y)
		.push(end_x)
		.push(start_x)
		.push(BaseAddress)
		.invoke(0x587080)
		.ret()
	);
	PVZ::Memory::WriteMemory<DWORD>(0x5870A4, 0x65B8F8);
}

void PVZ::Graphics::DrawRect(int x, int y, int width, int height)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push(height)
		.push(width)
		.push(y)
		.push(x)
		.mov_reg_imm(REG_EAX, BaseAddress)
		.invoke(0x586DE0)
		.ret()
	);
}

void PVZ::Graphics::FillRect(int x, int y, int width, int height)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push(height)
		.push(width)
		.push(y)
		.push(x)
		.mov_reg_imm(REG_EAX, BaseAddress)
		.invoke(0x586D50)
		.ret()
	);
}

void PVZ::Graphics::DrawTextBox(DWORD edit)
{
	int rect = PVZ::Memory::AllocMemoryUnsafe(0, 16);
	PVZ::Memory::Execute(AsmBuilder()
		.push(rect)
		.mov_reg_imm(REG_ECX, edit)
		.mov_reg_mem_reg_add_imm(REG_EDX, REG_ECX, 0)
		.mov_reg_mem_reg_add_imm(REG_EDX, REG_EDX, 4)
		.call_reg(REG_EDX)
		.mov_reg_reg(REG_EBX, REG_EAX)
		.mov_reg_mem(REG_EAX, 0x6A7890)
		.push(BaseAddress)
		.invoke(0x587900)
		.ret()
	);
	PVZ::Memory::FreeMemory(rect);
}

void PVZ::Graphics::DrawString(int x, int y, PVZ::PVZString str, Font font, int just, int r, int g, int b, int a)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push(a)
		.push(b)
		.push(g)
		.push(r)
		.push(just)
		.mov_reg_imm(REG_EBX, font.GetBaseAddress())
		.push(y)
		.mov_reg_imm(REG_ECX, x)
		.mov_reg_imm(REG_EDX, str.GetBaseAddress())
		.push(BaseAddress)
		.invoke(0x511CE0)
		.add_reg_imm(REG_ESP, 0x1C)
		.ret()
	);
}

void PVZ::Graphics::TodDrawImageScaledF(PVZ::Image image, float x, float y, float scale_x, float scale_y)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push_float(scale_y)
		.push_float(scale_x)
		.push_float(y)
		.push_float(x)
		.mov_reg_imm(REG_EAX, image.GetBaseAddress())
		.mov_reg_imm(REG_ECX, this->GetBaseAddress())
		.invoke(0x512950)
		.add_reg_imm(REG_ESP, 16)
		.ret()
	);
}

void PVZ::Graphics::TodDrawImageCenterScaledF(PVZ::Image image, float x, float y, float scale_x, float scale_y)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push_float(scale_y)
		.push_float(scale_x)
		.push_float(y)
		.push_float(x)
		.mov_reg_imm(REG_EAX, image.GetBaseAddress())
		.mov_reg_imm(REG_ECX, this->GetBaseAddress())
		.invoke(0x512A10)
		.add_reg_imm(REG_ESP, 16)
		.ret()
	);
}

void PVZ::Graphics::TodDrawImageCelScaledF(PVZ::Image image, float x, float y, float scale_x, float scale_y, int row, int col)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push_float(scale_y)
		.push_float(scale_x)
		.push(row)
		.push(col)
		.push_float(y)
		.push_float(x)
		.mov_reg_imm(REG_ECX, image.GetBaseAddress())
		.mov_reg_imm(REG_EAX, BaseAddress)
		.invoke(0x512880)
		.add_reg_imm(REG_ESP, 0x18)
		.ret()
	);
}

void PVZ::Graphics::DrawZombie(ZombieType::ZombieType type, float x, float y, DWORD cache)
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ESI, type)
		.push_float(y)
		.push_float(x)
		.mov_reg_imm(REG_EDI, BaseAddress)
		.mov_reg_imm(REG_EBX, cache)
		.invoke(0x470170)
		.ret()
	);
}
