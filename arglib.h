#ifndef ARGLIB_H
#define ARGLIB_H

static int arglib_word, arglib_letter, arglib_help = 0;
static const char arglib_split = '=';

// Local copies of argc and argv to ensure testability.
static char **arglibv;
static int arglibc;

// For each letter in argv
#define arg_value arglibv[arglib_word][arglib_letter]
#define arg_args(_argc, _argv) \
	arglibv = _argv; \
	arglibc = _argc; \
	for (int arglib_word = 1; arglib_word < arglibc; arglib_word++) \
		for (int arglib_letter = 1; arg_value != '\0'; arglib_letter++) \
			switch (arg_value)

// Print the help menu
// Must be given the function in which arguments are handled first.
#define arg_help(func) \
	if (!arglib_help){ \
		arglib_help = 1; \
		func(arglibc, arglibv); \
		arglib_help = 0; \
		return 1; \
	}

// If current letter is arg
#define arg_option(arg, desc) \
	case (arg): \
		if (arglib_help ? printf("%c | %s\n", arg, desc) : 1) \
			if (arg_value == arg)

// Get the value of an arg (after the '=');
#define arg_align \
	arglibv[arglib_word] + arglib_letter + 2; \
	arglibv[arglib_word][arglib_letter + 1] = '\0'

#define arg_hasvalue  \
	if (arglibv[arglib_word][arglib_letter + 1] == arglib_split)

#define arg_notfound \
	if (arglib_help) return 1; \
	break; \
	default:

#define arg_exitvalue \
	fprintf(stderr, "Argument -%c requires a value\n", arg); \
	return 1;
#endif
