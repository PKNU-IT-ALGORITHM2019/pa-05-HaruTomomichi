#include "main.h"
#include "sub_word.h"
#include "sub_tree.h"

extern char *input_analysis_data[3]; // 분석 결과를 저장하는 데이터 워드 배열
int i = 0;

void make_word_for_tree(char input_temp[]) {

	char *token = NULL, complete[MAX] = { NULL };




	// 여기에서 char 배열을 트리 배열에 넘겨준다

	i = 0;
}

void make_analysis_data(char complete[]) {
	input_analysis_data[i] = malloc(sizeof(complete));
	strcpy(input_analysis_data, complete);
	i++;
}