#include "main.h"
#include "sub_word.h"
#include "sub_tree.h"

void main() {

	initialize();

	char input[MAX];

	while (1) {
		printf("$ ");
		scanf("%[^\n]", input);

		if (!analysis(input) && strcmp(input,"exit") == 0) {
			break;
		}
		else if (!analysis(input)) {
			printf("잘못된 명령입니다! 다시 입력하십시오\n");
		}
		getchar();
	}
}

void initialize() {

	char input_temp[MAX];

	FILE *fp = fopen("data.txt", "r");

	while (!feof(fp)) {

		fgets(input_temp, MAX, fp);

		make_word_for_tree(input_temp);
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
		return false;
	}
	return false;
}