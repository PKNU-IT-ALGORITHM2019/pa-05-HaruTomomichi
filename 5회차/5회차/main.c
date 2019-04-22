#include "main.h"
#include "sub_word.h"
#include "sub_tree.h"

void main() {

	char input[MAX];

	while (1) {
		printf("$ ");
		scanf("%[^\n]", input);

		if (!analysis(input)) {
			break;
		}
		getchar();
	}
}

bool analysis(char input[]) {
	if (strcmp(input, "find") == 0) {
		return true;
	}
	else if (strcmp(input, "add") == 0) {
		return true;
	}
	else if (strcmp(input, "delete") == 0) {
		return true;
	}
	else if (strcmp(input, "deleteall") == 0) {
		return true;
	}
	else if (strcmp(input, "exit") == 0) {
		return true;
	}
	return false;
}