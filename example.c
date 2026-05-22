#include "arglib.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	// For each argument
	FORARGS {

		// Can run single line code after statement
		ARG("--help") printf("Help called!\n");

		// get the value of the argument
		ARG("--test") printf("test run with value: %s\n", ARGVAL);

		// Multi-line code execution
		ARG("--alt-test"){
			printf("test123\n");
			printf("test321\n");
		}
	}

	// That's it!
	return 0;
}
