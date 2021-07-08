#include "pipeline.h"

void	write_back(IDEX_latch* idex_output, EXMEM_latch* exmem_output, MEMWB_latch* memwb_input, MEMWB_latch* memwb_output, REG* R)
{
	int rst;
	int Write_Reg;
	int idex_Write_Reg;
	int exmem_Write_Reg;
	int memwb_Write_Reg;

	rst = MUX_MemtoReg(memwb_input->control_signal.MemtoReg, memwb_input->MEM_value, memwb_input->ALU_rst);
	Write_Reg = MUX_REGDst(memwb_input->control_signal.RegDst, memwb_input->debug.rd, memwb_input->debug.rt);
	idex_Write_Reg = MUX_REGDst(idex_output->control_signal.RegDst, idex_output->debug.rd, idex_output->debug.rt);
	exmem_Write_Reg = MUX_REGDst(exmem_output->control_signal.RegDst, exmem_output->debug.rd, exmem_output->debug.rt);
	memwb_Write_Reg = MUX_REGDst(memwb_output->control_signal.RegDst, memwb_output->debug.rd, memwb_output->debug.rt);

	if (memwb_input->control_signal.RegWrite)
	{
		(&R[Write_Reg])->value = rst;

		// 이전의 명령어에서 RegWrite 면서 그때의 쓰기 레지스터와 현재의 쓰기 레지스터가 같지 않다면 invalid = 0
		if (!((idex_output->control_signal.RegWrite && (Write_Reg == idex_Write_Reg))
			|| (exmem_output->control_signal.RegWrite && (Write_Reg == exmem_Write_Reg))
			|| (memwb_output->control_signal.RegWrite && (Write_Reg == memwb_Write_Reg))))
		{
			(&R[Write_Reg])->invalid = 0;
		}
		printf("[WB]\tR[%d] = 0x%x\n", Write_Reg, rst);
	}
	else
		printf("[WB]\tNOT ACCESS TO WB\n");
}
