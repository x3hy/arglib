#include <stdio.h>
#include "arglib.h"

int main(int argc, char *argv[]){
	FORARGS( argc, argv) {
		ARG ('h', "Show this menu")
			// Pass in the current function as the argument function
			HELP(main);

		// Takes a value
		ARG ('t', "Test arg (takes a value)") {

			// Print value if its given:
			HASVALUE {

				// Get the value after the '='
				char *value = ALIGNARG;
				printf("-t was run with value: %s\n", value);

			} else
				puts("-t was run with no value");
		}

		ARGELSE {
			printf("Unrecognised: %c\n", ARGVAL);
			return 1;
		}
	}

	if (argc == 1)
		puts("use -h for info");

	return 0;
}
