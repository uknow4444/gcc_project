#pragma once
#include "system.h"
#include "customer.h"
#include "supplier.h"
#include "pgm.h"
#include "medicine.h"



//=========================For Medicine ===========================
void medicine()
{
	check = 0;
	int ch;
	char ch2;
	do
	{
		system("cls");

		gotoxy(34, 3);
		printf("---------------");
		gotoxy(35, 4);
		printf("Medicine Menu.");
		gotoxy(34, 5);
		printf("---------------");

		gotoxy(25, 15);
		printf("Purchase New Medicine");

		gotoxy(25, 19);
		printf("Sale Medicine");

		gotoxy(25, 23);
		printf("Stock of Medicine");

		gotoxy(25, 27);
		printf("Search Medicine");

		gotoxy(25, 31);
		printf("Main Menu");

		main_box();

		gotoxy(10, 40);
		printf("Press First Character for further Operations  ");

		gotoxy(25, 15 + (check * 4));
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
				case 0:medi_entry();
					break;
				case 1:medi_sale();
					break;
				case 2:stock();
					break;
				case 3:medi_search();
					break;
				case 4:main_menu();
					break;
				}
			case 'P':medi_entry();
				break;
			case 'S':medi_sale();
				break;
			case 'C':stock();
				break;
			case 'A':medi_search();
				break;
			case 'M':main_menu();
				break;
			default://textcolor(4+BLINK);
				gotoxy(11, 34);
				printf("Plese Enter right character ONLY (P,S,C,M).");
				getch();
			}
		}
	} while (ch != 'M');
}


//============================ FOR MEDICINE PURCHASE    ===================
void medi_entry()
{
	char ch, id[6];
	//  struct date d;
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	int f;
	FILE *fp;
	system("cls");
	//getdate(&d);

	ptrp_r = fopen("purreport.dat", "a");
	ch = 'Y';
	while (ch == 'Y')
	{
		system("cls");
		box();
		//textcolor(14);
		//		t();  // THIS FUN IS USED FOR DISPLAY DATE & TIME.......
		lbox();
		gotoxy(30, 8);
		////textcolor(GREEN+BLINK);
		printf(" MEDICINE PURSHASE  ");
		{
			//textcolor(WHITE);
			gotoxy(7, 11);
			printf("MEDICINE ID    : ");

			gotoxy(40, 11);
			printf("MEDICINE NAME  : ");

			gotoxy(7, 14);
			printf("ENTER RACK NO  : ");

			gotoxy(40, 14);
			printf("CABNIT NO      : ");

			gotoxy(7, 18);
			printf("COMPANY NAME   : ");

			gotoxy(40, 18);
			printf("SUPPLIER NAME  : ");

			gotoxy(7, 21);
			printf("UNIT COST   Rs.:  ");

			gotoxy(40, 21);
			printf("SALE COST   Rs.: ");

			gotoxy(7, 24);
			printf("QUANTITY       :  ");

			gotoxy(7, 27);
			printf("MFG.DATE(dd-mm-yyyy): ");

			gotoxy(7, 29);
			printf("EXP.DATE(dd-mm-yyyy): ");

			gotoxy(25, 11);
			ventry(temp.id, 1);
			strcpy(id, temp.id);

			fp = fopen("medical.dat", "r");
			while ((fread(&temp, sizeof(temp), 1, fp)) == 1)
			{

				if (strcmp(id, temp.id) == 0)
				{
					f = 1;
					break;
				}
			}
			fclose(fp);
			if (f == 1)
			{
				gotoxy(20, 31);
				printf("ID Allready Exists");
				getche();
				system("cls");
				medi_entry();
			}
			else
			{
				ptr = fopen("medical.dat", "a+b");
				strcpy(temp.id, id);
				strcpy(p_r.medi_id, temp.id);
			}
			//flushall();
			gotoxy(58, 11);
			ventry(temp.medi_name, 0);
			strcpy(p_r.medir_name, temp.medi_name);
			//flushall();
			gotoxy(25, 14);
			ventry(a, 1);
			temp.rack = atoi(a);//atoi() used for convert str to int.
								//flushall();
			gotoxy(58, 14);
			ventry(temp.cabnit, 2);
			//flushall();
			gotoxy(25, 18);
			ventry(temp.comp_name, 0);
			//flushall();
			gotoxy(58, 18);
			ventry(temp.supp_name, 0);
			strcpy(p_r.supp_name, temp.supp_name);
			//flushall();
			gotoxy(25, 21);
			ventry(a, 1);
			temp.unit = atof(a);
			//flushall();
			p_r.rate = temp.unit;
			gotoxy(58, 21);
			ventry(a, 1);
			temp.sale = atof(a);
			//flushall();
			gotoxy(25, 24);
			ventry(a, 1);
			temp.quantity = atoi(a);
			p_r.qty = temp.quantity;
			//flushall();
			gotoxy(29, 27);
			//flushall();
			ventry(temp.manu_date, 1);
			gotoxy(29, 29);
			//flushall();
			ventry(temp.exp_date, 1);

			gotoxy(7, 31);
			printf("==========================================================");
			temp.total = temp.quantity*temp.sale;

			//textcolor(10);
			gotoxy(10, 33);
			printf("TOTAL SALE COST = Rs. %.2f", temp.total);
			temp.cost = (temp.unit*temp.quantity);
			gotoxy(40, 33);
			printf("TOTAL UNIT COST = Rs. %.2f", temp.cost);
			p_r.total = temp.cost;
			p_r.sDay = now->tm_mday;
			p_r.sMonth = now->tm_mon;
			p_r.sYear = now->tm_year;
		}
		gotoxy(20, 35);
		//textcolor(RED+BLINK);
		printf("S");
		//textcolor(WHITE);
		gotoxy(21, 35);
		printf("ave");
		gotoxy(28, 35);
		//textcolor(RED+BLINK);
		printf("C");
		//textcolor(WHITE);
		gotoxy(29, 35);
		printf("ancel");
		gotoxy(18, 38);
		printf("Press First charecter for the operation : ");


		ch = toupper(getche());

		if (ch == 'S')
		{
			fwrite(&temp, sizeof(temp), 1, ptr);
			fflush(stdin);
			//textcolor(10);
			fprintf(ptrp_r, "%s %s %s %d %.2f %.2f %d %d %d\n", p_r.medi_id, p_r.medir_name, p_r.supp_name, p_r.qty, p_r.rate, p_r.total, p_r.sDay, p_r.sMonth, p_r.sYear);
			system("cls");
			gotoxy(20, 20);
			printf("Medicine Added sucessfully!!!!!!");
			gotoxy(20, 25);
			printf("More entries  [y/n]");
			ch = toupper(getche());
			/*	if(ch=='Y')
			{
			system("cls");
			medi_entry();
			}*/
		}

	}
	fclose(ptr);
	fclose(ptrp_r);
}
//===========FOR MEDICINE SALE=========================
void medi_sale()
{
	struct bill bil;
	//struct date d;
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	int j, n, i, a, billno;
	int d1, m, y;
	float b, total, rate;
	char tar[30], ch, mediname[30], c_name[30], cname[30];
	FILE *fp, *fpc;
	int count = 0;
	//getdate(&d);
	d1 = now->tm_mday;
	m = now->tm_mon;
	y = now->tm_year;
	ch = 'y';
	while (ch == 'y')
	{
		fp = fopen("dbbill.dat", "a");
		ptr1 = fopen("customer.dat", "r");
		ptr = fopen("medical.dat", "r");
		ptrs_r = fopen("saleRpt.dat", "a");
		ptrpr_r = fopen("profitRpt.dat", "a");
		system("cls");
		box();
		for (i = 3; i <= 45; i++)      //This 'FOR' loop will print asteriks 'I'
		{                       //vertically till the 3th row is reached.
			gotoxy(50, i);
			printf("%c", 219);
		}
		i = 9;
		gotoxy(52, 7);
		printf("Cust_ID    Cust_Name");
		//flushall();
		while (fscanf(ptr1, "%d %s %s %s %s", &temp_c.cust_id, temp_c.cust_name, temp_c.mob_no, temp_c.city, temp_c.email) != EOF)
		{
			gotoxy(53, i);
			printf("%d", temp_c.cust_id);
			gotoxy(64, i);
			printf("%s", temp_c.cust_name);
			i += 2;
		}

		gotoxy(9, 7);
		printf("ENTER MEDICINE ID TO BE SOLD  : ");
		ventry(tar, 1);
		//scanf("%s",&tar);
		j = 0;
		while ((fread(&temp, sizeof(temp), 1, ptr)) == 1)
		{
			if ((strcmp(temp.id, tar)<0) || (strcmp(temp.id, tar)>0))
			{
				x[j] = temp;
				j++;
			}
			else if ((strcmp(temp.id, tar) == 0))
			{

				gotoxy(8, 10);
				printf(" Medicine Name        : %s", temp.medi_name);
				gotoxy(8, 12);
				printf(" Quantity in stock    : %d", temp.quantity);
				gotoxy(8, 14);
				printf(" Sales price          : %.2f", temp.sale);
				gotoxy(8, 16);
				printf("Enter bill number     : ");
				//flushall();
				ventry(bil.billno, 1);
				//scanf("%s",&bil.billno);
				gotoxy(8, 18);
				printf("Enter customer Name   : ");
				//flushall();
				ventry(c_name, 0);
				//scanf("%s",&c_name);
				gotoxy(8, 20);
				printf("Quantity want to sale : ");
				//ventry(a,1);
				scanf("%d", &a);

				pr_r.profit = (temp.sale - temp.unit)*a;
				x[j] = temp;
				x[j].quantity = (x[j].quantity - a);
				x[j].total = (x[j].quantity*temp.sale);
				x[j].cost = (x[j].quantity*temp.unit);
				x[j].bye = (x[j].sale*a);
				b = x[j].bye;
				x[j].qty = a;
				j++;
				count++;
				strcpy(bil.cname, c_name);
				strcpy(s_r.cust_name, c_name);
				strcpy(bil.mediname, temp.medi_name);
				bil.medi_qty = a;
				bil.medi_rate = temp.sale;
				bil.total = temp.sale*a;

				bil.day = d1;
				bil.month = m;
				bil.year = y;

				fprintf(fp, "%s %s %s %d %.2f %.2f %d %d %d\n", bil.billno, bil.cname, bil.mediname, bil.medi_qty, bil.medi_rate, bil.total, bil.day, bil.month, bil.year);
				fflush(stdin);

				fclose(fp);

				s_r.sDay = d1;
				s_r.sMonth = m;
				s_r.sYear = y;
				strcpy(s_r.medi_id, tar);
				strcpy(s_r.medir_name, temp.medi_name);
				s_r.qty = a;
				s_r.rate = temp.sale;
				s_r.total = temp.sale*a;

				//sale report
				fprintf(ptrs_r, "%s %s %s %d %.2f %.2f %d %d %d\n", s_r.medi_id, s_r.medir_name, s_r.cust_name, s_r.qty, s_r.rate, s_r.total, s_r.sDay, s_r.sMonth, s_r.sYear);
				fflush(stdin);
				fclose(ptrs_r);
				//profit report

				pr_r.sDay = d1;
				pr_r.sMonth = m;
				pr_r.sYear = y;
				strcpy(pr_r.medi_id, tar);
				strcpy(pr_r.medir_name, temp.medi_name);
				pr_r.qty = a;
				pr_r.rate = temp.sale;
				pr_r.unit = temp.unit;
				fprintf(ptrpr_r, "%s %s %d %d %d %d %.2f %.2f  %.2f\n", pr_r.medi_id, pr_r.medir_name, d1, pr_r.sMonth, pr_r.sYear, pr_r.qty, pr_r.unit, pr_r.rate, pr_r.profit);
				fflush(stdin);
				fclose(ptrpr_r);

			}
		}
		if (count == 0)
		{
			system("cls");
			gotoxy(33, 10);
			printf("Not in stock!!!!!");
			getch();
			return;
		}
		fclose(ptr1);
		fclose(ptr);
		n = j;
		system("cls");
		ptr = fopen("medical.dat", "wb");
		for (i = 0; i<n; i++)
			fwrite(&x[i], sizeof(x[i]), 1, ptr);
		fclose(ptr);
		system("cls");
		box();
		gotoxy(8, 15);
		printf("* Price paid by customer = %.2f", b);
		gotoxy(8, 17);
		printf("* Quantity sold          = %d", a);
		getch();
		gotoxy(10, 20);
		printf("more enteries=(y/n) :");
		ch = getche();
	}

}
//===========================MEDICINE STOCK=====================================
void stock()
{
	char ch;
	int i, c;
	do
	{
		system("cls");
		ptr1 = fopen("medical.dat", "r");
		if (ptr1 == NULL)
		{
			printf("\n\t Can not open File! ");
			exit(1);
		}
		system("cls");
		box();
		lbox();
		//textcolor(GREEN);
		gotoxy(30, 8);
		////textcolor(GREEN+BLINK);
		printf(" STOCK OF MEDICINE ");
		//textcolor(WHITE);
		i = 14;
		gotoxy(9, 10);
		printf("ID.   MEDICINE NAME.    QTY     Supplier Name     Exp.Date");
		gotoxy(9, 12);
		printf("==================================================================\n");

		while ((fread(&temp, sizeof(temp), 1, ptr1)) == 1)
		{
			gotoxy(9, i);
			printf(" %s", temp.id);
			gotoxy(15, i);
			printf(" %s", temp.medi_name);
			gotoxy(32, i);
			printf(" %d", temp.quantity);
			gotoxy(43, i);
			printf(" %s", temp.supp_name);
			gotoxy(60, i);
			printf(" %s", temp.exp_date);
			i++;
		}
		gotoxy(10, 42);
		printf("Press [1] for Update Medicine Stock  & [0] for main menu ");
		c = (getche());
		switch (c)
		{
		case '0':animation();
			main_menu();
			break;
		case '1':update_stock();
			break;
		}

	} while (c != '1');
	getche();
}
//=============================== FOR MEDICINE SEARCH ====================
void medi_search()
{
	char mid[6];
	int i, c;
	system("cls");
	ptr1 = fopen("medical.dat", "r");
	if (ptr1 == NULL)
	{
		printf("\n\t Can not open File! ");
		exit(0);
	}
	system("cls");
	box();

	gotoxy(10, 7);
	printf("Enter Medicine Id to be searched : ");
	scanf("%s", &mid);
	system("cls");
	box();
	lbox();
	//textcolor(GREEN);
	gotoxy(30, 8);
	//textcolor(GREEN+BLINK);
	printf(" MEDICINE ");
	//textcolor(WHITE);
	i = 14;
	gotoxy(9, 10);
	printf("ID.   MEDICINE NAME.    QTY     Supplier Name     Exp.Date");
	gotoxy(9, 12);
	printf("==================================================================\n");
	while ((fread(&temp, sizeof(temp), 1, ptr1)) == 1)
	{
		if (strcmp(mid, temp.id) == 0)
		{
			gotoxy(9, i);
			printf(" %s", temp.id);
			gotoxy(15, i);
			printf(" %s", temp.medi_name);
			gotoxy(32, i);
			printf(" %d", temp.quantity);
			gotoxy(43, i);
			printf(" %s", temp.supp_name);
			gotoxy(60, i);
			printf(" %s", temp.exp_date);
			i++;
			break;
		}

	}
	if (strcmp(mid, temp.id) != 0)
	{
		gotoxy(20, 20);
		printf("Not in Stock.....");
	}
	getche();

}
//============================ FOR MEDICINE UPDATE =====================
void update_stock()
{
	char mid[6];
	int j, a, count = 0, n;
	system("cls");
	ptr = fopen("medical.dat", "rb");
	if (ptr == NULL)
	{
		printf("\n\t Can not open File! ");
		exit(0);
	}
	system("cls");
	box();
	gotoxy(20, 45);
	printf("Press Enter to go to MENU ...........");
	//textcolor(GREEN);
	gotoxy(27, 8);
	////textcolor(GREEN+BLINK);
	printf(" UPDATE MEDICINE QUANTITY ");
	//textcolor(WHITE);
	gotoxy(9, 10);
	printf("Enter medicine id to be update qty: ");
	scanf("%s", &mid);
	j = 0;

	while ((fread(&temp, sizeof(temp), 1, ptr)) == 1)
	{
		if ((strcmp(temp.id, mid)<0) || (strcmp(temp.id, mid)>0))
		{
			x[j] = temp;
			j++;
		}
		else
		{
			gotoxy(8, 12);
			printf("Medicine Name     : %s", temp.medi_name);
			gotoxy(8, 14);
			printf("Quantity in stock : %d", temp.quantity);
			gotoxy(8, 16);
			printf("Quantity want to update : ");
			scanf("%d", &a);
			x[j] = temp;
			x[j].quantity = (x[j].quantity + a);
			x[j].total = (x[j].quantity*temp.sale);
			x[j].cost = (x[j].quantity*temp.unit);
			x[j].bye = (x[j].sale*a);
			x[j].qty = a;
			j++;
			count++;
		}
	}
	if (count == 0)
	{
		system("cls");
		gotoxy(33, 10);
		printf("Not in stock!!!!!!");
		getch();
		return;
	}
	fclose(ptr);
	n = j;
	system("cls");
	ptr = fopen("medical.dat", "wb");
	for (i = 0; i<n; i++)
		fwrite(&x[i], sizeof(x[i]), 1, ptr);
	fclose(ptr);
}