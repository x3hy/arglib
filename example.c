#define ARGLIB_HELP
#include "arglib.h"
#include <stdio.h>

// Argument processor function
void argparse(int argc, char *argv[]){
	FORARGS {
		// Can run single line code after statement
		ARG ("--help", "Show a basic help menu"){
			HELP(argparse, argc, argv);
		}

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
	argparse(argc, argv);

	// That's it!
	return 0;
}
