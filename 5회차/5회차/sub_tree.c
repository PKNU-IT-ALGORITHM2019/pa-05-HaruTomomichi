#include "main.h"
#include "sub_word.h"
#include "sub_tree.h"

// 26개의 헤드 배열에 1000개의 노드 구조체를 다시 선언하기에는 현재 곤란하므로, 단순 연결리스트로 구현한다

NODE *alphabet_word[26] = { NULL }; // 26개의 헤드를 저장하는 공간

int alphabet_n[26] = { 0 }; // 각 단어가 저장되는 회수

void make_tree_with_data() {
	int result = word_sort_analysis(input_analysis_data[0]);

	if (alphabet_n[result] == 0) {
		alphabet_word[result] = make_node();
		alphabet_n[result]++;
	}
	else {
		insert_node(alphabet_word[result], make_node());
		alphabet_n[result]++;
	}
}

int word_sort_analysis(char *input_word) {
	if (islower(input_word[0])) {
		return input_word[0] - 97;
	}
	return input_word[0] - 65;
}

NODE *make_node() {
	NODE *temp = malloc(sizeof(NODE));

	temp->left = NULL, temp->right = NULL, temp->parent = NULL;

	temp->word = strdup(input_analysis_data[0]);
	temp->part = strdup(input_analysis_data[1]);
	temp->meaning = strdup(input_analysis_data[2]);

	return temp;
}

void insert_node(NODE *T, NODE *z) {
	NODE *y = NULL;
	NODE *x = T; // T = head

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

	if (strcmp(z->word, y->word)<0) {
		y->left = z;
	}
	else {
		y->right = z;
	}
}