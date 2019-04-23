#pragma once

typedef struct node {
	struct node *parent;
	struct node *left;
	struct node *right;
	char *word, *part, *meaning;
}NODE;

void make_tree_with_data();

int word_sort_analysis(char *input_word);

NODE *make_node();

void insert_node(NODE *T, NODE *z);

NODE *search_node(NODE *x, char k[]);