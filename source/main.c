#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
#define Acct_Data 3	//定義能記錄、查詢幾筆資料的最大值，
					//為了Demo方便，這邊先設定為3
void Accounting(int *, int*, struct Acct[]);	//記帳副程式
void Feeding(int*, int*);						//餵食功能副程式

typedef struct _Accounting//記帳 一筆資料的結構
{
	int money;	//金額
	char type;	//支出or收入
	int year;	//年
	int month;	//月
	int day;	//日
}Acct;

int main()
{
	int my_money = 0;		//使用者的錢，初始值=0
	int i = 0;				//用來記第幾筆記帳資料的變數，初始值=0
	Acct myAcct[Acct_Data];	//記帳資料，可以記Acct_Data筆資料
	int select;				//主選單選擇
	int lv = 1;				//等級，初始等級=1
	int ex = 0;				//經驗，初始經驗=0

	do
	{
		do
		{
			printf("石虎喵喵──個人小助手\t$:%d LV:%d\n\n", my_money, lv);			//顯示錢包以及等級
			printf("請選擇功能：\n1.餵食\n2.記帳\n3.個性測驗\n4.占卜\n5.離開\n");	//選項清單
			scanf_s("%d", &select);			//輸入選項
		} while (select < 1 || select>5);	//輸入的選項若不在1~5，則重跑選單

		switch (select)
		{
		case 1:
			Feeding(&lv, &ex);						//等級1開放功能──選項1餵食
			break;
		case 2:
			if (lv < 2)
				printf("還未開放此功能!!\n\n");
			else
				Accounting(&my_money, &i, myAcct);	//等級2開放功能──選項2記帳
			break;
		case 5:
			return 0;								//選項5離開
			break;
		}

	} while (select != 5);							//沒選擇離開就繼續

	return 0;
}

void Accounting(int *money, int *i, Acct myAcct[Acct_Data])	//記帳副程式
{   //輸入值為使用者的錢、記第幾筆記帳資料的變數、記帳資料		
	int select;	//選擇

	do
	{
		do
		{
			printf("\n我的錢包：%d元\n", *money);						//顯示錢包的錢
			printf("請選擇功能：\n1.支出\n2.收入\n3.查詢\n4.離開\n");	//記帳功能選單
			scanf_s("%d", &select);										//輸入選項
		} while (select < 1 || select>4);			 //輸入的選項若不在1~4，則重跑選單

		switch (select)
		{
		case 1:	//支出
			if (*i == Acct_Data)	//若所記錄的為最後一筆資料
			{
				for (int j = 0; j < Acct_Data - 1; j++)
				{
					myAcct[j] = myAcct[j + 1];	//1~最後一筆資料往前移至0~最後一筆-1
					*i = Acct_Data - 1;			//當前記錄的資料=最後一筆-1
				}
			}
			myAcct[*i].type = 'a';				//type='a'為支出
			printf("請輸入支出的金額：");
			scanf_s("%d", &myAcct[*i].money);	//輸入要支出的金額
			printf("請輸入年/月/日(YYYY/MM/DD)\n");
			scanf_s("%d/%d/%d", &myAcct[*i].year, &myAcct[*i].month, &myAcct[*i].day);//輸入支出的年月日
			*money = *money - myAcct[*i].money;	//錢包扣掉支出的錢
			printf("於%d年%d月%d日支出%d元，我的錢包：%d元\n", myAcct[*i].year,
				myAcct[*i].month, myAcct[*i].day, myAcct[*i].money, *money);	//顯示支出結果
			*i = *i + 1;	//當前記錄的資料+1
			break;
		case 2:	//收入
			if (*i == Acct_Data)	//若所記錄的為最後一筆資料
			{
				for (int j = 0; j < Acct_Data - 1; j++)
				{
					myAcct[j] = myAcct[j + 1];	//1~最後一筆資料往前移至0~最後一筆-1
					*i = Acct_Data - 1;			//當前記錄的資料=最後一筆-1
				}
			}
			myAcct[*i].type = 'b';				//type='b'為收入
			printf("請輸入收入的金額：");
			scanf_s("%d", &myAcct[*i].money);	//輸入要支出的金額
			printf("請輸入年/月/日(YYYY/MM/DD)\n");
			scanf_s("%d/%d/%d", &myAcct[*i].year, &myAcct[*i].month, &myAcct[*i].day);//輸入收入的年月日
			*money = *money + myAcct[*i].money;	//錢包加上收入的錢
			printf("於%d年%d月%d日收入%d元，我的錢包：%d元\n", myAcct[*i].year,
				myAcct[*i].month, myAcct[*i].day, myAcct[*i].money, *money);	//顯示收入結果
			*i = *i + 1;	//當前記錄的資料+1
			break;
		case 3:	//查詢
			printf("===============================\n");
			printf(" 年  月  日   支出/收入   金額\n");	//顯示標題
			printf("===============================\n");
			for (int j = 0; j < *i; j++)
			{
				printf("%4d%3d%4d     %s%10d\n", myAcct[j].year, myAcct[j].month, myAcct[j].day,
					myAcct[j].type == 'a' ? "支出" : "收入", myAcct[j].money);
			} //顯示第0筆~當前記錄的資料
			break;
		case 4:	//離開
			return;
			break;
		}

		printf("\n繼續記帳/離開(1/0)：");	//是否繼續記帳
		scanf_s("%d", &select);				//輸入選項
		printf("\n");
	} while (select != 0);	//不等於0就繼續記帳
	return;	//回到主選單
}

void Feeding(int *lv, int *ex)//餵食功能的副程式
{
	int select;
	int lim = 5;//最高等級是五
	while (1)
	{
		printf("正在進行餵食功能\n\n目前石虎喵喵的狀態:LV:%d", *lv);
		for (int i = 1; i <= *ex; i++) //每餵食一次增加一點經驗值
		{
			printf("-");
		}
		printf("\n");
		printf("請選擇要餵食的食物:\n(1)炸雞 or (2)啤酒 or (3)退出       ");
		scanf_s("%d", &select);
		printf("\n");
		if (*lv == lim)
		{
			printf("已達等級上限\n");
			return;
		}
		else if (*lv < lim)//等級小於最高等，繼續增加一點經驗值
		{
			switch (select)
			{
			case 1:
				printf("已選擇 炸雞 增加1點經驗值\n===================================\n");
				*ex = *ex + 1;
				break;
			case 2:
				printf("已選擇 啤酒 增加1點經驗值\n===================================\n");
				*ex = *ex + 1;
				break;
			case 3:
				printf("已退出\n");
				return;
				break;
			}
			if (*ex % 10 == 0)//每十點經驗值，上升一等
			{
				*lv = *lv + 1;
				*ex = 0;
			}
		}

	}
}