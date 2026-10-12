#include "Classes/TooltipWidget.hpp"

void PVZ::TooltipWidget::CalculateSize()
{
	PVZ::Memory::Execute(AsmBuilder()
		.push_imm32(this->GetBaseAddress())
		.invoke(0x51A710)
		.ret()
	);
}

void PVZ::TooltipWidget::SetLabel(PVZ::PVZString str)
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EDX, str.GetBaseAddress())
		.mov_reg_imm(REG_ESI, this->GetBaseAddress())
		.invoke(0x51A8D0)
		.ret()
	);
}
