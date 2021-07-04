#include "calculator.h"

int (*g_OP_CODE_1[5])(int, int);
int (*g_OP_CODE_2[2])(int);
int (*g_OP_CODE_3[1])(int, int, int);
int (*g_OP_CODE_4[1])(void);
int g_OP_INDEX1[68];
int g_OP_INDEX2[78];
int g_OP_INDEX3[67];
int g_OP_INDEX4[73];

void	init(void)
{
	g_OP_CODE_1[0] = addition;
	g_OP_CODE_1[1] = subtraction;
	g_OP_CODE_1[2] = multiplication;
	g_OP_CODE_1[3] = division;
	g_OP_CODE_1[4] = C;
	g_OP_CODE_2[0] = M;
	g_OP_CODE_2[1] = J;
	g_OP_CODE_3[0] = B;
	g_OP_CODE_4[0] = H;

	g_OP_INDEX1['+'] = 0;
	g_OP_INDEX1['-'] = 1;
	g_OP_INDEX1['*'] = 2;
	g_OP_INDEX1['/'] = 3;
	g_OP_INDEX1['C'] = 4;
	g_OP_INDEX2['M'] = 0;
	g_OP_INDEX2['J'] = 1;
	g_OP_INDEX3['B'] = 0;
	g_OP_INDEX4['H'] = 0;
}

// str_to_num is change hex string after 0x into decimal type of int
int		str_to_num(char* str)
{
	int i;
	int rst;

	i = 2;
	rst = 0;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'F'))
	{
		if (str[i] >= 'A' && str[i] <= 'F')
			str[i] = str[i] - 'A' + '0' + 10;
		rst = rst * 16 + str[i] - '0';
		i++;
	}
	return (rst);
}

// inst_to_num : if OPCODE M, case of operand1, return number after char 'M'
// 		 else, return number contained in R[num]
int		inst_to_num(char* str, char *tmp, int *R)
{
	if (tmp[0] == 'M' && str == &tmp[2])
		return (str[1] - '0');
	return (R[str[1] - '0']);
}

int		Executing_J_or_B(char* str, int i, int* R, int size)
{
	int idx;
	int operand1;
	char* tmp;

	init();
	operand1 = 0;
	tmp = str;
	// find operand1
	while (*str++)
	{
		if (is_hex(str))
		{
			operand1 = str_to_num(str);
			break;
		}
	}
	str = &tmp[0];
	// error check: if operand1 > size, you cannot jump over input.txt
	if (operand1 > size)
	{
		printf("Stop : Segmentation Error!\n");
		return (-1);
	}
	idx = 0;
	if (str[0] == 'J')
	{
		idx = g_OP_CODE_2[g_OP_INDEX2[(int)str[0]]](operand1);
		printf("Executing...\n");
		printf("Jump to the %d Line!\n", idx);
	}
	if (str[0] == 'B')
	{
		idx = g_OP_CODE_3[g_OP_INDEX3[(int)str[0]]](operand1, R[0], i);
		printf("Executing...\n");
		if (R[0] == 1)
		{
			printf("R0 == %d, Jump to the %d Line!\n", R[0], idx);
			return (idx);
		}
		else
		{
			printf("R0 != 1, Not Jump!\n");
			return (idx + 2); // the reason of "+ 2" is that you have to jump just next index, but int the main.c, there is i-- after return this function.
		}
	}
	return (idx);
}

void	Executing_Else(char* str, int* R)
{
	int operand1;
	int operand2;
	char* tmp;

	init();
	operand1 = 0;
	operand2 = 0;
	tmp = str;
	// find operand1, operand2 = 1 means just flag for next loop
	while (*str++)
	{
		if (is_hex(str))
		{
			operand1 = str_to_num(str);
			operand2 = 1;
			break;
		}
		if (is_instruction(str))
		{
			operand1 = inst_to_num(str, tmp, R);
			operand2 = 1;
			break;
		}
	}
	// find operand2
	while (*str++)
	{
		if (operand2 != 0 && is_hex(str))
			operand2 = str_to_num(str);
		if (operand2 != 0 && is_instruction(str))
			operand2 = inst_to_num(str, tmp, R);
	}
	str = &tmp[0];
	// OPCODE M
	if (str[0] == 'M')
	{
		R[operand1] = g_OP_CODE_2[g_OP_INDEX2[(int)str[0]]](operand2);
		printf("Executing...\n");
		printf("R%d: %d\n", operand1, operand2);
	}
	// OPCODE +, -, *, /
	if (is_operator(str[0]) == 3 && str[0] != 'C')
	{
		R[0] = g_OP_CODE_1[g_OP_INDEX1[(int)str[0]]](operand1, operand2);
		printf("Executing ...\n");
		printf("R0: %d = %d %c %d\n", R[0], operand1, str[0], operand2);
		if (str[0] == '/' && operand2 == 0)
		{
			printf("Stop : Division by Zero!\n");
			return ;
		}
	}
	// OPCODE C
	if (str[0] == 'C')
	{
		R[0] = g_OP_CODE_1[g_OP_INDEX1[(int)str[0]]](operand1, operand2);
		printf("Executing...\n");
		if (R[0] >= 0)
			printf("R0: %d, Because %d >= %d\n", R[0], operand1, operand2);
		else
			printf("R0: %d, Because %d < %d\n", R[0], operand1, operand2);
	}
	// OPCODE H
	if (str[0] == 'H' && g_OP_CODE_4[g_OP_INDEX4[(int)str[0]]]() == -1)
	{
		printf("Executing...\n");
		printf("Stop : OPCODE 'H'!\n");
		return ;
	}
}
