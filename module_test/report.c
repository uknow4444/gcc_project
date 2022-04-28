#pragma once
#include "system.h"
#include "report.h"
#include "pgm.h"


//=========================For Report ===========================
void report_menu(){
	check = 0;
	int ch;
	char ch2;
	do	{
		system("cls");

		gotoxy(34, 3);
		printf("---------------");
		gotoxy(35, 4);
		printf("Report Menu.");
		gotoxy(34, 5);
		printf("---------------");

		gotoxy(25, 12);
		printf("Purchase Report");

		gotoxy(25, 16);
		printf("Sale Report");

		gotoxy(25, 20);
		printf("Profit Report");

		gotoxy(25, 24);
		printf("Daily Sale Report");

		gotoxy(25, 28);
		printf("Daily Purchase Report");

		gotoxy(25, 32);
		printf("Main Menu");

		main_box();

		gotoxy(10, 40);
		printf("Press First Character for further Operations  ");


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
				case 0:pur_rpt();
					break;
				case 1:sale_rpt();
					break;
				case 2:profit_rpt();
					break;
				case 3:sale_rpt_daily();
					break;
				case 4:pur_rpt_daily();
					break;
				case 5:main_menu();
					break;
				}
			case 'P':pur_rpt();
				break;
			case 'S':sale_rpt();
				break;
			case 'A':sale_rpt_daily();
				break;
			case 'O':profit_rpt();
				break;
			case 'D':pur_rpt_daily();
				break;
			case 'M':main_menu();
				break;
			default://textcolor(4+BLINK);
				gotoxy(11, 34);
				printf("Plese Enter right character ONLY (P,S,O,M).");
				getch();
			}
		}
	} while (ch != 'M');
}


//===================== view report =============================/
void sale_rpt(){
	char ch;
	int j;
	system("cls");
	ptrs_r = fopen("saleRpt.dat", "r");
	if (ptrs_r == NULL)
	{
		printf("\n\t Can not open File! ");
		exit(0);
	}
	system("cls");
	box();
	gotoxy(20, 50);
	printf("Press any key to go to REPORT MENU ...........");
	lbox();
	//textcolor(GREEN);
	gotoxy(30, 8);
	////textcolor(GREEN+BLINK);
	printf("Sales Report");
	//textcolor(WHITE);
	gotoxy(7, 10);
	printf("ID. Medicine Name.  Customer Name.   Qty.  Rate.  Total.   Date");
	gotoxy(7, 12);
	printf("===================================================================");
	j = 14;
	while (fscanf(ptrs_r, "%s %s %s %d %f %f %d %d %d\n", s_r.medi_id, s_r.medir_name, s_r.cust_name, &s_r.qty, &s_r.rate, &s_r.total, &s_r.sDay, &s_r.sMonth, &s_r.sYear) != EOF)
	{
		gotoxy(6, j);
		printf("%s", s_r.medi_id);
		gotoxy(11, j);
		printf("%s", s_r.medir_name);
		gotoxy(28, j);
		printf("%s", s_r.cust_name);
		gotoxy(44, j);
		printf("%d", s_r.qty);
		gotoxy(50, j);
		printf("%.2f", s_r.rate);
		gotoxy(57, j);
		printf("%.2f", s_r.total);
		gotoxy(65, j);
		printf("%d-%d-%d", s_r.sDay, s_r.sMonth, s_r.sYear);
		j = j + 2;
	}
	getche();
}
//======================= VIEW PURCHASE REPORT ===========================
void pur_rpt(){
	char ch;
	int j;
	system("cls");
	t();
	box();
	ptrp_r = fopen("purreport.dat", "r");
	if (ptrp_r == NULL)
	{
		printf("\n\t Can not open File! ");
		exit(0);
	}
	gotoxy(20, 50);
	printf("Press Enter to go to REPORT MENU ...........");
	lbox();
	//textcolor(GREEN);
	gotoxy(30, 8);
	printf("Purchase Report");
	//textcolor(WHITE);
	gotoxy(7, 10);
	printf("ID. Medicine Name.  Supplier Name.   Qty.  Rate.  Total.   Date");
	gotoxy(7, 12);
	printf("===================================================================");
	j = 14;
	while (fscanf(ptrp_r, "%s %s %s %d %f %f %d %d %d\n", p_r.medi_id, p_r.medir_name, p_r.supp_name, &p_r.qty, &p_r.rate, &p_r.total, &p_r.sDay, &p_r.sMonth, &p_r.sYear) != EOF)
	{
		gotoxy(6, j);
		printf("%s", p_r.medi_id);
		gotoxy(11, j);
		printf("%s", p_r.medir_name);
		gotoxy(28, j);
		printf("%s", p_r.supp_name);
		gotoxy(44, j);
		printf("%d", p_r.qty);
		gotoxy(50, j);
		printf("%.2f", p_r.rate);
		gotoxy(57, j);
		printf("%.2f", p_r.total);
		gotoxy(65, j);
		printf("%d-%d-%d", p_r.sDay, p_r.sMonth, p_r.sYear);
		j += 2;
	}
	getche();
}
//========================= report of profit ===========================
void profit_rpt(){
	char ch;
	int j;
	system("cls");
	t();
	box();
	ptrpr_r = fopen("profitRpt.dat", "r");
	if (ptrpr_r == NULL)
	{
		printf("\n\t Can not open File! ");
		//	exit(0);
	}
	gotoxy(20, 50);
	printf("Press Enter to go to REPORT MENU ...........");
	lbox();
	//textcolor(GREEN);
	gotoxy(30, 8);
	printf("Profit Report");
	//textcolor(WHITE);
	gotoxy(7, 10);
	printf("ID. Medicine Name.   Date        Qty.  Unit Price  Sale Price. Profit. ");
	gotoxy(7, 12);
	printf("===================================================================");
	j = 14;
	while (fscanf(ptrpr_r, "%s %s %d %d %d %d %f %f %f \n", pr_r.medi_id, pr_r.medir_name, &pr_r.sDay, &pr_r.sMonth, &pr_r.sYear, &pr_r.qty, &pr_r.unit, &pr_r.rate, &pr_r.profit) != EOF)
	{
		gotoxy(6, j);

		printf("%s", pr_r.medi_id);
		gotoxy(11, j);
		printf("%s", pr_r.medir_name);
		gotoxy(28, j);
		printf("%d-%d-%d", pr_r.sDay, pr_r.sMonth, pr_r.sYear);
		gotoxy(40, j);
		printf("%d", pr_r.qty);
		gotoxy(48, j);
		printf("%.2f", pr_r.unit);
		gotoxy(60, j);
		printf("%.2f", pr_r.rate);
		gotoxy(70, j);
		printf("%.2f", pr_r.profit);
		gotoxy(10, j);
		printf("%c", 124);
		j += 2;

	}
	getche();
}

void sale_rpt_daily(){
	char ch;
	int j, d, m, y;
	float total = 0.00;
	system("cls");
	ptrs_r = fopen("saleRpt.dat", "r");
	if (ptrs_r == NULL)
	{
		printf("\n\t Can not open File! ");
		exit(0);
	}
	system("cls");
	gotoxy(15, 10);
	printf("Enter Date(dd-mm-yyyy):  ");
	scanf("%d-%d-%d", &d, &m, &y);
	system("cls");
	gotoxy(20, 50);
	printf("Press any key to go to REPORT MENU ...........");
	box();
	lbox();
	//textcolor(GREEN);
	gotoxy(30, 8);
	////textcolor(GREEN+BLINK);
	printf("Sales Report");
	//textcolor(WHITE);
	gotoxy(7, 10);
	printf("ID. Medicine Name.  Customer Name.   Qty.  Rate.  Total.   Date");
	gotoxy(7, 12);
	printf("===================================================================");
	j = 14;
	while (fscanf(ptrs_r, "%s %s %s %d %f %f %d %d %d\n", s_r.medi_id, s_r.medir_name, s_r.cust_name, &s_r.qty, &s_r.rate, &s_r.total, &s_r.sDay, &s_r.sMonth, &s_r.sYear) != EOF)
	{
		if (d == s_r.sDay &&m == s_r.sMonth && y == s_r.sYear)
		{
			gotoxy(6, j);
			printf("%s", s_r.medi_id);
			gotoxy(11, j);
			printf("%s", s_r.medir_name);
			gotoxy(28, j);
			printf("%s", s_r.cust_name);
			gotoxy(44, j);
			printf("%d", s_r.qty);
			gotoxy(50, j);
			printf("%.2f", s_r.rate);
			gotoxy(57, j);
			printf("%.2f", s_r.total);
			gotoxy(65, j);
			printf("%d-%d-%d", s_r.sDay, s_r.sMonth, s_r.sYear);
			j = j + 2;
			total = total + s_r.total;
		}
	}
	gotoxy(7, 42);
	printf("-------------------------------------------------------------------");
	gotoxy(45, 43);
	printf("Total:        %.2f", total);
	getche();
}

void pur_rpt_daily(){
	char ch;
	int j, d, m, y;
	float total = 0.00;

	ptrp_r = fopen("purreport.dat", "r");
	if (ptrp_r == NULL)
	{
		printf("\n\t Can not open File! ");
		exit(0);
	}
	system("cls");
	gotoxy(15, 10);
	printf("Enter Date(dd-mm-yyyy):  ");
	scanf("%d-%d-%d", &d, &m, &y);
	system("cls");
	gotoxy(20, 50);
	printf("Press Enter to go to REPORT MENU ...........");
	t();
	box();
	lbox();
	//textcolor(GREEN);
	gotoxy(30, 8);
	printf("Purchase Report");
	//textcolor(WHITE);
	gotoxy(7, 10);
	printf("ID. Medicine Name.  Supplier Name.   Qty.  Rate.  Total.   Date");
	gotoxy(7, 12);
	printf("===================================================================");
	j = 14;
	while (fscanf(ptrp_r, "%s %s %s %d %f %f %d %d %d\n", p_r.medi_id, p_r.medir_name, p_r.supp_name, &p_r.qty, &p_r.rate, &p_r.total, &p_r.sDay, &p_r.sMonth, &p_r.sYear) != EOF)
	{
		if (d == p_r.sDay &&m == p_r.sMonth && y == p_r.sYear)
		{
			gotoxy(6, j);
			printf("%s", p_r.medi_id);
			gotoxy(11, j);
			printf("%s", p_r.medir_name);
			gotoxy(28, j);
			printf("%s", p_r.supp_name);
			gotoxy(44, j);
			printf("%d", p_r.qty);
			gotoxy(50, j);
			printf("%.2f", p_r.rate);
			gotoxy(57, j);
			printf("%.2f", p_r.total);
			gotoxy(65, j);
			printf("%d-%d-%d", p_r.sDay, p_r.sMonth, p_r.sYear);
			j += 2;
			total = total + p_r.total;
		}
	}
	gotoxy(7, 42);
	printf("-------------------------------------------------------------------");
	gotoxy(45, 43);
	printf("Total:        %.2f", total);
	getche();
}