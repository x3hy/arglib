#include <stdio.h>
#include "arglib.h"

int main(int argc, char *argv[]){

	// For each arg
	arg_args( argc, argv) {
		arg_option ('h', "Show this menu")
			// Pass in the current function as the argument function
			arg_help(main);

		// Takes a value
		arg_option ('t', "Test arg (takes a value)") {

			// Print value if its given:
			arg_hasvalue {

				// Get the value after the '='
				char *value = arg_align;
				printf("-t was run with value: %s\n", value);

			} else
				puts("-t was run with no value");
		}

		arg_notfound {
			printf("Unrecognised: %c\n", arg_value);
			return 1;
		}
	}

	if (argc == 1)
		puts("use -h for info");

	return 0;
}
