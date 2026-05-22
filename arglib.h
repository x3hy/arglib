#ifndef ARGLIB_H
#define ARGLIB_H

#define ARGLIB_MAX_ARGLEN 256
static int  __arg_exitcode  =  0;
static char __arg_splitchar = '=';


/* Function declarations */
static int _is_arg_match(char *pattern, char *arg);

/* macroslop */

/* Loops through arguments given, av and ac are equ to
 * argv and argc. */
#define arg_each(_argv, _argc) \
	for (int __arg_i = 1; __arg_i < _argc; __arg_i++)

#define avalue argv[__arg_i]

/* Uses a switch case to allow for inline code execution.
 * the `switch` line also assigns __arg_success the return
 * code of _is_arg_match which checks if a given argument
 * matches the given pattern. */
#define acase(arg) \
	switch(__arg_exitcode = _is_arg_match(arg, avalue)) \
		case 0:

static int _arglib_strlen(char *str){
	if (!str) return 1;
	int str_s = 0;
	while (str[str_s])
		str_s++;
	return str_s+1;
}

static int _arglib_strcmp(char *s1, char *s2){
	if (!s1 || !s2) return -1;
	while (*s1 && !(*s1 - *s2)){
		s1++;
		s2++;
	}
	
	return *s1 - *s2;
}

#include <stdio.h>
static int _is_arg_match(char *pattern, char *arg){
	const int arg_len = _arglib_strlen(arg);
	if (arg_len > arg_len)
		// Argument exceeds limit
		return -1;

	// Locate the splitchar within the argument
	int split = 0;
	while (arg[split]){
		if (arg[split] == __arg_splitchar)
			break;
		split++;
	}

	// Save a copy of argument for later :3
	char undobuf[arg_len];
	for (int i = 0; i < arg_len; i++)
		undobuf[i] = arg[i];

	// Separate the key and value from the argument
	// taken from x3hy/plib/plib6.h
	//
	// TODO: this can be optimised
	char key[arg_len - split];
	for (int i = 0; i < arg_len; i++){
		if (i <= (split != arg_len-1 ? split : arg_len)){
			key[i] = arg[i];
			if (split && i == split)
				key[i] = '\0';
			else if (i == arg_len)
				arg[0] = '\0';
		}

		// Copy all the content after the split
		// back to arg. This will leave arg with
		// just the last half (after the splitchar).
		if (split != arg_len -1)
			arg[i] = arg[i + split + 1];
	}

	// now we have the following:
	// key: first half of the argument (before the splitchar)
	// arg: last half of the argument (after the splitchar)
	if (_arglib_strcmp(pattern, key) == 0)
		return 0;

	// reset the argument using undobuf
	for (int i = 0; i < arg_len; i++)
		arg[i] = undobuf[i];

	return 1;
}

#endif//ARGLIB_H
