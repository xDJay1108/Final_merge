#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
#define Acct_Data 3	//�w�q��O���B�d�ߴX����ƪ��̤j�ȡA
					//���FDemo��K�A�o����]�w��3
void Accounting(int *, int*, struct Acct[]);	//�O�b�Ƶ{��
void Feeding(int*, int*);						//�����\��Ƶ{��

typedef struct _Accounting//�O�b �@����ƪ����c
{
	int money;	//���B
	char type;	//��Xor���J
	int year;	//�~
	int month;	//��
	int day;	//��
}Acct;

int main()
{
	int my_money = 0;		//�ϥΪ̪����A��l��=0
	int i = 0;				//�ΨӰO�ĴX���O�b��ƪ��ܼơA��l��=0
	Acct myAcct[Acct_Data];	//�O�b��ơA�i�H�OAcct_Data�����
	int select;				//�D�����
	int lv = 1;				//���šA��l����=1
	int ex = 0;				//�g��A��l�g��=0

	do
	{
		do
		{
			printf("�۪��p�p�w�w�ӤH�p�U��\t$:%d LV:%d\n\n", my_money, lv);			//��ܿ��]�H�ε���
			printf("�п�ܥ\��G\n1.����\n2.�O�b\n3.�өʴ���\n4.�e�R\n5.���}\n");	//�ﶵ�M��
			scanf_s("%d", &select);			//��J�ﶵ
		} while (select < 1 || select>5);	//��J���ﶵ�Y���b1~5�A�h���]���

		switch (select)
		{
		case 1:
			Feeding(&lv, &ex);						//����1�}��\��w�w�ﶵ1����
			break;
		case 2:
			if (lv < 2)
				printf("�٥��}�񦹥\��!!\n\n");
			else
				Accounting(&my_money, &i, myAcct);	//����2�}��\��w�w�ﶵ2�O�b
			break;
		case 5:
			return 0;								//�ﶵ5���}
			break;
		}

	} while (select != 5);							//�S������}�N�~��

	return 0;
}

void Accounting(int *money, int *i, Acct myAcct[Acct_Data])	//�O�b�Ƶ{��
{   //��J�Ȭ��ϥΪ̪����B�O�ĴX���O�b��ƪ��ܼơB�O�b���		
	int select;	//���

	do
	{
		do
		{
			printf("\n�ڪ����]�G%d��\n", *money);						//��ܿ��]����
			printf("�п�ܥ\��G\n1.��X\n2.���J\n3.�d��\n4.���}\n");	//�O�b�\����
			scanf_s("%d", &select);										//��J�ﶵ
		} while (select < 1 || select>4);			 //��J���ﶵ�Y���b1~4�A�h���]���

		switch (select)
		{
		case 1:	//��X
			if (*i == Acct_Data)	//�Y�ҰO�������̫�@�����
			{
				for (int j = 0; j < Acct_Data - 1; j++)
				{
					myAcct[j] = myAcct[j + 1];	//1~�̫�@����Ʃ��e����0~�̫�@��-1
					*i = Acct_Data - 1;			//��e�O�������=�̫�@��-1
				}
			}
			myAcct[*i].type = 'a';				//type='a'����X
			printf("�п�J��X�����B�G");
			scanf_s("%d", &myAcct[*i].money);	//��J�n��X�����B
			printf("�п�J�~/��/��(YYYY/MM/DD)\n");
			scanf_s("%d/%d/%d", &myAcct[*i].year, &myAcct[*i].month, &myAcct[*i].day);//��J��X���~���
			*money = *money - myAcct[*i].money;	//���]������X����
			printf("��%d�~%d��%d���X%d���A�ڪ����]�G%d��\n", myAcct[*i].year,
				myAcct[*i].month, myAcct[*i].day, myAcct[*i].money, *money);	//��ܤ�X���G
			*i = *i + 1;	//��e�O�������+1
			break;
		case 2:	//���J
			if (*i == Acct_Data)	//�Y�ҰO�������̫�@�����
			{
				for (int j = 0; j < Acct_Data - 1; j++)
				{
					myAcct[j] = myAcct[j + 1];	//1~�̫�@����Ʃ��e����0~�̫�@��-1
					*i = Acct_Data - 1;			//��e�O�������=�̫�@��-1
				}
			}
			myAcct[*i].type = 'b';				//type='b'�����J
			printf("�п�J���J�����B�G");
			scanf_s("%d", &myAcct[*i].money);	//��J�n��X�����B
			printf("�п�J�~/��/��(YYYY/MM/DD)\n");
			scanf_s("%d/%d/%d", &myAcct[*i].year, &myAcct[*i].month, &myAcct[*i].day);//��J���J���~���
			*money = *money + myAcct[*i].money;	//���]�[�W���J����
			printf("��%d�~%d��%d�馬�J%d���A�ڪ����]�G%d��\n", myAcct[*i].year,
				myAcct[*i].month, myAcct[*i].day, myAcct[*i].money, *money);	//��ܦ��J���G
			*i = *i + 1;	//��e�O�������+1
			break;
		case 3:	//�d��
			printf("===============================\n");
			printf(" �~  ��  ��   ��X/���J   ���B\n");	//��ܼ��D
			printf("===============================\n");
			for (int j = 0; j < *i; j++)
			{
				printf("%4d%3d%4d     %s%10d\n", myAcct[j].year, myAcct[j].month, myAcct[j].day,
					myAcct[j].type == 'a' ? "��X" : "���J", myAcct[j].money);
			} //��ܲ�0��~��e�O�������
			break;
		case 4:	//���}
			return;
			break;
		}

		printf("\n�~��O�b/���}(1/0)�G");	//�O�_�~��O�b
		scanf_s("%d", &select);				//��J�ﶵ
		printf("\n");
	} while (select != 0);	//������0�N�~��O�b
	return;	//�^��D���
}

void Feeding(int *lv, int *ex)//�����\�઺�Ƶ{��
{
	int select;
	int lim = 5;//�̰����ŬO��
	while (1)
	{
		printf("���b�i�������\��\n\n�ثe�۪��p�p�����A:LV:%d", *lv);
		for (int i = 1; i <= *ex; i++) //�C�����@���W�[�@�I�g���
		{
			printf("-");
		}
		printf("\n");
		printf("�п�ܭn����������:\n(1)���� or (2)��s or (3)�h�X       ");
		scanf_s("%d", &select);
		printf("\n");
		if (*lv == lim)
		{
			printf("�w�F���ŤW��\n");
			return;
		}
		else if (*lv < lim)//���Ťp��̰����A�~��W�[�@�I�g���
		{
			switch (select)
			{
			case 1:
				printf("�w��� ���� �W�[1�I�g���\n===================================\n");
				*ex = *ex + 1;
				break;
			case 2:
				printf("�w��� ��s �W�[1�I�g���\n===================================\n");
				*ex = *ex + 1;
				break;
			case 3:
				printf("�w�h�X\n");
				return;
				break;
			}
			if (*ex % 10 == 0)//�C�Q�I�g��ȡA�W�ɤ@��
			{
				*lv = *lv + 1;
				*ex = 0;
			}
		}

	}
}