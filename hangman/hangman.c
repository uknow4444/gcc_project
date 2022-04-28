#include "pgm.h"
#include "words.h"
#include "hangman.h"

double play_count = 0;
double win_count = 0;

char in;
int check[26];

char hangman(){
	display_m(); // ���� ���
	char_check(); // ���� �Է¹ޱ�
	hangman_process(); // ó��
	if (game_type != END) // ������ ������ �ʾҴٸ�
		hangman_check(); // ���� ���� Ȯ��
}

void char_check() { // ���� �Է¹ޱ�
	scanf(" %c",&in);
	/*
	in = getchar();
	while (getchar() != '\n'); // ! ��������� ! vs2015���� fflush ���� ����
	*/
	if (game_type == PLAY) { // �ߺ� ���� üũ
		if (check[in - 'A']) {
			check[in - 'A'] = false;
			correct_word_check = false;
		}
		else {
			printf("�̹� �Էµ� �����Դϴ�.\n�ٸ� ���ڸ� �Է����ּ���. : ");
			char_check(); // ����Լ�
		}
	}
}

void hangman_process() { // ������ ���¿� ���� ó��.
	int i;
	switch (game_type) {
	case PLAY:
		for (i = 0; i < strlen(dict[choice]); i++)
			if (dict[choice][i] == in) {
				correct_word[i] = in;
				correct_word_check = true;
			}
		display_correct(in);
		break;
	case WIN:	case OVER: // ������ ������ ��
		if (in == 'Y') { // ����ڰ� ������� ���ϸ�
			free(correct_word); // ��������ܾ� �Ҵ� ����
			new_game(); // �� ����
		}
		else
			game_type = END;
		break;
	}
}

void hangman_check() { // ���ӻ��¸� üũ���ִ� �Լ�
	int hang_check = true;
	for (int i = 0; i < strlen(dict[choice]);i++)
		if(correct_word[i] == '_')
			hang_check = false;
	if (hang_check) {
		game_type = WIN;
		win_count += 1;
	}
	else if (guess_count == 0)
		game_type = OVER;
}

void new_game() { // ������ �����
	choice_word(); // �ܾ� ����
	game_type = PLAY; // ���� ���� ����
	for (int i = 0; i < 26; i++) // �ߺ����� üũ �迭 �ʱ�ȭ
		check[i] = true;
	play_count += 1; // �÷��� �� ����
	guess_count = 8; // ���� �� �ʱ�ȭ
}