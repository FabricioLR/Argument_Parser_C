#ifndef ARGUMENT_PARSER_H_
#define ARGUMENT_PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define PARSER_ASSERT(A, format, ...) if (!(A)) {fprintf(stderr, format, ##__VA_ARGS__); assert(A);}

#define Max_Flags 10

#define OPTION_IS_REQUIRED         0b00000001
#define OPTION_VALUE_IS_REQUIRED   0b00000010
#define OPTION_IS_DEFINED          0b10000000

#define IS_INITIALIZED             0b00000001

struct Option {
	char *key;
	char *description;
	char *value;
	uint8_t flags;
};
typedef struct Option Option;

struct Option_Array {
	Option options[Max_Flags];
	int count;
	int flags;
};
typedef struct Option_Array Option_Array;

Option_Array *option_array = NULL;

void add_option(char *key, char *description, uint8_t flags){
	if (option_array == NULL){
		option_array = (Option_Array *) malloc(sizeof(Option_Array));
		PARSER_ASSERT(option_array != NULL, "Cant allocate memory\n");
		option_array->count = 0;
	}

	Option *option = &(option_array->options[option_array->count]);

	option->key = (char *) malloc(sizeof(char) * strlen(key));
	option->description = (char *) malloc(sizeof(char) * strlen(description));
	PARSER_ASSERT(option->key != NULL && option->description != NULL, "Cant allocate memory\n");

	strcpy(option->key, key);
	strcpy(option->description, description);
	option->flags = flags;

	option_array->count += 1;
}


char *get_option_value(char *key){
	PARSER_ASSERT(option_array != NULL, "Call add_option() first\n");
	PARSER_ASSERT(option_array->flags & IS_INITIALIZED, "Cant execute before parser_init()\n");

	for (int i = 0; i < option_array->count; i++){
		Option *option = &(option_array->options[i]);
		if (strcmp(option->key, key) == 0){
			PARSER_ASSERT(option->flags & OPTION_VALUE_IS_REQUIRED, "Option %s does not require value\n", key);
			return option->value;
		}
	}

	PARSER_ASSERT(0, "Option %s not found\n", key);
}

int option_is_defined(char *key){
	PARSER_ASSERT(option_array != NULL, "Call add_option() first\n");
	PARSER_ASSERT(option_array->flags & IS_INITIALIZED, "Cant execute before parser_init()\n");

	for (int i = 0; i < option_array->count; i++){
		Option *option = &(option_array->options[i]);
		if (strcmp(option->key, key) == 0){
			return option->flags & OPTION_IS_DEFINED;
		}
	}

	PARSER_ASSERT(0, "Option %s not found\n", key);
}

void usage(){
	PARSER_ASSERT(option_array != NULL, "Call add_option() first\n");

	printf("OPTIONS: \n");
	for (int i = 0; i < option_array->count; i++){
		Option *option = &(option_array->options[i]);
		printf("     %s %s\n", option->key, option->flags & OPTION_VALUE_IS_REQUIRED ? "<value>" : "");
		printf("          description: %s\n", option->description);
		if (option->flags != 0) printf("          Flags: %s | %s\n", option->flags & OPTION_VALUE_IS_REQUIRED ? "OPTION_VALUE_IS_REQUIRED" : "", option->flags & OPTION_IS_REQUIRED ? "OPTION_IS_REQUIRED" : "");
	}
}

int parser_init(int argc, char **argv){
	PARSER_ASSERT(option_array != NULL, "Call add_option() first\n");

	for (int i = 1; i < argc; i++){
		if (argv[i][0] != '-') continue;
		int options_is_valid = 0;
		for (int j = 0; j < option_array->count; j++){
			if (strcmp(option_array->options[j].key, argv[i]) == 0) options_is_valid = 1;
		}
		if (!options_is_valid) { fprintf(stderr, "Unkown option: %s\n", argv[i]); return 0; }
	}

	for (int i = 0; i < option_array->count; i++){
		Option *option = &(option_array->options[i]);

		int is_required = 0;
		if (option->flags & OPTION_IS_REQUIRED){
			for (int j = 1; j < argc; j++){
				if (strcmp(option->key, argv[j]) == 0) { is_required = 1; break; }
			}
			if (is_required == 0) { fprintf(stderr, "Option %s is required\n", option->key); return 0; }
		} 

		int hasnt_value = 0;
		if (option->flags & OPTION_VALUE_IS_REQUIRED){
			for (int j = 1; j < argc; j++){
				if (strcmp(option->key, argv[j]) == 0) {
					if (j + 1 >= argc) { hasnt_value = 1; break; }
					if (argv[j + 1][0] == '-') { hasnt_value = 1; break; }

					option->value = (char *)malloc(sizeof(char) * strlen(argv[j + 1]));
					PARSER_ASSERT(option->value != NULL, "Cant allocate memory\n");
					strcpy(option->value, argv[j + 1]);
				}
			}
			if (hasnt_value == 1) { fprintf(stderr, "Invalid value for option %s\n", option->key); return 0; }
		}	

		for (int j = 1; j < argc; j++){
			if (strcmp(option->key, argv[j]) == 0) {
				option->flags |= OPTION_IS_DEFINED;
			}
		}
	}

	option_array->flags |= IS_INITIALIZED;

	return 1;
}

#endif // ARGUMENT_PARSER_H_