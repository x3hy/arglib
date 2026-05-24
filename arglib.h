#ifndef ARGLIB_H
#define ARGLIB_H

// Basic strlen implementation.
static int _arglib_strlen(char *str){
	int str_s = 0;
	while (str[str_s])
		str_s++;
	return str_s+1;
}

/* checks if a given argument matches based on
 * a splitchar. */
static int _is_arg_match(char *pattern, char *arg, char splitchar){
	const int arg_len = _arglib_strlen(arg);

	// Locate the splitchar within the argument
	int split = 0;
	while (arg[split]){
		if (arg[split] == splitchar)
			break;
		split++;
	}

	// Save a copy of arg to undobuf
	char undobuf[arg_len];
	for (int i = 0; i < arg_len; i++)
		undobuf[i] = arg[i];

	// Separate the key and value from the argument
	char key[arg_len - split];
	for (int i = 0; i < arg_len; i++){
		if (i <= (split != arg_len-1 ? split : arg_len)){
			key[i] = arg[i];
			if (split && i == split) key[i] = '\0';
			else if (i == arg_len) arg[0] = '\0';
		}

		// Copy JUST the value back to arg
		if (split != arg_len -1)
			arg[i] = arg[i + split + 1];
	}

	/* now we have the following:
	 * key: first half of the argument (before the splitchar)
	 * arg: last half of the argument (after the splitchar) */

	for (int i = 0; i < _arglib_strlen(pattern); i++)
		if (pattern[i] != key[i]){
			// reset the argument using undobuf
			for (int i = 0; i < arg_len; i++)
				arg[i] = undobuf[i];
			return 1;
		}
	return 0;
}

static int  __arg_exitcode  =  0;
static char __arg_splitchar = '=';
static int __arg_show_help  =  0;

// Loops through arguments given
#define FORARGS \
	for (int __arg_i = 1; __arg_i < argc; __arg_i++)

// gets the value index from argv
#define ARGVAL argv[__arg_i]

#ifdef ARGLIB_HELP
#include <stdio.h>
// This should always return 1
static int _arg_show_help_menu(char *arg, char *desc){
	if (__arg_show_help)
		printf ("%s - %s\n", arg, desc);
	return __arg_show_help;
}

#define HELP(func, ac, av) \
	do { \
		__arg_show_help = 1; \
		func(ac, av); \
		__arg_show_help = 0; \
	} while (0)

#else
// filler function
#define _arg_show_help_menu(a,b) 0
#define HELP(func, ac, av) 0
#endif

/* Uses a switch case to allow for inline code execution.
 * the `switch` line also assigns __arg_success the return
 * code of _is_arg_match which checks if a given argument
 * matches the given pattern. */
#define ARG(arg, desc) \
	if (!_arg_show_help_menu(arg, desc)) \
		switch(__arg_exitcode = _is_arg_match(arg, \
					ARGVAL, __arg_splitchar)) \
			case 0:

#endif//ARGLIB_H
