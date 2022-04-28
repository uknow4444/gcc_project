#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h> // 헤더 중복
#include <ctype.h>
#include <time.h> // 헤더 중복
#include <windows.h>
#include <process.h>

// 아스키코드 키 값
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length; // 총 몸통길이
int bend_no; // 꺽이는 지점
int len; // 현재 출력된 길이
char key;

void record();
void load();
int life;
void Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x, int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();

struct coordinate {
	int x;
	int y;
	int direction;
};
typedef struct coordinate coordinate; // 위의 구조체 정의와 합쳐도 될 듯

coordinate head, bend[500], food, body[30];
// 머리,꺽인 좌표 저장,밥 좌표, 몸통좌표 

int main()
{
	char key; // 전역변수와 같음. 지워도 문제 없을 듯

	Print();
	system("cls");
	load();
	length = 5; // 초기 길이
	head.x = 25;
	head.y = 20;
	head.direction = RIGHT;

	Boarder();
	Food(); //to generate food coordinates initially
	life = 3; //number of extra lives
	bend[0] = head;
	Move();   //initialing initial bend coordinate

	return 0;
}

void Move()
{
	int a, i;

	do {
		Food();
		fflush(stdin); // 2017버전부터 동작안되는데 일단 없어도 정상실행(?)

		len = 0;

		for (i = 0; i<30; i++)
		{
			body[i].x = 0;
			body[i].y = 0;

			if (i == length)
				break;
		}

		Delay(length);

		Boarder();
		if (head.direction == RIGHT)
			Right();
		else if (head.direction == LEFT)
			Left();
		else if (head.direction == DOWN)
			Down();
		else if (head.direction == UP)
			Up();
		ExitGame();
	} while (!kbhit()); // 사용자가 키를 입력할 때까지 반복

	a = getch(); // 입력값 a에 저장

	if (a == 27) // 27은 esc 아스키 코드값 이것도 define 해주는 것이 좋을 듯.
	{
		system("cls"); // 화면지우기
		exit(0);
	}
	key = getch(); // 입력값 key에 저장...?  a를 지워도 될 듯
	
	//반대방향으로 진행을 못하도록 막는 if 문
	if ((key == RIGHT && head.direction != LEFT && head.direction != RIGHT) || (key == LEFT && head.direction != RIGHT && head.direction != LEFT) || (key == UP && head.direction != DOWN && head.direction != UP) || (key == DOWN && head.direction != UP && head.direction != DOWN))
	{
		bend_no++;
		bend[bend_no] = head;
		head.direction = key;
		if (key == UP)
			head.y--;
		if (key == DOWN)
			head.y++;
		if (key == RIGHT)
			head.x++;
		if (key == LEFT)
			head.x--;
		Move(); // 재귀함수
	}
	else if (key == 27) // esc
	{
		system("cls");
		exit(0); // 창 종료
	}
	else // 현재 상태 유지
	{
		printf("\a");
		Move(); // 재귀함수
	}
}

void gotoxy(int x, int y) // 출력좌표를 설정하는 함수, 커서 위치 설정
{
	COORD coord; // 커서 좌표계 선언
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // 커서 좌표 설정
}

void GotoXY(int x, int y) // 출력좌표를 설정하는 함수 위랑 차이가??
{
	HANDLE a; // 핸들 선언
	COORD b; // 커서 좌표계 선언
	fflush(stdout);
	b.X = x;
	b.Y = y;
	a = GetStdHandle(STD_OUTPUT_HANDLE); // 표준핸들러... 입력
	SetConsoleCursorPosition(a, b); // 위 문구랑 합쳐도 될 듯
}

void load() { // 로딩하는 척 일정시간 대기시키는 함수...?
	int row, col, r, c, q;
	gotoxy(36, 14);
	printf("loading...");
	gotoxy(30, 15);
	for (r = 1; r <= 20; r++) {
		for (q = 0; q <= 100000000; q++);//to display the character slowly
		printf("%c", 177);
	}
	getch();
}

void Down() // 아래로 내려가는 걸 출력하는 함수
{
	int i;
	for (i = 0; i <= (head.y - bend[bend_no].y) && len<length; i++)
	{
		GotoXY(head.x, head.y - i);
		{
			if (len == 0)
				printf("v");
			else
				printf("*");
		}
		body[len].x = head.x;
		body[len].y = head.y - i;
		len++;
	}
	Bend();
	if (!kbhit())
		head.y++;
}


/// 이건 딜레이 주는 함수인데... 너무한....
void Delay(long double k)
{
	Score();
	long double i;
	for (i = 0; i <= (10000000); i++); //야ㅏㅏㅏㅏㅏ
	//sleep 함수를 사용할 생각을 해봅시다.
}
void ExitGame() // 게임 종료 시
{
	int i, check = 0;
	for (i = 4; i<length; i++)   //starts with 4 because it needs minimum 4 element to touch its own body
	{
		if (body[0].x == body[i].x&&body[0].y == body[i].y)
		{
			check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
		}
		if (i == length || check != 0)
			break;
	}
	if (head.x <= 10 || head.x >= 70 || head.y <= 10 || head.y >= 30 || check != 0)
	{
		life--;
		if (life >= 0)
		{
			head.x = 25;
			head.y = 20;
			bend_no = 0;
			head.direction = RIGHT;
			Move();
		}
		else
		{
			system("cls");
			printf("All lives completed\nBetter Luck Next Time!!!\nPress any key to quit the game\n");
			record();
			exit(0);
		}
	}
}
void Food()
{
	if (head.x == food.x&&head.y == food.y) // 밥을 먹었을 경우
	{
		length++; // 길이증가
		time_t a;
		a = time(0);
		srand(a); // 시드값 랜덤 주는 함수 문구 합쳐도 될 듯
		food.x = rand() % 70; // 먹이 위치 변경
		if (food.x <= 10)
			food.x += 11;
		food.y = rand() % 30; // 먹이 위치 변경
		if (food.y <= 10)
			food.y += 11;
	}
	else if (food.x == 0)/*to create food for the first time coz global variable are initialized with 0*/
	{ // 처음에 먹이를 만들 경우.
		food.x = rand() % 70;
		if (food.x <= 10)
			food.x += 11;
		food.y = rand() % 30;
		if (food.y <= 10)
			food.y += 11;
	}
}

void Left() // 왼쪽으로 가는거 출력함수
{
	int i;
	for (i = 0; i <= (bend[bend_no].x - head.x) && len<length; i++)
	{
		GotoXY((head.x + i), head.y);
		{
			if (len == 0)
				printf("<");
			else
				printf("*");
		}
		body[len].x = head.x + i;
		body[len].y = head.y;
		len++;
	}
	Bend();
	if (!kbhit())
		head.x--;

}

void Right() // 오른쪽으로 가는거 출력 함수
{
	int i;
	for (i = 0; i <= (head.x - bend[bend_no].x) && len<length; i++)
	{
		//GotoXY((head.x-i),head.y);
		body[len].x = head.x - i;
		body[len].y = head.y;
		GotoXY(body[len].x, body[len].y);
		{
			if (len == 0)
				printf(">");
			else
				printf("*");
		}
		/*body[len].x=head.x-i;
		body[len].y=head.y;*/
		len++;
	}
	Bend();
	if (!kbhit())
		head.x++;
}

void Bend() // 굽어지는 것을 출력하는 함수
{
	int i, j, diff;
	for (i = bend_no; i >= 0 && len<length; i--)
	{
		if (bend[i].x == bend[i - 1].x)
		{
			diff = bend[i].y - bend[i - 1].y;
			if (diff<0)
				for (j = 1; j <= (-diff); j++)
				{
					body[len].x = bend[i].x;
					body[len].y = bend[i].y + j;
					GotoXY(body[len].x, body[len].y);
					printf("*");
					len++;
					if (len == length)
						break;
				}
			else if (diff>0)
				for (j = 1; j <= diff; j++)
				{
					/*GotoXY(bend[i].x,(bend[i].y-j));
					printf("*");*/
					body[len].x = bend[i].x;
					body[len].y = bend[i].y - j;
					GotoXY(body[len].x, body[len].y);
					printf("*");
					len++;
					if (len == length)
						break;
				}
		}
		else if (bend[i].y == bend[i - 1].y)
		{
			diff = bend[i].x - bend[i - 1].x;
			if (diff<0)
				for (j = 1; j <= (-diff) && len<length; j++)
				{
					/*GotoXY((bend[i].x+j),bend[i].y);
					printf("*");*/
					body[len].x = bend[i].x + j;
					body[len].y = bend[i].y;
					GotoXY(body[len].x, body[len].y);
					printf("*");
					len++;
					if (len == length)
						break;
				}
			else if (diff>0)
				for (j = 1; j <= diff && len<length; j++)
				{
					/*GotoXY((bend[i].x-j),bend[i].y);
					printf("*");*/
					body[len].x = bend[i].x - j;
					body[len].y = bend[i].y;
					GotoXY(body[len].x, body[len].y);
					printf("*");
					len++;
					if (len == length)
						break;
				}
		}
	}
}

void Boarder() // 화면 출력 함수
{
	system("cls"); // 화면 지우기
	int i;
	GotoXY(food.x, food.y);   /*displaying food*/
	printf("F"); // 먹이 출력
	for (i = 10; i<71; i++) // 가로출력
	{
		GotoXY(i, 10);
		printf("!");
		GotoXY(i, 30);
		printf("!");
	}
	for (i = 10; i<31; i++) // 새로출력
	{
		GotoXY(10, i);
		printf("!");
		GotoXY(70, i);
		printf("!");
	}
}

void Print() // 게임 안내판 출력
{
	//GotoXY(10,12);
	printf("\tWelcome to the mini Snake game.(press any key to continue)\n");
	getch();
	system("cls");
	printf("\tGame instructions:\n");
	printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> YOu can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc. \n");
	printf("\n\nPress any key to play game...");
	if (getch() == 27)  // esc 누를 시 
		exit(0); // 화면 종료
}

void record() { // 게임 결과 기록
	char plname[20], nplname[20], cha, c;
	int i, j, px;
	FILE *info;
	info = fopen("record.txt", "a+");
	getch();
	system("cls");
	printf("Enter your name\n");
	scanf("%[^\n]", plname);
	//************************
	for (j = 0; plname[j] != '\0'; j++) { //to convert the first letter after space to capital
		nplname[0] = toupper(plname[0]);
		if (plname[j - 1] == ' ') {
			nplname[j] = toupper(plname[j]);
			nplname[j - 1] = plname[j - 1];
		}
		else nplname[j] = plname[j];
	}
	nplname[j] = '\0';
	//*****************************
	//sdfprintf(info,"\t\t\tPlayers List\n");
	fprintf(info, "Player Name :%s\n", nplname);
	//for date and time

	time_t mytime;
	mytime = time(NULL);
	fprintf(info, "Played Date:%s", ctime(&mytime));
	//**************************
	fprintf(info, "Score:%d\n", px = Scoreonly());//call score to display score
												  //fprintf(info,"\nLevel:%d\n",10);//call level to display level
	for (i = 0; i <= 50; i++)
		fprintf(info, "%c", '_');
	fprintf(info, "\n");
	fclose(info);
	printf("wanna see past records press 'y'\n");
	cha = getch();
	system("cls");
	if (cha == 'y') {
		info = fopen("record.txt", "r");
		do {
			putchar(c = getc(info));
		} while (c != EOF);
	}
	fclose(info);
}

int Score()  // 점수 출력 및 계산 함수
{
	int score;
	GotoXY(20, 8);
	score = length - 5;
	printf("SCORE : %d", (length - 5));
	score = length - 5;
	GotoXY(50, 8);
	printf("Life : %d", life);
	return score;
}

int Scoreonly() // 결과 기록할 때 사용하려고 score 값만 확인해서 반환해주는 함수
{
	int score = Score();
	system("cls");
	return score;
}

void Up() // 위로 올라가는 함수
{
	int i;
	for (i = 0; i <= (bend[bend_no].y - head.y) && len<length; i++)
	{
		GotoXY(head.x, head.y + i);
		{
			if (len == 0)
				printf("^");
			else
				printf("*");
		}
		body[len].x = head.x;
		body[len].y = head.y + i;
		len++;
	}
	Bend();
	if (!kbhit())
		head.y--;
}