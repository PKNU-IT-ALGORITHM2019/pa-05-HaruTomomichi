#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#pragma warning(disable:4996)

#define MAX 10000

extern NODE *alphabet_word[27];
extern int alphabet_n[27];

void initialize();

void get_two_words_from_input(char input[]);

bool analysis();

void command_size();

void command_find();