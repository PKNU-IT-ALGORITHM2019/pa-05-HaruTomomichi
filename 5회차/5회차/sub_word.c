#include "main.h"
#include "sub_word.h"
#include "sub_tree.h"

extern char *input_analysis_data[3]; // �м� ����� �����ϴ� ������ ���� �迭
int i = 0;

void make_word_for_tree(char input_temp[]) {

	char *token = NULL, complete[MAX] = { NULL };




	// ���⿡�� char �迭�� Ʈ�� �迭�� �Ѱ��ش�

	i = 0;
}

void make_analysis_data(char complete[]) {
	input_analysis_data[i] = malloc(sizeof(complete));
	strcpy(input_analysis_data, complete);
	i++;
}