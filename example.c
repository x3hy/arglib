#include "arglib.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	struct arguments[] = {
		CAT("basic", OPT(ENABLED),
			{"--help", "Shows the help menu", OPT(TAKES_VALUE, NOT_NULL)},
			{"--test",
		),
		CAT("other", OPT(ENABLED),
			{"--test2", "test argument", OPT(TAKES_VALUE, UNIQUE)},
			{"--test3", "another test", OPT(NO_VALUE, LAST_ITEM)}
		)
	};
}
