#pragma once

void gotoxy(int x, int y);
//function for welcome & main menu
void welcome(); // 로딩창
void sub_welcome(); // welcome 환영창 및 로딩 후 대기창
void main_menu(); // 메인 메뉴 창
//function for all box
void main_box(); // 메인 박스창
void lbox(); // 리스트 출력시 창

//function for about menu
void about(); // 프로그램 설명

void ventry(char t[], int code); // 현재 시각 띄워주기 (메인메뉴)

int t();// 시간

void animation(); // 딜레이 함수 + 애니메이션처럼 콘솔을 움직임.

//function for bill slip
void bill(); // 영수증 번호로 찾는 함수.
