#include <stdio.h>
#include "arglib.h"

int main(int argc, char *argv[]){
	FORARGS
	{
		ARG ('h', "Show this menu") {
			// Pass in the current function as the argument function
			HELP(main);
		}

		// Takes a value
		ARG ('t', "Test arg") {
			printf("-t run\n");

			// Print value if its given:
			HASVALUE {
				ALIGNARG(value);
				printf("%s\n", value);

			} else
				printf("No args given to -t\n");
		}

		ARGELSE {
			printf("Unrecognised: %c\n", argv[__arg_word][__arg_letter]);
			return 1;
		}
	}

	return 0;
}
