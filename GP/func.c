#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"


static bool check_is_prefix(const char* string, const char* prefix)
{
	return strncmp(string, prefix, strlen(prefix)) == 0;
}

static bool extract_option(const char** args, int* arg_index, const char* option, bool* option_provided, const char** option_arg)
{
	assert(check_is_prefix(args[*arg_index], option));

	// Не -C aD, а -CaD решили передать. Тогда аргументы только в конце, т.е. если передадут -Ca D, будет -Сa, а D игнорируем.
	bool argument_is_suffix = true;

	if (strcmp(args[*arg_index], option) == 0)
	{
		// Если опция полностью совпадает с текущим аргументом командной строки, значит аргумент опции идёт дальше отдельно.
		argument_is_suffix = false;
	}

	if (*option_provided)
	{
		printf("Option \"%s\" supplied second time.\n", option);
		return false;
	}
	*option_provided = true;

	if (argument_is_suffix)
	{
		*option_arg = args[*arg_index] + strlen(option);
	}
	else
	{
		*arg_index += 1;
		*option_arg = args[*arg_index];
	}

	return true;
}

static bool digit_from_char(char character, int base, int* result)
{
	int value = 0;
	if ('0' <= character && character <= '9')
		value = character - '0';
	else if ('a' <= character && character <= 'z')
		value = character - 'a';
	else if ('A' <= character && character <= 'Z')
		value = character - 'A';

	if (value >= base)
		return false;

	*result = value;
	return true;
}

static int my_atoi(const char* string, int base, int* output)
{
	if (base <= 1 || base > 10 + 'z' - 'a' + 1)
		return 0;

	bool is_negative = false;
	if (string[0] == '-')
	{
		is_negative = true;
		++string;
	}

	int number = 0;
	for (; *string != '\0'; ++string)
	{
		if (is_negative && number < INT_MIN / base)
			return 0;
		else if (!is_negative && number > INT_MAX / base)
			return 0;
		number *= base;

		int digit = 0;
		if (!digit_from_char(*string, base, &digit))
			return 0;

		if (is_negative)
		{
			if (number < INT_MIN + digit)
			{
				// Same as number - digit < INT_MIN
				return 0;
			}
			number -= digit;
		}
		else
		{
			if (number > INT_MAX - digit)
			{
				// Same as number + digit > INT_MAX
				return 0;
			}
			number += digit;
		}
	}

	*output = number;

	return 1;
}

bool parse_parameters(int num_args, const char** args, struct parameters* parameters)
{
	int arg_index = 0;
	while (arg_index < num_args)
	{
		if (check_is_prefix(args[arg_index], "-m1"))
		{
			const char* option_arg = NULL;
			if (!extract_option(args, &arg_index, "-m1", &parameters->min_length_provided, &option_arg))
				return false;
			if (my_atoi(option_arg, 10, &parameters->min_length) == 0)
			{
				printf("Argument for option \"-m1\" is invalid.\n");
				return false;
			}
			arg_index += 1;
		}
		else if (check_is_prefix(args[arg_index], "-m2"))
		{
			const char* option_arg = NULL;
			if (!extract_option(args, &arg_index, "-m2", &parameters->max_length_provided, &option_arg))
				return false;
			if (my_atoi(option_arg, 10, &parameters->max_length) == 0)
			{
				printf("Argument for option \"-m2\" is invalid.\n");
				return false;
			}
			arg_index += 1;
		}
		else if (check_is_prefix(args[arg_index], "-n"))
		{
			const char* option_arg = NULL;
			if (!extract_option(args, &arg_index, "-n", &parameters->length_provided, &option_arg))
				return false;
			if (my_atoi(option_arg, 10, &parameters->length) == 0)
			{
				printf("Argument for option \"-n\" is invalid.\n");
				return false;
			}
			arg_index += 1;
		}
		else if (check_is_prefix(args[arg_index], "-c"))
		{
			const char* option_arg = NULL;
			if (!extract_option(args, &arg_index, "-c", &parameters->num_passwords_provided, &option_arg))
				return false;
			if (my_atoi(option_arg, 10, &parameters->num_passwords) == 0)
			{
				printf("Argument for option \"-c\" is invalid.\n");
				return false;
			}
			arg_index += 1;
		}
		else if (check_is_prefix(args[arg_index], "-a"))
		{
			if (!extract_option(args, &arg_index, "-a", &parameters->alphabet_provided, &parameters->alphabet))
				return false;
			arg_index += 1;
		}
		else if (check_is_prefix(args[arg_index], "-C"))
		{
			if (!extract_option(args, &arg_index, "-C", &parameters->symbol_sets_provided, &parameters->symbol_sets))
				return false;
			arg_index += 1;
		}
		else
			arg_index += 1;
	}

	if (parameters->length_provided && parameters->length <= 0)
	{
		printf("Length must be positive.\n");
		return false;
	}

	if (parameters->min_length_provided && parameters->min_length <= 0)
	{
		printf("Min length must be positive.\n");
		return false;
	}

	if (parameters->max_length_provided && parameters->max_length <= 0)
	{
		printf("Max length must be positive.\n");
		return false;
	}

	if (parameters->num_passwords_provided && parameters->num_passwords <= 0)
	{
		printf("Number of passwords must be positive.\n");
		return false;
	}

	if (parameters->min_length_provided && !parameters->max_length_provided)
	{
		printf("Min length requires max length to be supplied.\n");
		return false;
	}

	if (parameters->min_length_provided && parameters->max_length_provided && parameters->min_length > parameters->max_length)
	{
		printf("Min length must be not greater than max length.\n");
		return false;
	}

	if (parameters->length_provided && parameters->min_length_provided && parameters->max_length_provided)
	{
		printf("Specifying range of possible lengths when explicit length is stated is not allowed. \n");
		return false;
	}

	if (parameters->length_provided && parameters->max_length_provided && parameters->length > parameters->max_length)
	{
		printf("Length must be not greater than max length.\n");
		return false;
	}

	if (parameters->alphabet_provided && parameters->symbol_sets_provided)
	{
		printf("Cannot use alphabet and symbol sets both at the same time.\n");
		return false;
	}

	if (parameters->symbol_sets_provided)
	{
		for (size_t i = 0; i < strlen(parameters->symbol_sets); ++i)
		{
			char symbol_set = parameters->symbol_sets[i];
			if (symbol_set != 'a' && symbol_set != 'A' && symbol_set != 'D' && symbol_set != 'S')
			{
				printf("Invalid symbol set \'%c\'.\n", symbol_set);
				return false;
			}
		}
	}

	return true;
}