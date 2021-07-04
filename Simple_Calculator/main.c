#include "calculator.h"

/*
This is a calculator that contatins not only basic four rule calculations(+, -, *, /), but also register operation(M, C, J, B, H).
*/

char	**save_arr(char* str, FILE *fp, int size)
{
	int i;
	int j;
	int k;
	char** arr;

	i = 0;
	// get size (i) for malloc row of arr
	while (fgets(str, size, fp))
		i++;
	if (!(arr = (char**)malloc(sizeof(char*) * (i + 1))))
		return (0);
	// fp to 0
	fseek(fp, 0, SEEK_SET);
	i = 0;
	while (fgets(str, size, fp))
	{
		j = 0;
		k = 0;
		i++;
		// get size (j) for malloc each col of arr
		while (str[j])
			j++;
		if (!(arr[i - 1] = (char*)malloc(sizeof(char) * (j + 1))))
			return (0);
		// save str to col of arr
		while (str[k])
		{
			arr[i - 1][k] = str[k];
			k++;
		}
		arr[i - 1][k] = '\0';
	}
	arr[i] = NULL;
	return (arr);
}

int		main(void)
{
	int size;
	FILE* fp = fopen("input.txt", "r");
	char** save_txt;
	char* str_txt;
	int i;
	int R[10] = { 0 };

	i = 0;
	if (!is_valid_file(fp))
		return (0);
	else
	{
		printf("Fetching...\n");
		printf("=========================================\n");
	}
	fseek(fp, 0, SEEK_END);
	// size == input.txt's size, if size == 0, input.txt is empty file.
	size = ftell(fp);
	if (size == 0)
	{
		printf("Stop : Invalid Input!\n");
		return (0);
	}
	if (!(str_txt = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	fseek(fp, 0, SEEK_SET);
	// after this, save_txt has all of input.txt
	save_txt = save_arr(str_txt, fp, size);
	// error check about input.txt
	while (save_txt[i])
	{
		if (!validation_check(save_txt[i]))
		{
			printf("Stop : Invalid Input!\n");
			return (0);
		}
		i++;
	}
	i = 0;
	// execute each line
	while (save_txt[i])
	{
		printf("%dth line\n", i + 1);
		printf("Original Source: %s\n", save_txt[i]);
		if (save_txt[i][0] == 'J' || save_txt[i][0] == 'B')
		{
			i = Executing_J_or_B(save_txt[i], i, R, size) - 1;
			if (i == -2)
				return (0);
			printf("=========================================\n");
			continue; // continue == JUMP to returned (i - 1) index
		}
		else if (save_txt[i][0] == 'H')
		{
			Executing_Else(save_txt[i], R);
			printf("=========================================\n");
			break ;
		}
		else
		{
			Executing_Else(save_txt[i], R);
			printf("=========================================\n");
		}
		i++;
	}
	printf("SUCCESS!\n");
	i = 0;
	// free malloc
	while (save_txt[i])
	{
		free(save_txt[i]);
		i++;
	}
	free(save_txt);
	fclose(fp);
	return (0);
}
