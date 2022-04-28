#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define true 1
#define false 0

typedef enum { PLAY, OVER, WIN, END }; // 게임 상태를 열거형으로 설정
int game_type; // 게임 상태를 구분할 변수

char dict[100][20]; // 100개의 단어를 저장할 2차원 배열
char *correct_word; // 현재 단어 상태를 나타낼 변수
int correct_word_check; // 글자를 맞췄는지 체크해줄 변수
int choice; // 단어를 선택해주는 변수
int guess_count; // 남은 추측 횟수를 카운트해주는 변수
