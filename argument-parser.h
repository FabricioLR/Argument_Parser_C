#ifndef ARGUMENT_PARSER_H_
#define ARGUMENT_PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#define ERROR_LOG(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define LOG(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define PARSER_ASSERT(A, format, ...) if(!(A)) {ERROR_LOG(format, ##__VA_ARGS__); assert(A);}

struct Node {
	char name[255];
	char alias[255];
	char value[255];
	int has_value;
	int required;
	struct Node *next;
};

int linked_list_insert(struct Node *head, char name[255], char alias[255], int has_value, int required){
	struct Node *current = head;

	while (current->next != NULL){
		current = current->next;
	}

	current->next = (struct Node *)malloc(sizeof(struct Node));
	if (current->next == NULL){
		ERROR_LOG("Cannot allocate memory\n");
		return 0;
	}
	current->next->next = NULL;
	strcpy(current->name, name);
	strcpy(current->alias, alias);
	current->value[0] = '\0';
	current->has_value = has_value;
	current->required = required;

	return 1;
}

struct Node* linked_list_search(struct Node *head, char *key){
	struct Node *current = head;

	while (current != NULL){
		if (strcmp(current->name, key) == 0) return current;
		if (current->alias[0] != '\0'){
			if (strcmp(current->alias, key) == 0) return current;
		}
		current = current->next;
	}

	return NULL;
}

void substring(char *string, char *buffer, int n){
	int count = 0, j = 0;

	for (int i = 0; i < strlen(string); i++){
		if (count >= n - 1 && count < n && string[i] != ':'){
			buffer[j] = string[i];
			j++;
		}

		if (string[i] == ':') count++;
	}

	buffer[j] = '\0';
}

int read_config(struct Node *head){
	FILE *f = fopen("argument-parser.config", "r");
	PARSER_ASSERT(f != NULL, "Cannot open argument-parse.config file\n")

	char buffer[255], name[255], alias[255], has_value_tmp[1], required_tmp[1];
	int has_value = 0, required = 0;

	while (fgets(buffer, 255, f)){
		if (buffer[0] == '#') continue;

		substring(buffer, name, 1);
		substring(buffer, alias, 2);
		substring(buffer, has_value_tmp, 3);
		substring(buffer, required_tmp, 4);

		if (alias[0] == '0') alias[0] = '\0';
		if (has_value_tmp[0] == '1') has_value = 1;
		if (required_tmp[0] == '1') required = 1;

		linked_list_insert(head, name, alias, has_value, required);

		has_value = 0, required = 0, name[0] = '\0', alias[0] = '\0', buffer[0] = '\0';
	}

	return 1;
}

struct Node *head = NULL;

int parser_init(int argc, char **argv){
	head = (struct Node *)malloc(sizeof(struct Node));
	if (head == NULL){
		ERROR_LOG("Cannot allocate memory\n");
		return 0;
	}

	read_config(head);

	struct Node *current = head;

	while (current != NULL){
		if (!current->required) {
			current = current->next;
			continue;
		}

		int is_defined = 0;
		for (int i = 1; i < argc; i++){
			if (strcmp(current->name, argv[i]) == 0) is_defined = 1;
		}

		PARSER_ASSERT(is_defined != 0, "Option %s is required\n", current->name);

		current = current->next;
	}

	for (int i = 1; i < argc; i++){
		if (argv[i][0] == '-'){
			struct Node *arg = linked_list_search(head, argv[i]);
			if (arg == NULL){
				LOG("Unknown option: %s\n", argv[i]);
				return 0;
			}

			if (arg->has_value){
				PARSER_ASSERT(i + 1 < argc, "Option %s requires one value\n", argv[i]);
				PARSER_ASSERT(argv[i + 1][0] != '-', "Invalid value for option %s\n", argv[i]);
				strcpy(arg->value, argv[i + 1]);
			} else {
				arg->value[0] = '1';
			}
		}
	}

	return 1;
}

int option_is_defined(char *key){
	PARSER_ASSERT(head != NULL, "Call parser_init() first\n");

	struct Node *arg = linked_list_search(head, key);
	if (arg == NULL) return 0;

	return 1;
}

int argument_is_defined(char *key){
	PARSER_ASSERT(head != NULL, "Call parser_init() first\n");

	struct Node *arg = linked_list_search(head, key);
	if (arg == NULL) return 0;

	return arg->value[0] != '\0';
}

char *get_argument_value(char *key){
	PARSER_ASSERT(head != NULL, "Call parser_init() first\n");
	PARSER_ASSERT(option_is_defined(key) == 1, "Option %s is not defined in the config file\n", key);

	struct Node *arg = linked_list_search(head, key);

	PARSER_ASSERT(arg->has_value == 1, "Option %s does not require value\n", arg->name);

	if (arg == NULL) return '\0';

	return arg->value;
}

#endif