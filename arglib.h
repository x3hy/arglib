#ifndef ARGLIB_H
#define ARGLIB_H

// For each letter in argv
#define ARGIDX __arg_word
#define FORARGS \
	for (int ARGSIDX = 1; ARGSIDX < argc; ARGSIDX++) \
		for (int __arg_letter = 1; argv[ARGSIDX][__arg_letter] != '\0'; __arg_letter++) \
			switch (argv[ARGSIDX][__arg_letter])

// Print the help menu
static int __arg_help = 0;

// Must be given a *(int, char**) function
#define HELP(func) \
	do { \
		if (!__arg_help){ \
			__arg_help = 1; \
			func(argc, argv); \
			__arg_help = 0; \
		} \
	} while(0)

// If current letter is arg
#define ARG(arg, desc) \
	case (arg): \
		if (__arg_help ? printf("%c | %s\n", arg, desc) + 1 : 1) \
			if (argv[ARGSIDX][__arg_letter] == arg)

// Get the value of an arg (after the '=');
#define ALIGNARG(name) \
	char *name = argv[ARGSIDX] + __arg_letter + 2; \
	argv[ARGSIDX][__arg_letter + 1] = '\0'

#define HASVALUE \
	if (argv[ARGSIDX][__arg_letter + 1] == '=')

#define ARGELSE \
	if (__arg_help) return 1; \
	break; \
	default:
#endif
