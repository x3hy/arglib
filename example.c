#include "arglib.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	// for each argument
	arg_each(argv, argc){

		// can run single line code after statement
		acase("--help") printf("Help called!\n");

		// get the value of the argument
		acase("--test") printf("test run with value: %s\n", avalue);

		// multi-line code execution
		acase("--alt-test"){
			printf("test123\n");
			printf("test321\n");
		}

		// print some extra info
		printf("value: %s, exitcode: %d\n", avalue, __arg_exitcode);
	}

	return 0;
}
