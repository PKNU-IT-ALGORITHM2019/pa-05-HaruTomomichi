#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#pragma warning(disable:4996)

#define MAX 100000

void initialize();

void get_two_words_from_input(char input[]);

bool analysis();

void command_size();

void command_find();

void command_add();

void command_add_assist(int i);

void command_del();

void command_destroy();

void command_destroy_assist();

void command_view();