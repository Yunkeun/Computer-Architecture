#include "calculator.h"

int		is_valid_file(FILE* fp)
{
	if (fp == NULL)
	{
		printf("There is no input.txt. Thank you.\n");
		return (0);
	}
	return (1);
}

int		is_operator(char c)
{
	if (c == 'J' || c == 'B')
		return (1);
	if (c == 'M')
		return (2); 
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == 'C')
		return (3);
	if (c == 'H')
		return (4);
	return (0);
}

int		is_hex(char* str)
{
	if (*(str++) == '0' && *str == 'x' && ((*(++str) >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F')))
		return (1);
	return (0);
}

int		is_instruction(char* str)
{
	if (*str++ == 'R' && (*str >= '0' && *str <= '9') && ((*(++str) == ' ') || *str == '\n' || *str == '\0'))
		return (1);
	return (0);
}

/*
is_operand()'s return value description
error	:	return (0)
J, B	:	return (1)
M	:	return (2)
+,-,*,/,C:	return (3)
H	:	return (4)
*/
int		is_operand(char* str)
{
	int flag;
	char* tmp;

	tmp = str;
	flag = 0;
	if (str[0] == 'J' || str[0] == 'B')
	{
		while (*str)
		{
			if (*str++ == ' ' && is_hex(str) && !is_instruction(str))
			{
				flag++;
				str = &str[1];
			}
			if (flag == 1 && (is_hex(str) || is_instruction(str)))
				return (0);
		}
	}
	if (flag == 1)
		return (1);
	str = &tmp[0];
	flag = 0;
	if (str[0] == 'M')
	{
		while (*str)
		{
			if (*str++ == ' ' && is_instruction(str) && !is_hex(str))
				flag++;
			if (flag == 1 && *str == ' ')
			{
				str = &str[1];
				if (is_hex(str) || is_instruction(str))
					flag++;
			}
		}
	}
	if (flag == 2)
		return (2);
	str = &tmp[0];
	flag = 0;
	while (*str)
		if (*str++ == ' ' && (is_hex(str) || is_instruction(str)))
			flag++;
	if (flag == 2)
		return (3);
	str = &tmp[0];
	if (is_operator(str[0]) == 4 && (str[1] == '\0' || str[1] == '\n'))
		return (4);
	return (0);
}

/*
validation_check()'s return value description
error	:	return (0)
J,B	:	return (1)
M	:	return (2)
+,-,*,/,C:	return (3)
H	:	return (4)
*/
int		validation_check(char* str)
{
	if (is_operator(str[0]) == 1 && is_operand(str) == 1)
		return (1);
	else if (is_operator(str[0]) == 2 && is_operand(str) == 2)
		return (2);
	else if (is_operator(str[0]) == 3 && is_operand(str) == 3)
		return (3);
	else if (is_operator(str[0]) == 4 && is_operand(str) == 4)
		return (4);
	return (0);
}
