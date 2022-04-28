#pragma once
#include "system.h"
#include "customer.h"
#include "supplier.h"
#include "pgm.h"
#include "medicine.h"

COORD coord = { 0, 0 };
void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



//=========================welcome screen ==============
void welcome(){
	for (int w = 0; w < 1; w++) {
		system("cls");
		main_box();
		gotoxy(35, 20);
		printf("WELCOME");
		gotoxy(38, 22);
		printf("TO");
		gotoxy(28, 24);
		printf("MEDICAL");
		gotoxy(36, 24);
		printf("STORE");
		gotoxy(42, 24);
		printf("SYSTEM");
		gotoxy(52, 45);
		printf("Loading");
		gotoxy(59, 45);
		for (int q = 0; q < 6; q++) {
			printf(".");
			Sleep(300);
		}
	}
	sub_welcome();
}
void sub_welcome() { // 시작을 알리는 창
	check = 0;
	int ch;
	char ch2;
	do {
		system("cls");
		main_box();
		gotoxy(35, 12);
		printf("WELCOME");
		gotoxy(38, 14);
		printf("TO");
		gotoxy(28, 16);
		printf("MEDICAL");
		gotoxy(36, 16);
		printf("STORE");
		gotoxy(42, 16);
		printf("SYSTEM");

		gotoxy(25, 23);
		printf("Press S tart");
		gotoxy(25, 26);
		printf("Press A bout program");
		gotoxy(25, 29);
		printf("Press E xit");
		gotoxy(31, 23+(check*3));
		ch = getch();
		if (ch == 0 || ch == 0xe0) {
			ch = getch();
			switch (ch) {
			case 72: case 75:
				check--;
				if (check < 0)
					check = 2;
				break;
			case 80: case 77:
				check = (check + 1) % 3;
				break;
			}
		}
		else {
			ch2 = toupper(ch);
			switch (ch2) {
			case 13: case 32: // 엔터일 경우, 스페이스바의 경우
				switch (check) { // 현재 콘솔에 따라서 행동.
				case 0:main_menu();
					break;
				case 1:about();
					break;
				case 2:gotoxy(23, 20);
					//textcolor(4);
					printf("Do you want to exit now? Y/N :");
					Sleep(100);
					ch = (getche());
					ch = toupper(ch);
					if (ch == 'Y')
					{
						animation();
						system("cls");
						gotoxy(35, 20);
						printf(" Please wait.....");
						Sleep(2000);
						exit(0);
					}
					else
						sub_welcome();
				}
			case 'S':main_menu();
				break;
			case 'A':about();
				break;
			case 'E':
				system("cls");
				gotoxy(23, 20);
				printf("Do you want to exit now? Y/N :");
				Sleep(100);
				ch = (getche());
				ch = toupper(ch);
				if (ch == 'Y')
				{
					animation();
					system("cls");
					//textcolor(2);
					gotoxy(35, 20);
					printf(" Please wait.....");
					Sleep(2000);
					exit(0);
				}
				else
					sub_welcome();
			default://textcolor(4+BLINK);
				gotoxy(11, 34);
				printf("Plese Enter right character ONLY (S,A,E).");
				getch();
			}
		}
	} while (1);
}

//=========================main screen ==============
void main_menu() {
	check = 0;
	int ch;
	char ch2;
	system("cls");
	do	{
		gotoxy(34, 3);
		//textcolor(GREEN);
		printf("---------------");
		gotoxy(37, 4);
		printf("Main Menu.");
		gotoxy(34, 5);
		printf("---------------");
		gotoxy(25, 12);
		printf("SUPPLIER");

		gotoxy(25, 16);
		printf("CUSTOMER");

		gotoxy(25, 20);
		printf("MEDICINE");


		gotoxy(25, 24);
		printf("REPORT");


		gotoxy(25, 28);
		printf("BILL");

		gotoxy(25, 32);
		printf("EXIT");

		main_box();

		gotoxy(10, 40);
		//textcolor(RED+BLINK);
		printf("Press ");
		gotoxy(16, 40);
		//textcolor(15);
		printf("First Character for further Menu  ");

		gotoxy(25, 12 + (check * 4));
		ch = getch();
		if (ch == 0 || ch == 0xe0) {
			ch = getch();
			switch (ch) {
			case 72: case 75:
				check--;
				if (check < 0)
					check = 5;
				break;
			case 80: case 77:
				check = (check + 1) % 6;
				break;
			}
		}
		else {
			ch2 = toupper(ch);
			switch (ch2) {
			case 13: case 32: // 엔터일 경우, 스페이스바의 경우
				switch (check) { // 현재 콘솔에 따라서 행동.
				case 0:supplier();
					break;
				case 1:customer();
					break;
				case 2:medicine();
					break;
				case 3:report_menu();
					break;
				case 4:bill();
					break;
				case 5:gotoxy(23, 20);
					//textcolor(4);
					printf("Do you want to exit now? Y/N :");
					Sleep(100);
					ch = (getche());
					ch = toupper(ch);
					if (ch == 'Y')
					{
						animation();
						system("cls");
						//textcolor(2);
						gotoxy(35, 20);
						printf(" Please wait.....");
						Sleep(2000);
						exit(0);
					}
					else
						main_menu();
				default://textcolor(4+BLINK);
					gotoxy(11, 34);
					printf("Plese Enter right character ONLY (S,C,M,R,B).");
					getch();
				
				}
			case 'S':supplier();
				break;
			case 'C':customer();
				break;
			case 'M':medicine();
				break;
			case 'R':report_menu();
				break;
			case 'B':bill();
				break;
			case 'E':
				system("cls");
				gotoxy(23, 20);
				printf("Do you want to exit now? Y/N :");
				Sleep(100);
				ch = (getche());
				ch = toupper(ch);
				if (ch == 'Y')
				{
					animation();
					system("cls");
					//textcolor(2);
					gotoxy(35, 20);
					printf(" Please wait.....");
					Sleep(2000);
					exit(0);
				}
				else
					main_menu();
			default://textcolor(4+BLINK);
				gotoxy(11, 34);
				printf("Plese Enter right character ONLY (S,C,M,R,B).");
				getch();
			}
		}
	} while (ch != 'E');
}

void main_box(){
	gotoxy(1, 6);
	printf("%c", 201);
	for (i = 1; i<79; i++)	{
		gotoxy(1 + i, 6);
		printf("%c", 205);
	}

	gotoxy(80, 6);
	printf("%c", 187);
	gotoxy(1, 6);
	for (i = 5; i<35; i++)	{
		gotoxy(1, 2 + i);
		printf("%c", 186);
	}
	gotoxy(1, 37);
	printf("%c", 200);
	for (i = 1; i<79; i++)	{
		gotoxy(1 + i, 37);
		printf("%c", 205);
	}
	gotoxy(80, 37);
	printf("%c", 188);
	gotoxy(80, 6);
	for (i = 5; i<35; i++)	{
		gotoxy(80, 2 + i);
		printf("%c", 186);
	}
}

//============================================================================
void box(){
	for (i = 3; i <= 79; i++) 	//This 'FOR' loop will print a combination of
	{
		gotoxy(i, 3);    //the 79th column is reached.
		printf("%c", 219);
		gotoxy(78, 45);
		printf("%c", 219);
		gotoxy(i, 45);
		printf("%c", 219);
	}

	for (i = 3; i <= 45; i++)      //This 'FOR' loop will print asteriks 'I'
	{                       //vertically till the 3th row is reached.
		gotoxy(3, i);
		printf("%c", 219);
		gotoxy(79, i);
		printf("%c", 219);
	}
}

//============================ box for label ==========
void lbox(){
	gotoxy(25, 6);
	printf("%c", 201);
	for (i = 26; i<55; i++)
	{
		gotoxy(i, 6);
		printf("%c", 205);
	}
	gotoxy(55, 6);
	printf("%c", 187);
	gotoxy(25, 6);
	for (i = 6; i<8; i++)
	{
		gotoxy(25, i + 1);
		printf("%c", 186);
	}
	gotoxy(25, 9);
	printf("%c", 200);
	for (i = 26; i<55; i++)
	{
		gotoxy(i, 9);
		printf("%c", 205);
	}
	gotoxy(55, 9);
	printf("%c", 188);
	gotoxy(55, 6);
	for (i = 6; i<8; i++)
	{
		gotoxy(55, i + 1);
		printf("%c", 186);
	}

}

//===============프로그램 설명===============
void about()
{
	int c;
	system("cls");

	do
	{
		//   window(1,1,80,50);

		//textcolor(LIGHTGRAY);
		gotoxy(28, 4);
		//textcolor(RED+BLINK);
		printf("***** MEDICAL STORE *****");
		gotoxy(10, 8);
		printf("=> This Project Is About Medical Store ");
		gotoxy(10, 10);
		printf("=> In This Project we Can Add Medicine ,Customer,Supplier Details");
		gotoxy(10, 12);
		printf("=> We Can Modifed & Delete Existing Record");
		gotoxy(10, 14);
		printf("=> We Can Also Search Medicine ,Customer,Supplier Details");
		gotoxy(10, 16);
		printf("=> It's Helpfull For Display Stock Of Medicine ");

		printf("<<<<-Press 1 for main menu->>>>");
		c = getche();

		switch (c)      //This 'SWITCH' structure will ask the user for input from [1] to [7] and will display error on Invalid Entry.
		{
		case '1':animation(); sub_welcome();
			gotoxy(26, 24);
			puts("<<--ENTER FROM 1 PLEASE-->>");	//This message will only print on INVALID ENTRY and Will ask again for input.
			getch();
		}

	} while (c != '1');
}

//=========================Time & Date ====================
int t(){
	//struct date d;
	//struct time t;

	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	//getdate(&d);
	//gettime(&t);
	gotoxy(55, 46);
	printf("Date: %d-%d-%d ", now->tm_mday, now->tm_mon, now->tm_year);
	gotoxy(55, 48);
	printf("Time: %d:%d:%d", now->tm_hour, now->tm_min, now->tm_sec);
	return 0;
}

//=======================Animation ==========================
void animation(){
	for (i = 45; i >= 1; i--)
	{
		Sleep(30);
		gotoxy(1, i);
		//clreol();
	}
	for (i = 1; i <= 20; i++)
	{
		//clreol();
		Sleep(40);
		gotoxy(1, i);
	}
}


//=========================== validation =========================
void ventry(char t[], int code){
	int i = 0;
	if (code == 0)	{
		while ((t[i] = getch()) != '\r' && i<30)
			if ((t[i] >= 97 && t[i] <= 122) || (t[i] >= 65 && t[i] <= 90) || t[i] == 32 || t[i] == '_')
			{
				printf("%c", t[i]);
				i++;
			}
			else if (t[i] == 8 && i>0)
			{
				printf("%c%c%c", 8, 32, 8);
				i--;              //Length counter is decremented.

			}
	}
	else if (code == 1)
	{
		while ((t[i] = getch()) != '\r' && i<10)
			if ((t[i] >= 48 && t[i] <= 57) || t[i] == 46 || t[i] == '-')
			{
				printf("%c", t[i]);
				i++;
			}
			else if (t[i] == 8 && i>0)
			{
				printf("%c%c%c", 8, 32, 8);
				i--;              //Length counter is decremented.

			}
	}
	else if (code == 2)
	{
		while ((t[i] = getch()) != '\r' && i<30)
			if ((t[i] >= 97 && t[i] <= 122) || (t[i] >= 65 && t[i] <= 90) || (t[i] >= 48 && t[i] <= 57) || t[i] == 32 || t[i] == 8 || t[i] == '@' || t[i] == '.')
			{
				printf("%c", t[i]);
				i++;
			}
			else if (t[i] == 8 && i>0)
			{
				printf("%c%c%c", 8, 32, 8);
				i--;              //Length counter is decremented.
			}
	}
	t[i] = '\0';
}


//========================for bill =============================
void bill()
{
	//struct date d;
	time_t td = time(0);   // get time now
	struct tm * now = localtime(&td);

	FILE *ptrbill;
	char id[6];
	int j = 1, d1, m, y, k;
	float netamt = 0.0;
	//getdate(&d);
	d1 = now->tm_mday;
	m = now->tm_mon;
	y = now->tm_year;
	system("cls");
	ptrbill = fopen("dbbill.dat", "r");
	gotoxy(13, 4);
	printf("Enter bill no : ");
	scanf("%s", &id);
	system("cls");
	gotoxy(25, 3);
	////textcolor(YELLOW+BLINK);
	// printf("***** CareWell Medico *****");
	box();
	gotoxy(7, 7);
	printf("Bill No: ");
	printf(" %s", id);
	gotoxy(7, 9);
	printf("Customer Name: ");
	gotoxy(50, 7);
	printf("Date : ");
	printf("%d-%d-%d", d1, m, y);
	gotoxy(7, 12);
	printf("Sr.No   Medicine Name       Qty          Rate         Total ");
	gotoxy(6, 14);
	printf("---------------------------------------------------------------------");

	i = 15;
	while (fscanf(ptrbill, "%s %s %s %d %f %f %d %d %d", bil.billno, bil.cname, bil.mediname, &bil.medi_qty, &bil.medi_rate, &bil.total, &bil.day, &bil.month, &bil.year) != EOF)
	{

		do
		{
			if (strcmp(id, bil.billno) == 0)
			{
				gotoxy(7, i);
				printf(" %d", j);
				gotoxy(14, i);
				printf(" %s", bil.mediname);
				gotoxy(22, 9);
				printf(" %s", bil.cname);
				gotoxy(35, i);
				printf(" %d", bil.medi_qty);
				gotoxy(47, i);
				printf(" %.2f", bil.medi_rate);
				gotoxy(60, i);
				printf(" %.2f", bil.total);
				netamt = netamt + bil.total;
				i++;
				j++;
				gotoxy(35, 32);
				printf("                                ");
				gotoxy(20, 50);
				//textcolor(YELLOW+BLINK);
				printf("Press Any key to go to  MENU ...........");

				//	break;
			}


		} while (feof(ptrbill));

	}


	gotoxy(6, 35);
	printf("---------------------------------------------------------------------");
	gotoxy(50, 37);
	printf("Net Amount : ");
	printf("%.2f", netamt);

	fclose(ptrbill);
	getch();
}

