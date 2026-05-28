#include <stdio.h>
#include "arglib.h"

// Argument processor function
void argparse(int argc, char *argv[]){
	FORARGS {
		// Can run single line code after statement
		// Built-in help menu
		ARG ("--help", "Show this basic help menu")
			/* Argument parsing is required to occur within
			 * a function in order to use the HELP menu. */
			HELP(argparse, argc, argv);

		// Multi-line code execution
		ARG ("--alt-test", "Another testing argument") {
			printf ("test123\n");
			printf ("test321\n");
			puts(ARGVAL);
		}

		ARG ("--positional", "Positional argument (must be the last given argument")
			if (! ARGLAST){
				// argument is not at the end of the list
				printf("%s must be the end argument\n", arg_name);
				goto exit;
			} else 
				printf ("working\n");


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
		ALTHELP(argparse);
		return 1;
	}
	
	/* Pass the command line arguments into parser
	 * function. */
	argparse(argc, argv);

	// That's it!
	return 0;
}
