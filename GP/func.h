#pragma once


struct parameters
{
	bool min_length_provided;
	int min_length;

	bool max_length_provided;
	int max_length;

	bool length_provided;
	int length;

	bool num_passwords_provided;
	int num_passwords;

	bool alphabet_provided;
	const char* alphabet;

	bool symbol_sets_provided;
	const char* symbol_sets;
};

static bool check_is_prefix(const char* string, const char* prefix);
static bool extract_option(const char** args, int* arg_index, const char* option, bool* option_provided, const char** option_arg);
static bool digit_from_char(char character, int base, int* result);
static int my_atoi(const char* string, int base, int* output);
extern bool parse_parameters(int num_args, const char** args, struct parameters* parameters);
