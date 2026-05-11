#ifndef ARGLIB_H
#define ARGLIB_H

// Dependencies
#include <stdint.h>
#include <stdarg.h>
#include <limits.h>

// Type used for properties, increase this to a
// uint16_t if you have custom properties
#define _ARG_PROP_TYPE uint8_t

// Possible opts, refer to the _ARG_PROP_TYPE
// if you intend on adding more properties
enum {
	UNIUQE,
	NO_VALUE,
	TAKES_VALUE,
	NOT_NULL,
	FIRST_ARG,
	LAST_ARG,
	SINGLE_USE
};

// prior is uint8_t this value will be 8
#define _ARG_MAX_PROP (int)(sizeof(_PROP_TYPE))

// Gets the count of VA_ARGS
#define _VA_ARGS_COUNT(...) \
	sizeof((int[]){0, __VA_ARGS__}) / sizeof(int)
#define OPT(...) \
	(_VA_ARGS_COUNT(__VA_ARGS__) ? 0 : arglib_combine_opts())

/**
 * Combines given values into a singular prop type
 * See: OPT
 **/
static _ARG_PROP_TYPE
arg_combine_opts(int count, ...)
{
	if (count > _ARG_MAX_PROP || count <= 0)
		return 0u;

	// Fetch va arg list
	va_list lst;
	va_start(lst, count);
	_ARG_PROP_TYPE out = 0u;

	// for each given opt
	for (int i = 0; i < count; i++)
		out = out ^ (1u << va_arg(lst, int));

	va_end(lst);
	return out;
}

// linked list for the values in the argument list
typedef struct arg_value {
	char *value;
	int index;
	struct arg_value *next;
} arg_value;

// linked list for the arguments
typedef struct arg_linked_list {
	char *flag;
	char *desc;
	struct arg_linked_list *next;
} arg_linked_list;


#endif//ARGLIB_H
