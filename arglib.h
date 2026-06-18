#ifndef ARGLIB_H
#define ARGLIB_H

static int __arg_word, __arg_letter, __arg_help = 0;
static const char __arg_split = '=';

// Local copies of argc and argv to ensure testability.
static char **__argv;
static int __argc;

// For each letter in argv
#define ARGVAL __argv[__arg_word][__arg_letter]
#define FORARGS(_argc, _argv) \
	__argv = _argv; \
	__argc = _argc; \
	for (int __arg_word = 1; __arg_word < __argc; __arg_word++) \
		for (int __arg_letter = 1; ARGVAL != '\0'; __arg_letter++) \
			switch (ARGVAL)

// Print the help menu
// Must be given the function in which arguments are handled first.
#define HELP(func) \
	if (!__arg_help){ \
		__arg_help = 1; \
		func(__argc, __argv); \
		__arg_help = 0; \
		return 1; \
	}

// If current letter is arg
#define ARG(arg, desc) \
	case (arg): \
		if (__arg_help ? printf("%c | %s\n", arg, desc) : 1) \
			if (ARGVAL == arg)

// Get the value of an arg (after the '=');
#define ALIGNARG \
	__argv[__arg_word] + __arg_letter + 2; \
	__argv[__arg_word][__arg_letter + 1] = '\0'

#define HASVALUE \
	if (__argv[__arg_word][__arg_letter + 1] == __arg_split)

#define ARGELSE \
	if (__arg_help) return 1; \
	break; \
	default:
#endif
