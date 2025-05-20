#include "../argument-parser.h"

int main(int argc, char **argv){
	add_option("--argument1", "Argumento1 para teste", OPTION_IS_REQUIRED | OPTION_VALUE_IS_REQUIRED);
	add_option("-arg2", "Argumento2 para teste", 0);

	if (!parser_init(argc, argv)){
		usage();
		return 0;
	}

	printf("%s\n", get_option_value("--argument1"));
	if (option_is_defined("-arg2")) printf("%s\n", get_option_value("-arg2"));
	printf("%s\n", get_option_value("-naoexiste"));

	return 0;
}