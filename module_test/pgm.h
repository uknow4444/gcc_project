#pragma once
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<dos.h>
#include<time.h>
#include<ctype.h>
#include<windows.h>


int i;
int check;
//===================================structures =========================
struct medical{
	char id[6];
	char medi_name[20];
	int rack;
	char cabnit[2];
	int quantity;
	float sale;
	float total;
	float unit;
	float cost;
	float profit;
	float bye;
	int qty;
	char pur_date[15];
	char exp_date[15];
	char manu_date[15];
	int bill_no;
	char comp_name[20];
	char supp_name[30];
};

struct medical temp;
struct medical x[20];
FILE *ptr;

char a[10];
struct supplier{
	int supp_id;
	char supp_name[25];
	char city[20];
	char mob_no[11];
	char email[30];

};
struct supplier temp1;

struct customer{
	int cust_id;
	char cust_name[30];
	char city[20];
	char mob_no[11];
	char email[50];

};
struct customer temp_c;
FILE *ptr1;

struct bill{
	char billno[6];
	char cname[30];
	char mediname[30];
	int medi_qty;
	float medi_rate;
	float total;
	int day;
	int month;
	int year;
};
struct bill bil;
FILE *ptrbill;

struct sales_report
{
	char medi_id[6];
	char medir_name[20];
	char cust_name[30];
	int sDay, sMonth, sYear;
	int qty;
	float rate;
	float total;
};
struct sales_report s_r;
FILE *ptrs_r;

struct purchase_report{
	char medi_id[6];
	char medir_name[20];
	char supp_name[30];
	int sDay, sMonth, sYear;
	int qty;
	float rate;
	float total;
};

struct purchase_report p_r;
FILE *ptrp_r;

struct profit_report{
	char medi_id[6];
	char medir_name[20];
	int sDay, sMonth, sYear;
	int qty;
	float rate;
	float unit;
	float profit;
};

struct profit_report pr_r;
FILE *ptrpr_r;

