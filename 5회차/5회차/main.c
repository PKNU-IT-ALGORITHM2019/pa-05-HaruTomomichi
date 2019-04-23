#include "main.h"
#include "sub_word.h"
#include "sub_tree.h"

char first[MAX], second[MAX];

void main() {

	initialize();

	char input[MAX];

	while (1) {
		printf("$ ");
		scanf("%[^\n]", input);

		get_two_words_from_input(input);

		bool result = analysis();

		if (!result && strcmp(input,"exit") == 0) {
			break;
		}
		else if (!result) {
			printf("잘못된 명령입니다! 다시 입력하십시오\n");
		}
		getchar();
	}
}

void initialize() {

	char input_temp[MAX];

	FILE *fp = fopen("shuffled_dict.txt", "r");

	while (1) {

		fgets(input_temp, MAX, fp);

		if (feof(fp)) {
			break;
		}

		make_word_for_tree(input_temp);
	}
}

void get_two_words_from_input(char input[]) {
	char *token = strtok(input, " ");

	strcpy(first, token);

	token = strtok(NULL, " ");

	strcpy(second, token);
}

bool analysis() {

	if (strcmp(first, "size") == 0) {
		command_size();
		return true;
	}
	else if (strcmp(first, "find") == 0) {
		command_find();
		return true;
	}
	else if (strcmp(first, "add") == 0) {
		return true;
	}
	else if (strcmp(first, "delete") == 0) {
		return true;
	}
	else if (strcmp(first, "deleteall") == 0) {
		return true;
	}
	else if (strcmp(first, "exit") == 0) {
		return false;
	}
	return false;
}

void command_size() {
	int sum = 0;

	for (int i = 0; i < 26; i++) {
		sum += alphabet_n[i];
	}
	printf("%d\n", sum);
}

void command_find() {

	int result = word_sort_analysis(second);
	NODE *find_value = search_node(alphabet_word[result], second);

	if (find_value == NULL) {
		printf("Can not find such that word - ERROR!\n");
		return;
	}
	printf("The part of word you find - %s / The meaning of word you find - %s\n",find_value->part, find_value->meaning);
}