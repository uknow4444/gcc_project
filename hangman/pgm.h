#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define true 1
#define false 0

typedef enum { PLAY, OVER, WIN, END }; // ���� ���¸� ���������� ����
int game_type; // ���� ���¸� ������ ����

char dict[100][20]; // 100���� �ܾ ������ 2���� �迭
char *correct_word; // ���� �ܾ� ���¸� ��Ÿ�� ����
int correct_word_check; // ���ڸ� ������� üũ���� ����
int choice; // �ܾ �������ִ� ����
int guess_count; // ���� ���� Ƚ���� ī��Ʈ���ִ� ����
