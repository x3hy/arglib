#include "arglib.h"
#include <stdio.h>

// Argument processor function
void argparse(int argc, char *argv[]){
	FORARGS {
		// Can run single line code after statement
		// Built-in help menu
		ARG ("--help", "Show this basic help menu")
			/* Argument parsing is required to occur within
			 * a function in order to use the HELP menu. */
			HELP(argparse, argc, argv);

		// Get the value of the argument
		ARG ("--test", "Basic testing argument")
			printf ("test run with value: %s\n", ARGVAL);

		// Multi-line code execution
		ARG ("--alt-test", "Another testing argument") {
			printf ("test123\n");
			printf ("test321\n");
		}
	}
}

// Argument processor function
int main (int argc, char *argv[]) {
	
	/* Pass the command line arguments into parser
	 * function. */
	argparse(argc, argv);

	// That's it!
	return 0;
}
