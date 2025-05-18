#include "../argument-parser.h"
#include <stdio.h>

int main(int argc, char **argv){
	if (!parser_init(argc, argv)){
		printf("main |-arg1 *\n     |--argument1 *\n     optional ---\n       |-arg2\n       |--argument2\n     optional ---\n       |--argument3 *\n");
		return 1;
	}

	printf("Value of --arg1: %s\n", get_argument_value("-arg1"));
	printf("--argument2 is defined? %s\n", argument_is_defined("--argument2") == 1 ? "true" : "false");
	if (argument_is_defined("--argument3")) printf("Value of --argument3: %s\n", get_argument_value("--argument3"));
	printf("Value of --argument3342: %s\n", get_argument_value("--argument3342"));

	return 0;
}