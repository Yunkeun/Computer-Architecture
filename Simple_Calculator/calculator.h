#ifndef CALCULATOR_H
# define CALCULATOR_H

#include <stdio.h>
#include <stdlib.h>

int		addition(int val1, int val2);
int		subtraction(int val1, int val2);
int		multiplication(int val1, int val2);
int		division(int val1, int val2);
int		C(int val1, int val2);
int		M(int operand1);
int		J(int operand1);
int		B(int operand1, int condition1, int current);
int		H(void);

int		is_valid_file(FILE* fp);
int		validation_check(char* str);
int		Executing_J_or_B(char* str, int i, int* R, int size);
void		Executing_Else(char* str, int* R);

int		is_operator(char c);
int		is_hex(char* str);
int		is_instruction(char* str);

#endif
