#include <stdio.h>

int		addition(int operand1, int operand2)
{
	printf("Decoding '+'...\n");
	return (operand1 + operand2);
}

int		subtraction(int operand1, int operand2)
{
	printf("Decoding '-'...\n");
	return (operand1 - operand2);
}

int		multiplication(int operand1, int operand2)
{
	printf("Decoding '*'...\n");
	return (operand1 * operand2);
}

int		division(int operand1, int operand2)
{
	printf("Decoding '/'...\n");
	return (operand1 / operand2);
}

int		C(int operand1, int operand2)
{
	printf("Decoding 'C'...\n");
	if (operand1 >= operand2)
		return (0);
	else
		return (1);
}

int		M(int operand1)
{
	printf("Decoding 'M'...\n");
	return (operand1);
}

int		J(int operand1)
{
	printf("Decoding 'J'...\n");
	return (operand1);
}

int		B(int operand1, int condition1, int current)
{
	printf("Decoding 'B'...\n");
	if (condition1 == 1)
		return (operand1);
	return (current);
}

int		H(void)
{
	printf("Decoding 'H'...\n");
	return (-1);
}
