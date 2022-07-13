#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "func.h"


int main(int argc, const char** argv) 
{
	srand((unsigned int)time(NULL));

	struct parameters parameters = { 0 };
	if (!parse_parameters(argc, argv, &parameters)) 
	{
		return 1;
	}

	size_t password_len = 0;
	static const size_t DEFAULT_PASSWORD_LEN = 12;
	if (parameters.length_provided) 
	{
		assert(parameters.length >= 1);
		password_len = (size_t)parameters.length;
	}
	else if (parameters.min_length && parameters.max_length) 
	{
		assert(parameters.min_length >= 1);
		assert(parameters.min_length <= parameters.max_length);

		int num_lengths = parameters.max_length - parameters.min_length + 1;
		int length_index = abs(rand()) % num_lengths;

		password_len = (size_t)(parameters.min_length + length_index);
	}
	else 
		password_len = DEFAULT_PASSWORD_LEN;

	size_t alphabet_len = 0;

	static const char SPECIAL_SYMBOLS[] = "()*&%$#@!-+=*^<>?/.[]{}\\|";

	static const size_t LATIN_ALPHABET_LEN = 'z' - 'a' + 1;
	static const size_t NUM_DIGITS = 10;
	const size_t NUM_SPECIAL_SYMBOLS = sizeof(SPECIAL_SYMBOLS) / sizeof(char) - 1;

	if (parameters.alphabet_provided) 
	{
		// Alphabet from user input.
		alphabet_len = strlen(parameters.alphabet);
	}
	else 
	{
		// Alphabet from symbol sets.
		// If no symbol sets were provided, default alphabet is all symbol sets.
		if (!parameters.symbol_sets_provided) 
		{
			// Use default alphabet.
			// Default alphabet is generated from a symbol set.
			parameters.symbol_sets_provided = true;
			parameters.symbol_sets = "aADS";
		}
		if (strchr(parameters.symbol_sets, 'a') != NULL) 
			alphabet_len += LATIN_ALPHABET_LEN;

		if (strchr(parameters.symbol_sets, 'A') != NULL) 
			alphabet_len += LATIN_ALPHABET_LEN;
		
		if (strchr(parameters.symbol_sets, 'D') != NULL) 
			alphabet_len += NUM_DIGITS;
		
		if (strchr(parameters.symbol_sets, 'S') != NULL) 
			alphabet_len += NUM_SPECIAL_SYMBOLS;
		
	}

	char* alphabet = calloc(alphabet_len + 1, sizeof(char));
	if (alphabet == NULL) 
	{
		printf("Failed to allocate memory for alphabet.\n");
		return 2;
	}

	if (parameters.alphabet_provided) 
		memcpy(alphabet, parameters.alphabet, alphabet_len);
	else 
	{
		assert(parameters.symbol_sets_provided);

		if (strchr(parameters.symbol_sets, 'a') != NULL) 
		{
			size_t cur_alphabet_len = strlen(alphabet);
			for (char chr = 'a'; chr <= 'z'; ++chr) 
			{
				alphabet[cur_alphabet_len] = chr;
				++cur_alphabet_len;
			}
		}
		if (strchr(parameters.symbol_sets, 'A') != NULL) 
		{
			size_t cur_alphabet_len = strlen(alphabet);
			for (char chr = 'A'; chr <= 'Z'; ++chr) 
			{
				alphabet[cur_alphabet_len] = chr;
				++cur_alphabet_len;
			}
		}
		if (strchr(parameters.symbol_sets, 'D') != NULL) 
		{
			size_t cur_alphabet_len = strlen(alphabet);
			for (char chr = '0'; chr <= '9'; ++chr) 
			{
				alphabet[cur_alphabet_len] = chr;
				++cur_alphabet_len;
			}
		}
		if (strchr(parameters.symbol_sets, 'S') != NULL) 		
			strcat(alphabet, SPECIAL_SYMBOLS);
		
	}

	char* password = calloc(password_len + 1, sizeof(char));
	if (password == NULL) 
	{
		free(alphabet);
		printf("Failed to allocate memory for password.\n");
		return 3;
	}

	int num_passwords = 1;
	if (parameters.num_passwords_provided) 
		num_passwords = parameters.num_passwords;


	for (int password_index = 0; password_index <= num_passwords; ++password_index) 
	{
		for (size_t i = 0; i < password_len; ++i) 
		{
			password[i] = alphabet[(size_t)abs(rand()) % alphabet_len];
		}

		printf("%s\n", password);
	}

	free(password);
	free(alphabet);

	return 0;
}