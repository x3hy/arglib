#include <stdio.h>
#include "arglib.h"

// Argument processor function
void argparse(int argc, char *argv[]){
	FORARGS {
		// Positional argument
		POSANY(ARGLAST, "filename", "Must be the last argument"){
			printf("%s\n", ARGVAL);
			ARGNEXT;
		}

		// Can run single line code after statement
		// Built-in help menu
		ARG ("--help", "Show this basic help menu")
			HELP(argparse);

		// Multi-line code execution
		ARG ("--alt-test", "Another testing argument"){
			printf ("test123\n");
			printf ("test321\n");
			puts(ARGVAL);
		}

		// ...
	}
	exit:
}

// Argument processor function
int main (int argc, char *argv[]) {

	// If no args are given.
	if (argc == 1){

		/* When not inside a FORARGS loop,
		 * you can use ALTHELP. */
		HELP(argparse);
		return 1;
	}
	
	/* Pass the command line arguments into parser
	 * function. */
	argparse(argc, argv);

	// That's it!
	return 0;
}
