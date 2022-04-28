#include "pgm.h"
#include "display.h"

extern double play_count;
extern double win_count;

void display_m() { // 게임상태에 따른 출력
	switch (game_type) {
	case PLAY : 
		display_play(); // 게임중일 때 출력하는 화면
		break;
	case WIN :
		printf("축하합니다! 정답입니다!\n정답 : %s\n", dict[choice]);
		printf("게임을 재시작하시겠습니까? (Y/N) : ");
		break;
	case OVER :
		display_hangman();
		printf("게임에서 패배하였습니다.\n정답 : %s\n", dict[choice]);
		printf("게임을 재시작하시겠습니까? (Y/N) : ");
		break;
	}
}

void display_play() {
	//행맨 그리기
	display_hangman();
	// 현재 단어상태 보여주기
	printf("현재 단어 상태 : %s\n", correct_word);
	printf("남은 생명 : %d\n", guess_count);
	printf("단어를 예측해주세요. : ");
}

void display_correct(char in) { // 사용자가 입력한 문자에 대한 결과를 출력하는 함수
	if (correct_word_check)
		printf("예측에 성공했습니다!\n");
	else {
		printf("' %c ' 는 단어에 없습니다.\n", in);
		guess_count--;
	}
}

void display_hangman() { // 행맨을 그리는 함수
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

void end_display() { // 종료시 출력되는 display
	printf("게임이 종료되었습니다.\n총 게임수 : %.0lf\n당신의 성공률 : %.0lf%%\n", play_count, win_count / play_count * 100);
}