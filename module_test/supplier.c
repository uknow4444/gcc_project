#pragma once
#include "system.h"
#include "customer.h"
#include "supplier.h"
#include "pgm.h"
#include "medicine.h"


//=========================For supplier ===========================
void supplier()
{
	check = 0;
	int ch;
	char ch2;
	do	{
		system("cls");
		gotoxy(34, 3);
		//textcolor(GREEN);
		printf("----------------");
		gotoxy(35, 4);
		//textcolor(GREEN);
		printf("Supplier MENU");
		gotoxy(34, 5);
		//textcolor(GREEN);
		printf("----------------");

		gotoxy(25, 11);
		printf("Add New Supplier");

		gotoxy(25, 15);
		printf("Update Supplier");

		gotoxy(25, 19);
		printf("Search Supplier");

		gotoxy(25, 23);
		printf("List of Existing Supplier");

		gotoxy(25, 27);
		printf("Main Menu");

		main_box();

		gotoxy(10, 40);
		printf("Press First Character for further Operation ");

		gotoxy(25, 11 + (check * 4));
		ch = getch();
		if (ch == 0 || ch == 0xe0) {
			ch = getch();
			switch (ch) {
			case 72: case 75:
				check--;
				if (check < 0)
					check = 4;
				break;
			case 80: case 77:
				check = (check + 1) % 5;
				break;
			}
		}
		else {
			ch2 = toupper(ch);
			switch (ch2) {
			case 13: case 32: // 엔터일 경우, 스페이스바의 경우
				switch (check) { // 현재 콘솔에 따라서 행동.
				case 0:animation();
					supp_entry();
					break;
				case 1:animation();
					sup_update();
					break;
				case 2:animation();
					search();
					break;
				case 3:animation();
					supp_list();
					break;
				case 4:main_menu();
					break;
				}
			case 'A':animation();
				supp_entry();
				break;
			case 'U':animation();
				sup_update();
				break;
			case 'L':animation();
				supp_list();
				break;
			case 'S':search();
				break;
			case 'M':main_menu();
				break;
			default://textcolor(4+BLINK);
				gotoxy(11, 34);
				printf("Plese Enter right character ONLY (A,L,U,S,M).");
				getch();
			}
		}
	} while (ch != 'M');

}


//========FOR SUPPLIERS ENTRY=================
void supp_entry()
{
	int id;
	char ch;
	FILE *fp;
	system("cls");

	fp = fopen("supplier.dat", "a");
	if (fp == NULL)
	{
		printf("\n Can not open file!!");
		exit(0);
	}
	system("cls");
	ch = 'y';
	while (ch == 'y')
	{
		system("cls");
		//textcolor(14);
		t();
		box();
		lbox();
		gotoxy(30, 8);
		printf(" SUPPLIER ENTRY ");
		gotoxy(8, 13);
		//		//flushall();
		temp1.supp_id = getsupp_id();
		printf("SUPPLIER ID : %d ", temp1.supp_id);
		//ventry(temp1.supp_id,1);
		//flushall();
		gotoxy(39, 13);
		printf("SUPPLIER NAME : ");
		gotoxy(8, 18);
		printf("CITY        : ");
		gotoxy(39, 18);
		printf("CONTACT NO.   : ");
		gotoxy(8, 23);
		printf("EMAIL ID    : ");

		gotoxy(55, 13);
		//flushall();
		ventry(temp1.supp_name, 0);
		gotoxy(22, 18);
		ventry(temp1.city, 0);
		//flushall();
		gotoxy(55, 18);
		ventry(temp1.mob_no, 1);
		//flushall();
		gotoxy(22, 23);
		gets(temp1.email);
		//flushall();

		gotoxy(20, 30);
		//textcolor(RED+BLINK);
		printf("S");
		//textcolor(WHITE);
		gotoxy(21, 30);
		printf("ave");
		gotoxy(28, 30);
		//textcolor(RED+BLINK);
		printf("C");
		//textcolor(WHITE);
		gotoxy(29, 30);
		printf("ancel");
		gotoxy(18, 36);
		printf("Press First charecter for the operation : ");
		ch = getch();
		if (ch == 's' || ch == 'S')
		{
			fprintf(fp, "%d %s %s %s %s\n\n", temp1.supp_id, temp1.supp_name, temp1.mob_no, temp1.city, temp1.email);
			fprintf(fp, "\n");
			//flushall();
			system("cls");
			gotoxy(20, 20);
			printf("Supplier Added successfully!!!!!");
			//textcolor(10);
			gotoxy(20, 25);
			printf("More entries  [y/n]");
			ch = getche();
		}
	}
	fclose(fp);

}
//=========FOR SUPPLIER DISPLAY LIST ==========
void supp_list()
{
	char ch;
	int j;
	system("cls");
	ptr1 = fopen("supplier.dat", "r");
	if (ptr1 == NULL)
	{
		printf("\n\t Can not open File! ");
		exit(0);
	}
	system("cls");
	box();
	t();
	//textcolor(GREEN+BLINK);
	gotoxy(8, 48);
	printf("Press Anykey to go to SUPPLIER MENU !!!");
	//textcolor(GREEN);
	lbox();
	gotoxy(30, 8);
	printf(" SUPPLIER LIST ");
	//textcolor(WHITE);
	gotoxy(5, 10);
	printf("ID.  SUPPLIER NAME.      PH.NO.     CITY.         EMAIL");
	gotoxy(4, 12);
	i = 14;
	printf("=================================================================");
	while (fscanf(ptr1, "%d %s %s %s %s", &temp1.supp_id, temp1.supp_name, temp1.city, temp1.mob_no, temp1.email) != EOF)
	{
		gotoxy(4, i);
		printf(" %d", temp1.supp_id);
		gotoxy(9, i);
		printf(" %s", temp1.supp_name);
		gotoxy(29, i);
		printf(" %s", temp1.city);
		gotoxy(41, i);
		printf(" %s", temp1.mob_no);
		gotoxy(54, i);
		printf(" %s", temp1.email);
		i = i + 2;
	}
	getche();
}
//======================search supplier==================
void search()
{
	check = 0;
	int ch;
	char ch2;
	do
	{
		system("cls");
		//textcolor(WHITE);
		gotoxy(17, 10);
		printf(" Two options Available for searching ");

		gotoxy(15, 15);
		printf("Search by");
		gotoxy(25, 15);
		printf("ID number");

		gotoxy(15, 18);
		printf("Search by");
		gotoxy(25, 18);
		printf("Name");

		gotoxy(15, 21);
		printf("Return");

		main_box();

		gotoxy(17, 24);
		printf("Press First charecter for the operation : ");
		gotoxy(15, 15 + (check * 3));
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
				case 0:
					animation();
					search_id();

					break;
				case 1:
					animation();
					search_name();
					break;
				case 2:
					animation();
					supplier();
					break;
				}
			case 'I':
				animation();
				search_id();

				break;
			case 'N':
				animation();
				search_name();
				break;
			case 'R':
				animation();
				supplier();
				break;
			default:
				gotoxy(22, 18);
				printf("You entered wrong choice!!!!!");
				getch();
			}
		}
	} while (ch != 'R');

}
//=============================== Search by id =============================
void search_id()
{
	int id;
	FILE *fp;

	fp = fopen("supplier.dat", "r");
	if (fp == NULL)
	{
		printf("file can't open!!!!");

	}
	system("cls");
	box();
	gotoxy(13, 8);
	printf("Enter id to be searched:");
	scanf("%d", &id);
	gotoxy(20, 35);
	//textcolor(YELLOW);
	printf("Press Any key to Return Back Menu ....");
	gotoxy(12, 14);
	printf("ID.  SUPPLIER NAME.   CITY.     PH.NO.       EMAIL");
	gotoxy(12, 16);
	i = 18;
	printf("==============================================================");
	while (fscanf(fp, "%d %s %s %s %s", &temp1.supp_id, temp1.supp_name, temp1.mob_no, temp1.city, temp1.email) != EOF)
	{
		if (temp1.supp_id == id)
		{
			gotoxy(10, i);
			printf(" %d", temp1.supp_id);
			gotoxy(15, i);
			printf(" %s", temp1.supp_name);
			gotoxy(30, i);
			printf(" %s", temp1.city);
			gotoxy(40, i);
			printf(" %s", temp1.mob_no);
			gotoxy(53, i);
			printf(" %s", temp1.email);
			i++;
			break;
		}
	}
	if (temp1.supp_id != id)
	{
		gotoxy(20, 30);
		printf("Record not found!");
	}
	fclose(fp);
	getche();
}
//============================ Search by name =============================
void search_name()
{
	char name[20];
	FILE *fp;

	fp = fopen("supplier.dat", "r");
	if (fp == NULL)
	{
		printf("file can't open!!!!");

	}
	system("cls");
	box();
	fp = fopen("supplier.dat", "rb");
	gotoxy(13, 8);
	printf(" Enter Supplier Name to be searched : ");
	scanf("%s", &name);
	gotoxy(20, 35);
	//textcolor(YELLOW);
	printf("Press Any key to Return Back Menu ....");
	gotoxy(12, 14);
	printf("ID. SUPPLIER NAME.   CITY.     PH.NO.       EMAIL");
	gotoxy(12, 16);
	i = 18;
	printf("==============================================================");

	while (fscanf(fp, "%d %s %s %s %s", &temp1.supp_id, temp1.supp_name, temp1.mob_no, temp1.city, temp1.email) != EOF)
	{
		if (strcmp(temp1.supp_name, name) == 0)
		{
			gotoxy(11, i);
			printf(" %d", temp1.supp_id);
			gotoxy(15, i);
			printf(" %s", temp1.supp_name);
			gotoxy(30, i);
			printf(" %s", temp1.city);
			gotoxy(40, i);
			printf(" %s", temp1.mob_no);
			gotoxy(53, i);
			printf(" %s", temp1.email);
			i++;
			break;
		}
	}
	if (strcmp(temp1.supp_name, name) != 0)
	{
		gotoxy(20, 30);
		//textcolor(YELLOW);
		printf("Record not found!!!");
	}
	fclose(ptr1);
	getche();
}
//============supp update=================
void sup_update()
{
	int i;
	char ch;
	int sid;
	FILE *ft;
	system("cls");
	box();
	ptr1 = fopen("supplier.dat", "rb+");
	if (ptr1 == NULL)
	{
		printf("\n\t Can not open file!! ");
		exit(0);
	}
	lbox();
	gotoxy(30, 8);
	printf(" Modifying Supplier ");
	gotoxy(12, 13);
	printf("Enter supplier ID :  ");
	// //flushall();
	scanf("%d", &sid);
	gotoxy(12, 15);

	ft = fopen("temp.dat", "w");
	if (ft == NULL)
	{
		printf(" Can not open file");
		exit(1);
	}
	else
	{
		while (fscanf(ptr1, "%d %s %s %s %s", &temp1.supp_id, temp1.supp_name, temp1.mob_no, temp1.city, temp1.email) != EOF)
		{
			if (temp1.supp_id == sid)
			{
				gotoxy(18, 17);
				printf(" Existing Record  ");
				gotoxy(10, 19);
				printf("%d\t %s \t%s \t%s \t%s", temp1.supp_id, temp1.supp_name, temp1.mob_no, temp1.city, temp1.email);
				gotoxy(12, 22);
				printf("Enter New Name       : ");
				//flushall();
				ventry(temp1.supp_name, 0);
				gotoxy(12, 24);
				printf("Enter New mobile no  : ");
				//flushall();
				ventry(temp1.mob_no, 1);
				gotoxy(12, 26);
				printf("Enter New City       : ");
				//flushall();
				ventry(temp1.city, 0);
				gotoxy(12, 28);
				printf("Enter New email      : ");
				//flushall();
				ventry(temp1.email, 2);
				gotoxy(20, 32);
				//textcolor(RED+BLINK);
				printf("U");
				gotoxy(21, 32);
				//textcolor(WHITE);
				printf("pdate");
				gotoxy(30, 32);
				//textcolor(RED+BLINK);
				printf("C");
				gotoxy(31, 32);
				//textcolor(WHITE);
				printf("ancel");
				gotoxy(18, 36);
				printf("Press First charecter for the operation : ");
				ch = getch();
				if (ch == 'u' || ch == 'U')
				{
					fprintf(ft, "%d %s %s %s %s\n", temp1.supp_id, temp1.supp_name, temp1.mob_no, temp1.city, temp1.email);
					//flushall();
					gotoxy(20, 38);
					printf("Supplier updated successfully...");
					remove("supplier.dat");
					rename("temp.dat", "supplier.dat");

				}
			}
			else
			{
				fprintf(ft, "%d %s %s %s %s\n", temp1.supp_id, temp1.supp_name, temp1.mob_no, temp1.city, temp1.email);
				fflush(stdin);
			}
		}

		fclose(ft);
		fclose(ptr1);
	}
}





//=========================getsupp_id =======================
int getsupp_id() {

	FILE *fp;
	fp = fopen("supplier.dat", "r");
	if (fp == NULL)
	{
		gotoxy(22, 15);
		printf("Data not Found.....");
		getch();
	}
	else
	{
		temp1.supp_id = 100;
		rewind(fp);
		while (fscanf(fp, "%d %s %s %s %s", &temp1.supp_id, temp1.supp_name, temp1.city, temp1.mob_no, temp1.email) != EOF);
	}
	fclose(fp);
	return temp1.supp_id + 1;
}
