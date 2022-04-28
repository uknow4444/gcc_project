#include "pgm.h"
#include "words.h"

void make_dict() { // 단어장 추가
	FILE *file;
	char *filename = "dict.txt";
	char store_word[20];

	file = fopen(filename, "r");
	int count = 0;
	while (fscanf(file, "%s", store_word) != EOF) {
		strcpy(dict[count], strupr(store_word));
		count++;
	}
}

void choice_word() { // 단어 선택
	choice = rand() % 100;
	make_check_word();
}

void make_check_word() { // 정답지 만들기
	correct_word = (char*)malloc(sizeof(char)*strlen(dict[choice]) + 1);
	int i;
	for (i = 0; i < strlen(dict[choice]); i++)
		correct_word[i] = '_';
	correct_word[i] = 0;
}