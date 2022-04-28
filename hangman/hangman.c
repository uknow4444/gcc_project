#include "pgm.h"
#include "words.h"
#include "hangman.h"

double play_count = 0;
double win_count = 0;

char in;
int check[26];

char hangman(){
	display_m(); // 메인 출력
	char_check(); // 글자 입력받기
	hangman_process(); // 처리
	if (game_type != END) // 게임이 끝나지 않았다면
		hangman_check(); // 게임 상태 확인
}

void char_check() { // 글자 입력받기
	scanf(" %c",&in);
	/*
	in = getchar();
	while (getchar() != '\n'); // ! 버퍼지우기 ! vs2015부터 fflush 지원 안함
	*/
	if (game_type == PLAY) { // 중복 문자 체크
		if (check[in - 'A']) {
			check[in - 'A'] = false;
			correct_word_check = false;
		}
		else {
			printf("이미 입력된 문자입니다.\n다른 문자를 입력해주세요. : ");
			char_check(); // 재귀함수
		}
	}
}

void hangman_process() { // 게임의 상태에 따른 처리.
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
	case WIN:	case OVER: // 게임이 끝났을 때
		if (in == 'Y') { // 사용자가 재시작을 원하면
			free(correct_word); // 정답저장단어 할당 해제
			new_game(); // 새 게임
		}
		else
			game_type = END;
		break;
	}
}

void hangman_check() { // 게임상태를 체크해주는 함수
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

void new_game() { // 새게임 만들기
	choice_word(); // 단어 선택
	game_type = PLAY; // 게임 상태 변경
	for (int i = 0; i < 26; i++) // 중복글자 체크 배열 초기화
		check[i] = true;
	play_count += 1; // 플레이 수 증가
	guess_count = 8; // 추측 수 초기화
}