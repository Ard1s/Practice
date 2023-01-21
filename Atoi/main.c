#define _CRT_SECURE_NO_WARNINGS

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static bool check_is_prefix(const char* string, const char* prefix) 
{
	while (*string != '\0' && *prefix != '\0') 
	{
		if (*string != *prefix) 
			return false;
		++string;
		++prefix;
	}
	if (*string == '\0' && *prefix != '\0') 
		return false;

	return true;
}

static bool digit_from_char(char character, int base, int* result) 
{
	int value = 0;
	if ('0' <= character && character <= '9')
		value = character - '0';
	else if ('a' <= character && character <= 'z') 
		value = 10 + character - 'a';
	else if ('A' <= character && character <= 'Z') 
		value = 10 + character - 'A';

	if (value >= base) 
		return false;

	*result = value;
	return true;
}

int strtoi(const char* string, const char** char_error_at, int* result) 
{
	bool is_negative = false;
	if (*string == '-') 
	{
		is_negative = true;
		++string;
	}

	int base = 0;
	if (check_is_prefix(string, "0x") || check_is_prefix(string, "0X")) 
	{
		base = 16;
		string += 2;
	}
	else if (check_is_prefix(string, "0")) 
	{
		base = 8;
		string += 1;
		if (*string == '\0') 
		{
			*result = 0;
			return 1;
		}
	}
	else if (check_is_prefix(string, "b")) 
	{
		base = 2;
		string += 1;
	}
	else 
		base = 10;

	if (*string == '\0') 
	{
		// Empty string. Not a valid number.
		if (char_error_at != NULL) 
			*char_error_at = string;
		return 0;
	}

	if (char_error_at != NULL)
		*char_error_at = NULL;

	int number = 0;
	while (*string != '\0') 
	{
		if (is_negative && number < INT_MIN / base) 
		{
			*char_error_at = string;
			*result = number;
			return 0;
		}
		else if (!is_negative && number > INT_MAX / base) 
		{
			*char_error_at = string;
			*result = number;
			return 0;
		}
		number *= base;

		int digit = 0;
		if (!digit_from_char(*string, base, &digit)) 
		{
			*char_error_at = string;
			*result = number;
			return 0;
		}
		++string;

		if (is_negative) 
		{
			if (number < INT_MIN + digit) 
			{
				// Same as number - digit < INT_MIN
				*char_error_at = string;
				*result = number;
				return 0;
			}
			number -= digit;
		}
		else 
		{
			if (number > INT_MAX - digit) 
			{
				// Same as number + digit > INT_MAX
				*char_error_at = string;
				*result = number;
				return 0;
			}
			number += digit;
		}
	}

	*result = number;

	return 1;
}

static void reverse_string(char* number_start_ptr, char* number_end_ptr) 
{
	size_t number_len = (size_t)(number_end_ptr - number_start_ptr) + 1;
	for (; number_len >= 2; number_len -= 2) 
	{
		char tmp_first = *number_start_ptr;
		*number_start_ptr = *number_end_ptr;
		*number_end_ptr = tmp_first;

		++number_start_ptr;
		--number_end_ptr;
	}
}


int my_itoa(char* buffer, int buffer_size, int value, int base) 
{
	int num_chars_written = 0; 

	if (buffer_size < 1)
		return 0;
	buffer_size -= 1;

	if (base <= 1 || base > 10 + 'z' - 'a' + 1)
		return 0;

	if (value < 0) 
	{
		if (buffer_size == 0) 
			return 0;

		*buffer = '-';
		++buffer;
		num_chars_written += 1;
		buffer_size -= 1;
	}

	if (value == 0) 
	{
		if (buffer_size == 0)
			return 0;
		*buffer = '0';
		++buffer;
		num_chars_written += 1;
		buffer_size -= 1;

		*buffer = '\0';
		return num_chars_written;
	}

	char* number_start_ptr = buffer;

	while (value != 0) 
	{
		int digit = value % base;
		if (digit != 0 && (digit < 0) != (value < 0)) 
		{
			if (value < 0)
				digit -= base;
			else 
				digit += base;
		}
		if (digit < 0) 
			digit *= -1;

		if (buffer_size == 0) 
			return num_chars_written;

		if (digit >= 10)
			*buffer = (char)('a' + (digit - 10));
		else 
			*buffer = (char)('0' + digit);
		++buffer;
		num_chars_written += 1;
		buffer_size -= 1;

		if (value < 0) 
			value += digit;
		else
			value -= digit;
		value /= base;
	}

	char* number_end_ptr = buffer - 1;
	reverse_string(number_start_ptr, number_end_ptr);

	*buffer = '\0';

	return num_chars_written;
}

int main() 
{
	printf("Enter string: ");
	fflush(stdout);

	char input_buffer[100 + 1] = { 0 };
	if (scanf("%100s", input_buffer) != 1)
		return 1;

	int number = 0;
	char* char_error_at = NULL;
	int strtoi_result = strtoi(input_buffer, (const char**)&char_error_at, &number);
	printf("Number is %d", number);
	if (char_error_at != NULL) 
		printf(", error at %zu-th (0-indexed) pos", (size_t)(char_error_at - input_buffer));
	printf(", strtoi result is %d.\n", strtoi_result);

	printf("Enter buffer size: ");
	fflush(stdout);

	size_t buffer_size = 0;

	if (scanf("%zu", &buffer_size) != 1) 
	{
		printf("Error while reading buffer size.\n");
		return 2;
	}
	else if (buffer_size == 0) 
	{
		printf("Buffer size of 0 is not allowed.\n");
		return 3;
	}

	if (buffer_size > INT_MAX) 
	{
		printf("Too big buffer.\n");
		return 4;
	}

	char* my_itoa_buffer = calloc(buffer_size, sizeof(char));
	if (my_itoa_buffer == NULL) 
	{
		printf("Failed to allocate buffer.\n");
		return 5;
	}

	int atoi_result = 0;

	atoi_result = my_itoa(my_itoa_buffer, (int)buffer_size, number, 8);
	printf("Number base 8 is %s, my_itoa result is %d.\n", my_itoa_buffer, atoi_result);

	atoi_result = my_itoa(my_itoa_buffer, (int)buffer_size, number, 10);
	printf("Number base 10 is %s, my_itoa result is %d.\n", my_itoa_buffer, atoi_result);

	atoi_result = my_itoa(my_itoa_buffer, (int)buffer_size, number, 16);
	printf("Number base 16 is %s, my_itoa result is %d.\n", my_itoa_buffer, atoi_result);

	atoi_result = my_itoa(my_itoa_buffer, (int)buffer_size, number, 20);
	printf("Number base 20 is %s, my_itoa result is %d.\n", my_itoa_buffer, atoi_result);

	free(my_itoa_buffer);

	return 0;
}