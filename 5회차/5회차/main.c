#include "main.h"

char first[MAX] = { NULL }, second[MAX] = { NULL };
NODE *alphabet_word[27] = { NULL }; // 26개의 헤드를 저장하는 공간
int alphabet_n[27] = { 0 }; // 각 단어가 저장되는 회수 / 26번째는 특수문자로 시작하는 단어들 (예 : -lit)
NODE *find_value = NULL;

void main() {

	initialize();

	char input[MAX] = { NULL };

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

	FILE *fp = fopen("shuffled_dict.txt", "r"); //shuffled_dict

	while (1) {

		fgets(input_temp, MAX, fp);

		if (feof(fp)) {
			break;
		}

		make_word_for_tree(input_temp);
	}

	fclose(fp);
}

void get_two_words_from_input(char *input) {
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
		if (command_del()) {
			printf("Deleted successfully!\n");
		}
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
	find_value = search_node(alphabet_word[result], second);

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

bool command_del() {
	int result = word_sort_analysis(second);
	find_value = search_node(alphabet_word[result], second);

	if (find_value == NULL && strcmp(first, "deleteall") == 0) {
		return false;
	}
	else if (find_value == NULL ) {
		printf("Can not find such that word - ERROR!\n");
		return false;
	}

	// 동일 단어 모두 삭제

	while (1) {
		find_value = search_node(alphabet_word[result], second);

		if (find_value == NULL) {
			break;
		}

		alphabet_n[result]--;
		find_value = del_node(alphabet_word[result], find_value);
		//free(find_value);

		find_value = NULL;
	}
	return true;
}

void command_destroy() {

	char input_temp[MAX] = { NULL }, save_the_name[MAX] = { NULL };
	int count = 0;

	strcpy(save_the_name, second);

	FILE *fp_2 = fopen(save_the_name, "r");

	while (1) {

		fgets(input_temp, MAX, fp_2);

		if (feof(fp_2)) {
			break;
		}

		input_temp[strlen(input_temp) - 1] = '\0';
		strcpy(second, input_temp);

		if (command_del()) {
			count++;
		}
	}

	fclose(fp_2);

	printf("%d words were deleted successfully!\n", count);
}

void command_view() {
	int result = word_sort_analysis(second);
	
	printf("현재 저장된 단어의 개수는 %d입니다\n\n", alphabet_n[result]);
	inorder_walk(alphabet_word[result]);
}

//

void make_tree_with_data() {
	int result = word_sort_analysis(input_analysis_data[0]);

	insert_node(make_node(),result);
	alphabet_n[result]++;
}

NODE *make_node() {
	NODE *temp = malloc(sizeof(NODE));

	temp->left = NULL, temp->right = NULL, temp->parent = NULL;

	temp->word = strdup(input_analysis_data[0]);
	temp->part = strdup(input_analysis_data[1]);
	temp->meaning = strdup(input_analysis_data[2]);

	return temp;
}

int word_sort_analysis(char *input_word) {
	if (islower(input_word[0])) {
		return input_word[0] - 97;
	}
	else if (input_word[0] - 65 < 0) {
		return 26;
	}
	return input_word[0] - 65;
}

void insert_node(NODE *z,int result) {
	NODE *y = NULL;
	NODE *x = alphabet_word[result];

	while (x != NULL) {
		y = x;

		if (strcmp(z->word, x->word) < 0) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	z->parent = y;

	if (y == NULL) {
		alphabet_word[result] = z;
	}
	else {
		if (strcmp(z->word, y->word) < 0) {
			y->left = z;
		}
		else {
			y->right = z;
		}
	}
}

NODE *search_node(NODE *x, char *k) {

	if (x == NULL) {
		return x;
	}

	if (strcmp(k, x->word) == 0) {
		return x;
	}

	if (strcmp(k, x->word) < 0) {
		return search_node(x->left, k);
	}
	return search_node(x->right, k);
}

NODE *del_node(NODE *T, NODE *z) {
	NODE *x = NULL, *y = NULL;

	if (z->left == NULL || z->right == NULL) {
		y = z;
	}
	else {
		y = find_successor(z);
	}

	if (y->left != NULL) {
		x = y->left;
	}
	else {
		x = y->right;
	}

	if (x != NULL) {
		x->parent = y->parent;
	}

	if (y->parent == NULL) {
		int result = word_sort_analysis(x->word);
		alphabet_word[result] = x;
	}
	else {
		if (y == y->parent->left) {
			y->parent->left = x;
		}
		else {
			y->parent->right = x;
		}
	}

	if (y != z) {
		strcpy(z->word, y->word);
		strcpy(z->part, y->part);
		strcpy(z->meaning, y->meaning);
	}

	return y;
}

NODE *find_successor(NODE *x) {
	if (x->right != NULL) {
		return find_min(x->right);
	}
	NODE *y = x->parent;

	while (y != NULL && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

NODE *find_min(NODE *x) {
	while (x->left != NULL) {
		x = x->left;
	}
	return x;
}

void inorder_walk(NODE *x) {
	if (x != NULL) {
		inorder_walk(x->left);
		printf("%s / %s / %s\n", x->word, x->part, x->meaning);
		inorder_walk(x->right);
	}
}

//

void make_word_for_tree(char *input_temp) {
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

	make_analysis_data(complete, i);
	i++;

	strcpy(complete, token);
	while (1) {
		if (token == NULL || token[strlen(token) - 1] == ')') {
			break;
		}

		token = strtok(NULL, " ");

		if (token == NULL) {
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
		token = strtok(NULL, " ");
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

void make_analysis_data(char *complete, int i) {
	input_analysis_data[i] = strdup(complete);
}