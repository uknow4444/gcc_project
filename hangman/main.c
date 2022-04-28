#include "pgm.h"
#include "words.h"
#include "hangman.h"

int main() {
	srand((unsigned)time(NULL));

	make_dict(); // 단어장 만들기
	new_game(); // 새게임
	while (game_type != END) { // 게임 종료시까지
		hangman(); // 게임 실행
	}
	end_display(); // 최종 출력
	return 0;
}