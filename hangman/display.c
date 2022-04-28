#include "pgm.h"
#include "display.h"

extern double play_count;
extern double win_count;

void display_m() { // ���ӻ��¿� ���� ���
	switch (game_type) {
	case PLAY : 
		display_play(); // �������� �� ����ϴ� ȭ��
		break;
	case WIN :
		printf("�����մϴ�! �����Դϴ�!\n���� : %s\n", dict[choice]);
		printf("������ ������Ͻðڽ��ϱ�? (Y/N) : ");
		break;
	case OVER :
		display_hangman();
		printf("���ӿ��� �й��Ͽ����ϴ�.\n���� : %s\n", dict[choice]);
		printf("������ ������Ͻðڽ��ϱ�? (Y/N) : ");
		break;
	}
}

void display_play() {
	//��� �׸���
	display_hangman();
	// ���� �ܾ���� �����ֱ�
	printf("���� �ܾ� ���� : %s\n", correct_word);
	printf("���� ���� : %d\n", guess_count);
	printf("�ܾ �������ּ���. : ");
}

void display_correct(char in) { // ����ڰ� �Է��� ���ڿ� ���� ����� ����ϴ� �Լ�
	if (correct_word_check)
		printf("������ �����߽��ϴ�!\n");
	else {
		printf("' %c ' �� �ܾ �����ϴ�.\n", in);
		guess_count--;
	}
}

void display_hangman() { // ����� �׸��� �Լ�
	int hangman[8][7] = { 0,2,1,1,1,1,0,
		0,2,0,0,0,0,0,
		0,2,0,0,0,0,0,
		0,2,0,0,0,0,0,
		0,2,0,0,0,0,0,
		0,2,0,0,0,0,0,
		0,2,0,0,0,0,0,
		1,1,1,1,1,1,1 };
	if (guess_count < 8)
		hangman[1][5] = '|';
	if (guess_count < 7)
		hangman[2][5] = '|';
	if (guess_count < 6)
		hangman[3][5] = 'O';
	if (guess_count < 5)
		hangman[4][5] = 'T';
	if (guess_count < 4)
		hangman[4][4] = '(';
	if (guess_count < 3)
		hangman[4][6] = ')';
	if (guess_count < 2)
		hangman[5][4] = '/';
	if (guess_count < 1)
		hangman[5][5] = '|';
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {
			if (hangman[i][j] == 0) {
				printf("  ");
			}
			else if (hangman[i][j] == 1)
				printf("--");
			else if (hangman[i][j] == 2)
				printf("|");
			else {
				if (hangman[i][j] == '(' || hangman[i][j] == '/')
					printf(" ");
				printf("%c", hangman[i][j]);
			}
		}
		printf("\n");
	}

}

void end_display() { // ����� ��µǴ� display
	printf("������ ����Ǿ����ϴ�.\n�� ���Ӽ� : %.0lf\n����� ������ : %.0lf%%\n", play_count, win_count / play_count * 100);
}