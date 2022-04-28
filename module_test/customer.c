#pragma once
#include "system.h"
#include "customer.h"
#include "supplier.h"
#include "pgm.h"
#include "medicine.h"


//=========================For customer ===========================
void customer()
{
	check = 0;
	int ch;
	char ch2;
	do
	{
		system("cls");

		gotoxy(34, 3);
		//textcolor(GREEN);
		printf("---------------");
		gotoxy(35, 4);
		printf("Customer Menu.");
		gotoxy(34, 5);
		printf("---------------");

		gotoxy(25, 11);
		printf("Add New Customer");

		gotoxy(25, 15);
		printf("Update Customer");

		gotoxy(25, 19);
		printf("Search Customer");

		gotoxy(25, 23);
		printf("List of Existing Customer");

		gotoxy(25, 27);

		printf("Main Menu");

		main_box();

		gotoxy(10, 40);
		printf("Press First Character for further Operations  ");


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
					cust_entry();
					break;
				case 1:animation();
					cust_update();
					break;
				case 2:animation();
					cust_search();
					break;
				case 3:cust_list();
					break;
				case 4:main_menu();
					break;
				}
			case 'A':animation();
				cust_entry();
				break;
			case 'U':animation();
				cust_update();
				break;
			case 'L':animation();
				cust_list();
				break;
			case 'S':cust_search();
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

//========FOR CUSTOMER ENTRY=================
void cust_entry()
{
	char ch;
	int id;
	FILE *fp;
	system("cls");
	fp = fopen("customer.dat", "a");
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
		printf(" CUSTOMER ENTRY ");
		gotoxy(8, 13);
		//flushall();
		temp_c.cust_id = getcust_id();
		printf("CUSTOMER ID :%d", temp_c.cust_id);
		//ventry(temp_c.cust_id,1);
		//flushall();
		gotoxy(39, 13);
		printf("CUSTOMER NAME : ");
		gotoxy(8, 18);
		printf("CITY        : ");
		gotoxy(39, 18);
		printf("CONTACT NO.   : ");
		gotoxy(8, 23);
		printf("EMAIL ID    : ");

		gotoxy(55, 13);
		//flushall();
		ventry(temp_c.cust_name, 0);
		gotoxy(22, 18);
		ventry(temp_c.city, 0);
		//flushall();
		gotoxy(55, 18);
		ventry(temp_c.mob_no, 1);
		//flushall();
		gotoxy(22, 23);
		gets(temp_c.email);
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
			fprintf(fp, "%d %s %s %s %s\n", temp_c.cust_id, temp_c.cust_name, temp_c.mob_no, temp_c.city, temp_c.email);
			fprintf(fp, "\n");
			fflush(stdin);
			system("cls");
			gotoxy(20, 20);
			printf("Customer Added Successfully!!!!!");
			//textcolor(10);
			gotoxy(20, 25);
			printf("More entries  [y/n] ");
			ch = getche();

		}
	}
	fclose(fp);
}

//=========FOR CUSTOMER DISPLAY LIST ==========
void cust_list()
{
	char ch;
	system("cls");
	ptr1 = fopen("customer.dat", "r");
	if (ptr1 == NULL)
	{
		printf("\n\t Can not open File! ");
		exit(0);
	}
	system("cls");
	box();
	//textcolor(GREEN+BLINK);
	gotoxy(8, 48);
	printf("Press Anykey to go to CUSTOMER MENU!!!");
	//textcolor(GREEN);
	lbox();
	gotoxy(30, 8);
	printf(" CUSTOMER LIST ");
	//textcolor(WHITE);
	i = 14;
	gotoxy(5, 10);
	printf(" ID. CUSTOMER NAME.    CITY.     MOBILE.NO.      EMAIL");
	gotoxy(4, 12);
	printf("==============================================================");
	while (fscanf(ptr1, "%d %s %s %s %s", &temp_c.cust_id, temp_c.cust_name, temp_c.mob_no, temp_c.city, temp_c.email) != EOF)
	{
		gotoxy(4, i);
		printf(" %d", temp_c.cust_id);
		gotoxy(11, i);
		printf(" %s", temp_c.cust_name);
		gotoxy(28, i);
		printf(" %s", temp_c.city);
		gotoxy(40, i);
		printf(" %s", temp_c.mob_no);
		gotoxy(53, i);
		printf(" %s", temp_c.email);
		i = i + 2;
	}
	getche();
}
//======================search CUSTOMER==================
void cust_search()
{
	check = 0;
	int ch;
	char ch2;
	do	{
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
					search_cid();
					break;
				case 1:
					animation();
					search_cname();
					break;
				case 2:
					animation();
					customer();
					break;
				}
			case 'I':
				animation();
				search_cid();

				break;
			case 'N':
				animation();
				search_cname();
				break;
			case 'R':
				animation();
				customer();
				break;
			default:
				gotoxy(22, 18);
				printf("You entered wrong choice!!!!!");
				getch();
			}
		}
	} while (ch != 'R');
	getche();
}
//===========================Search by CustomerId=========================
void search_cid()
{
	int id;
	system("cls");
	box();
	ptr1 = fopen("customer.dat", "rb");
	gotoxy(13, 8);
	printf("\xDB\xDB\xB2  Enter id to be searched:");
	scanf("%d", &id);
	//textcolor(GREEN);
	//textcolor(WHITE);
	i = 18;
	gotoxy(9, 15);
	printf(" ID. CUSTOMER NAME.    CITY.     MOBILE.NO.      EMAIL");
	gotoxy(8, 16);
	printf("==============================================================");
	while (fscanf(ptr1, "%d %s %s %s %s", &temp_c.cust_id, temp_c.cust_name, temp_c.mob_no, temp_c.city, temp_c.email) != EOF)
	{
		if (temp_c.cust_id == id)
		{
			gotoxy(8, i);
			printf(" %d", temp_c.cust_id);
			gotoxy(15, i);
			printf(" %s", temp_c.cust_name);
			gotoxy(28, i);
			printf(" %s", temp_c.city);
			gotoxy(40, i);
			printf(" %s", temp_c.mob_no);
			gotoxy(54, i);
			printf(" %s", temp_c.email);
			gotoxy(20, 35);
			//textcolor(YELLOW);
			printf("Press Any key to go to CUSTOMER MENU ...........");
			break;
		}
	}
	if (temp_c.cust_id != id)
	{
		gotoxy(20, 30);
		printf("Record not found!");
	}
	fclose(ptr1);
	getche();
}
/*****************************search by CUSTOMERname******************************/
void search_cname()
{
	char name[20];
	system("cls");
	box();
	ptr1 = fopen("customer.dat", "rb");
	gotoxy(12, 8);
	printf("\xDB\xDB\xB2  Enter Customer Name to be searched:");
	scanf("%s", &name);
	//textcolor(GREEN);
	//textcolor(WHITE);
	i = 18;
	gotoxy(9, 15);
	printf(" ID. CUSTOMER NAME.    CITY.     MOBILE.NO.      EMAIL");
	gotoxy(8, 16);
	printf("==============================================================");
	while (fscanf(ptr1, "%d %s %s %s %s", &temp_c.cust_id, temp_c.cust_name, temp_c.mob_no, temp_c.city, temp_c.email) != EOF)
	{
		if (strcmp(temp_c.cust_name, name) == 0)
		{
			gotoxy(8, i);
			printf(" %d", temp_c.cust_id);
			gotoxy(15, i);
			printf(" %s", temp_c.cust_name);
			gotoxy(28, i);
			printf(" %s", temp_c.city);
			gotoxy(40, i);
			printf(" %s", temp_c.mob_no);
			gotoxy(54, i);
			printf(" %s", temp_c.email);
			gotoxy(20, 35);
			//textcolor(YELLOW);
			printf("Press Any key to go to CUSTOMER MENU ...........");
			break;
		}
	}
	if (strcmp(temp_c.cust_name, name) != 0)
	{
		gotoxy(5, 10);
		//textcolor(YELLOW);
		printf("Record not found!");
	}
	fclose(ptr1);
	getche();
}
//============CUSTOMER update=================
void cust_update()
{
	int i;
	char ch;
	int cid;
	FILE *ft;
	system("cls");
	box();
	ptr1 = fopen("customer.dat", "rb+");
	if (ptr1 == NULL)
	{
		printf("\n\t Can not open file!! ");
		exit(0);
	}
	lbox();
	gotoxy(30, 8);
	printf(" Modifying customer ");
	gotoxy(12, 13);
	printf("Enter the CUSTOMER ID : ");
	scanf("%d", &cid);
	gotoxy(12, 15);

	ft = fopen("temp.txt", "w");
	if (ft == NULL)
	{
		printf("\n Can not open file");
		exit(0);
	}
	else
	{

		while (fscanf(ptr1, "%d %s %s %s %s", &temp_c.cust_id, temp_c.cust_name, temp_c.mob_no, temp_c.city, temp_c.email) != EOF)
		{
			if (temp_c.cust_id == cid)
			{
				gotoxy(25, 17);
				printf("*** Existing Record ***");
				gotoxy(10, 19);
				printf("%d\t %s \t%s \t%s \t%s", temp_c.cust_id, temp_c.cust_name, temp_c.mob_no, temp_c.city, temp_c.email);
				gotoxy(12, 22);
				printf("Enter New Name         : ");
				//flushall();
				ventry(temp_c.cust_name, 0);
				gotoxy(12, 24);
				printf("Enter New mobile no    : ");
				//flushall();
				ventry(temp_c.mob_no, 1);
				gotoxy(12, 26);
				printf("Enter New City         : ");
				//flushall();
				ventry(temp_c.city, 0);
				gotoxy(12, 28);
				printf("Enter New email        : ");
				//flushall();
				scanf("%s", temp_c.email);
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
				gotoxy(18, 35);
				printf("Press First charecter for the operation : ");
				ch = getche();
				if (ch == 'u' || ch == 'U')
				{
					fprintf(ft, "%d %s %s %s %s\n", temp_c.cust_id, temp_c.cust_name, temp_c.mob_no, temp_c.city, temp_c.email);
					//	fprintf(ft,"\n");
					fflush(stdin);
					gotoxy(20, 36);
					printf("Customer updated successfully...");
					remove("customer.dat");
					rename("temp.txt", "customer.dat");
				}
			}
			else
			{
				fprintf(ft, "%d %s %s %s %s\n", temp_c.cust_id, temp_c.cust_name, temp_c.mob_no, temp_c.city, temp_c.email);
				fflush(stdin);
			}
		}


		fclose(ft);
		fclose(ptr1);
	}

}



//=========================getcust_id =======================
int getcust_id()
{
	FILE *fp;
	fp = fopen("customer.dat", "r");
	if (fp == NULL)
	{
		gotoxy(22, 15);
		printf("Data not Found.....");
		getch();
	}
	else
	{
		temp_c.cust_id = 100;
		rewind(fp);
		while (fscanf(fp, "%d %s %s %s %s", &temp_c.cust_id, temp_c.cust_name, temp_c.mob_no, temp_c.city, temp_c.email) != EOF);
	}
	fclose(fp);
	return temp_c.cust_id + 1;
}