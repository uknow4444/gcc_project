#pragma once

void gotoxy(int x, int y);
//function for welcome & main menu
void welcome(); // �ε�â
void sub_welcome(); // welcome ȯ��â �� �ε� �� ���â
void main_menu(); // ���� �޴� â
//function for all box
void main_box(); // ���� �ڽ�â
void lbox(); // ����Ʈ ��½� â

//function for about menu
void about(); // ���α׷� ����

void ventry(char t[], int code); // ���� �ð� ����ֱ� (���θ޴�)

int t();// �ð�

void animation(); // ������ �Լ� + �ִϸ��̼�ó�� �ܼ��� ������.

//function for bill slip
void bill(); // ������ ��ȣ�� ã�� �Լ�.
