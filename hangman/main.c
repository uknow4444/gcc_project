#include "pgm.h"
#include "words.h"
#include "hangman.h"

int main() {
	srand((unsigned)time(NULL));

	make_dict(); // �ܾ��� �����
	new_game(); // ������
	while (game_type != END) { // ���� ����ñ���
		hangman(); // ���� ����
	}
	end_display(); // ���� ���
	return 0;
}