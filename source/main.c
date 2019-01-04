#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
#define Acct_Data 3	//定義能記錄、查詢幾筆資料的最大值，
					//為了Demo方便，這邊先設定為3
void Accounting(int *, int*, struct Acct[]);	//記帳副程式
void Feeding(int*, int*);						//餵食功能副程式
void Personality();								//個性測驗副程式

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
		case 3:
			if (lv < 3)
				printf("還未開放此功能!!\n\n");
			else
				Personality();						//等級3開放功能──選項3個性測驗
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

void Personality()
{
	printf("==================\n");
	printf("=    個性測驗    =\n");
	printf("==================\n");
	int a = 0;
	int s;
	printf("1.你何時感覺最好?\n(1)早晨 (2)下午或傍晚 (3)夜晚    ");
	scanf_s("%d", &s);
	switch (s) {
	case 1:
		a = a + 2;
		break;
	case 2:
		a = a + 4;
		break;
	case 3:
		a = a + 6;
		break;
	}
	printf("2.你走路時是......\n(1)大步的快走 (2)小步的快走 (3)不快，仰著頭面對世界 (4)不快，低著頭 (5)很慢    ");
	scanf_s("%d", &s);
	switch (s) {
	case 1:
		a = a + 6;
		break;
	case 2:
		a = a + 4;
		break;
	case 3:
		a = a + 7;
		break;
	case 4:
		a = a + 2;
		break;
	case 5:
		a = a + 1;
		break;
	}
	printf("3.和人說話時，你......\n(1)手臂交叉的站著 (2)雙手緊握著 (3)一隻手或兩手放在臀部 (4)碰著或推著與你說話的人 (5)玩著你的耳朵、摸著你的下巴或用手整理頭髮    ");
	scanf_s("%d", &s);
	switch (s) {
	case 1:
		a = a + 4;
		break;
	case 2:
		a = a + 2;
		break;
	case 3:
		a = a + 5;
		break;
	case 4:
		a = a + 7;
		break;
	case 5:
		a = a + 6;
		break;
	}
	printf("4.坐著休息時，你的......\n(1)兩膝蓋攏 (2)兩腿交叉 (3)兩腿伸直 (4)一腿捲在身下    ");
	scanf_s("%d", &s);
	switch (s) {
	case 1:
		a = a + 4;
		break;
	case 2:
		a = a + 6;
		break;
	case 3:
		a = a + 2;
		break;
	case 4:
		a = a + 1;
		break;
	}
	printf("5.碰到你感到發笑的事時，你的反應是......\n(1)一個欣賞的大笑 (2)笑著，但不大聲 (3)輕聲的咯咯笑 (4)羞怯的微笑    ");
	scanf_s("%d", &s);
	switch (s) {
	case 1:
		a = a + 6;
		break;
	case 2:
		a = a + 4;
		break;
	case 3:
		a = a + 3;
		break;
	case 4:
		a = a + 5;
		break;
	}
	printf("6.當你去一個派對或社交場合時，你......\n(1)很大聲地入場以引起注意 (2)安靜地入場，找你認識的人 (3)非常安靜地入場，儘量保持不被注意    ");
	scanf_s("%d", &s);
	switch (s) {
	case 1:
		a = a + 6;
		break;
	case 2:
		a = a + 4;
		break;
	case 3:
		a = a + 2;
		break;
	}
	printf("7.當你非常專心工作時，有人打斷你，你會......\n(1)歡迎他 (2)感到非常憤怒 (3)在上兩極端之間    ");
	scanf_s("%d", &s);
	switch (s) {
	case 1:
		a = a + 6;
		break;
	case 2:
		a = a + 2;
		break;
	case 3:
		a = a + 4;
		break;
	}
	printf("8.下列顏色中，你最喜歡哪一顏色......\n(1)紅或橘色 (2)黑色 (3)黃或淺藍色 (4)綠色 (5)深藍或紫色 (6)白色 (7)棕或灰色    ");
	scanf_s("%d", &s);
	switch (s) {
	case 1:
		a = a + 6;
		break;
	case 2:
		a = a + 7;
		break;
	case 3:
		a = a + 5;
		break;
	case 4:
		a = a + 4;
		break;
	case 5:
		a = a + 3;
		break;
	case 6:
		a = a + 2;
		break;
	case 7:
		a = a + 1;
		break;
	}
	printf("9.臨入睡的前幾分鐘，你的床上姿勢是......\n(1)仰躺，伸直 (2)，俯躺，伸直 (3)側躺，微捲 (4)頭睡在一手臂上 (5)被蓋過頭    ");
	scanf_s("%d", &s);
	switch (s) {
	case 1:
		a = a + 7;
		break;
	case 2:
		a = a + 6;
		break;
	case 3:
		a = a + 4;
		break;
	case 4:
		a = a + 2;
		break;
	case 5:
		a = a + 1;
		break;
	}
	printf("10.你經常夢到你在......\n(1)落下 (2)打架或掙扎 (3)找東西或人 (4)飛或漂浮 (5)你平常不作夢 (6)你的夢都是愉快的    ");
	scanf_s("%d", &s);
	switch (s) {
	case 1:
		a = a + 4;
		break;
	case 2:
		a = a + 2;
		break;
	case 3:
		a = a + 3;
		break;
	case 4:
		a = a + 5;
		break;
	case 5:
		a = a + 6;
		break;
	case 6:
		a = a + 1;
		break;
	}
	if (a < 21) {
		printf("【你是內向的悲觀者】\n");
		printf("人們認為你是一個害羞的、神經質的、優柔寡斷的、是需要人照顧的、永遠要別人替你做決定、\n不想遇任何事或任何人有關。他們認為你是一個杞人憂天者，一個永遠看到不存在的問題的人。\n有些人認為你令人乏味，只有那些深知你的人知道你不是這樣的人。\n");
	}
	else if (a >= 21 && a < 31) {
		printf("【缺乏信心的挑剔者】\n");
		printf("你的朋友認為你勤勉刻苦、很挑剔。他們認為你是一個謹慎的、十分小心的人，一個緩慢而\n穩定新潛工作的人。如果你做任何衝動的事或無準備的事，你會令他們大吃一驚。他們認為你會\n從各個角度仔細地檢查一切之後，仍經常決定不做。他們認為對你的這種反應一部分是因為你的\n小心的天性所引起的。\n");
	}
	else if (a >= 31 && a < 41) {
		printf("【以牙還牙的自我保護者】\n");
		printf("別人認為你是一個明智、謹慎、注重時效的人，也認為你是一個伶俐、有天賦有才幹且謙虛\n的人。你不會很快、很容易和人成為朋友，卻是一個對朋友非常忠誠的人，同時要求朋友對你也\n有忠誠的回報。那些真正有機會了解你的人會知道要動搖你對朋友的信念是很難的，但對等的，\n依但這信任被破壞，會使你很難熬過。\n");
	}
	else if (a >= 41 && a < 51) {
		printf("【平衡的中道】\n");
		printf("別人認為你是一個新鮮的、有活力的、有魅力的、好玩的、講究實際的、而永遠有趣的人;\n個經常是群眾注意力的焦點，但你是一個足夠平行的人，不至於因此而昏了頭。他們也認為你\n親切、和藹、體貼、能諒解人;一個永遠會使人高興起來且會幫助別人的人。\n");
	}
	else if (a >= 51 && a < 61) {
		printf("【吸引人的冒險家】\n");
		printf("別人認為你是一個令人興奮的、高度活潑的、相當易衝動的個性;你是一個天生的領袖、一\n個做決定會很快的人，雖然你的決定不總是對的。他們認為你是大膽地和冒險的，會願意試做任何\n事至少一次;是一個願意嘗試機會而欣賞冒險的人。因為妳散發的刺激，他們喜歡跟你在一\n起。\n");
	}
	else {
		printf("【傲慢的孤獨者】");
		printf("別人認為對你必須「小心處理」。在別人眼中，你是自負的、自我中心的、是個極端有支\n配慾的、統治慾的。別人可能欽佩妳，希望能多向你一點，但不會永遠相信你，會對與你更深入的\n來往有所躊躇及猶豫。\n");
	}
	printf("\n");
}