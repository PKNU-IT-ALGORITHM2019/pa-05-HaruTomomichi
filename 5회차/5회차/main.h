#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#pragma warning(disable:4996)

#define MAX 100000

typedef struct node {
	struct node *parent;
	struct node *left;
	struct node *right;
	char *word, *part, *meaning;
}NODE;

void initialize();

void get_two_words_from_input(char *input);

bool analysis();

void command_size();

void command_find();

void command_add();

void command_add_assist(int i);

bool command_del();

void command_destroy();

void command_destroy_assist();

void command_view();

//

void make_tree_with_data();

NODE *make_node();

int word_sort_analysis(char *input_word);

void insert_node(NODE *z, int result);

NODE *search_node(NODE *x, char *k);

NODE *del_node(NODE *T, NODE *z);

NODE *find_successor(NODE *x);

NODE *find_min(NODE *x);

void inorder_walk(NODE *x);

//

char *input_analysis_data[3]; // 분석 결과를 저장하는 데이터 워드 배열

void make_word_for_tree(char *input_temp);

void make_analysis_data(char *complete, int i);