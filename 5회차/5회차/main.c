#include "main.h"
#include "sub_word.h"
#include "sub_tree.h"

char first[MAX] = { NULL }, second[MAX] = { NULL };

extern NODE *alphabet_word[27];
extern int alphabet_n[27];

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

	fclose(fp);
}

void get_two_words_from_input(char input[]) {
	char *token = strtok(input, " ");

	strcpy(first, token);

	token = strtok(NULL, " ");

	if (token == NULL) {
		return;
	}
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
		command_add();
		return true;
	}
	else if (strcmp(first, "delete") == 0) {
		command_del();
		printf("Deleted successfully!\n");
		return true;
	}
	else if (strcmp(first, "deleteall") == 0) {
		command_destroy();
		return true;
	}
	else if (strcmp(first, "view") == 0) {
		command_view();
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

void command_find(){

	int result = word_sort_analysis(second);
	NODE *find_value = search_node(alphabet_word[result], second);

	if (find_value == NULL) {
		printf("Can not find such that word - ERROR!\n");
		return;
	}

	if (find_value->meaning[strlen(find_value->meaning) - 1] == '\n') {
		printf("The part of word you find : %s\nThe meaning of word you find : %s", find_value->part, find_value->meaning);
	}
	else {
		printf("The part of word you find : %s\nThe meaning of word you find : %s\n", find_value->part, find_value->meaning);
	}
}

void command_add() {
	// 현재 second가 쓰이지 않는 상태이므로, second를 temp 대용으로 사용한다

	int i = 0;

	printf("Word : ");
	command_add_assist(i);
	i++;

	printf("Class : ");
	command_add_assist(i);
	i++;

	printf("Meaning : ");
	command_add_assist(i);

	make_tree_with_data();
}

void command_add_assist(int i) {
	getchar();
	scanf("%[^\n]", second);
	input_analysis_data[i] = strdup(second);
	strcpy(second, "\0");
}

void command_del() {
	int result = word_sort_analysis(second);
	NODE *find_value = search_node(alphabet_word[result], second);

	if (find_value == NULL) {
		printf("Can not find such that word - ERROR!\n");
		return;
	}

	alphabet_n[result]--;
	del_node(alphabet_word[result], find_value);
}

void command_destroy() {

	char input_temp[MAX] = { NULL }, save_the_name[MAX] = { NULL };
	int count = 0;

	strcpy(save_the_name, second);

	FILE *fp = fopen(save_the_name, "r");

	while (1) {

		fgets(input_temp, MAX, fp);

		if (feof(fp)) {
			break;
		}

		command_destroy_assist(input_temp);

		strcpy(second, input_analysis_data[0]);
		command_del();

		count++;
	}

	printf("%d words were deleted successfully!\n", count);
}

void command_destroy_assist(char input_temp[]) {
	char *token = NULL, complete[MAX] = { NULL };
	int i = 0;

	token = strtok(input_temp, " ");
	strcpy(complete, token);

	while (1) {
		token = strtok(NULL, " ");

		if (token[0] == '(') {
			break;
		}

		strcat(complete, " ");
		strcat(complete, token);
	}
	
	i = 0;

	make_analysis_data(complete, i);
}

void command_view() {
	int result = word_sort_analysis(second);
	
	inorder_walk(alphabet_word[result]);
}