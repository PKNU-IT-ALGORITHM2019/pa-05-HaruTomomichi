#include "main.h"
#include "sub_word.h"
#include "sub_tree.h"

void make_word_for_tree(char input_temp[]) {

	char *token = NULL, complete[MAX] = { NULL };
	int i = 0;

	token = strtok(input_temp," ");
	strcpy(complete, token);

	while (1) {
		token = strtok(NULL, " ");

		if (token[0] == '(') {
			break;
		}

		strcat(complete, " ");
		strcat(complete, token);
	}

	make_analysis_data(complete,i);
	i++;

	strcpy(complete, token);
	while (1) {
		token = strtok(NULL, " ");

		if (token == NULL || token[strlen(token)-1] != ')') {
			break;
		}

		strcat(complete, " ");
		strcat(complete, token);
	}

	make_analysis_data(complete, i);
	i++;

	if (token == NULL) {
		strcpy(complete, "\0");
	}
	else {
		strcpy(complete, token);
	}

	while (1) {
		token = strtok(NULL, " ");

		if (token == NULL) {
			break;
		}

		strcat(complete, " ");
		strcat(complete, token);
	}

	make_analysis_data(complete, i);
	i = 0;

	make_tree_with_data();
}

void make_analysis_data(char complete[],int i) {
	input_analysis_data[i] = strdup(complete);
}