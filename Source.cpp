#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct
{
	char Lastname[20];		//苗字
	char Firstname[20];		//名前
	int Age ;
	float Height;
	float weight;
}STATUS;

void Input(STATUS *pstatus);
void Output(STATUS *pstatus);

int main(void)
{
	
	bool Fg = false;
	printf("今から個人データを入力してもらいます。\n\n");
	printf("入力する人数を設定してください(1～10) >");
	while (Fg==false)
	{
		int number;
		scanf("%d", &number);
		if (1 <= number&& number <= 10)
		{
			STATUS status[10];
			printf("個人データを入力してください\n\n");
			for (int i = 0; i < number; i++)
			{
				printf("%d人目のデータを入力してください",i+1);
				Input(&status[i]);
			}
			for (int i = 0; i < number; i++)
			{
				Output(&status[i]);
			}
			Fg = true;
		}
		else
		{
			printf("もう一回入れ直して、どうぞ\n\n");
		}
	}


	rewind(stdin);
	getchar();
}


void Input(STATUS *pstatus)
{
	printf("\n・苗字を入力してください（半角ローマ字）>");
	scanf("%s", pstatus->Lastname);
	printf("\n\n・名前を入力してください（半角ローマ字）>");
	scanf("%s", pstatus->Firstname);
	printf("\n\n年齢を入力してください");
	scanf("%d", &pstatus->Age);
	printf("\n\n身長を入力してください（小数第一位まで[160.5など]）>");
	scanf("%f.2", &pstatus->Height);
	printf("\n\n体重を入力してください（小数第一位まで[74.5など]）>");
	scanf("%f.2", &pstatus->weight);
}

void Output(STATUS *pstatus)
{
	printf("個人データを表示します");
	printf("氏名：%s %s\n", pstatus->Lastname, pstatus->Firstname);
	printf("年齢：%d\n", pstatus->Age);
	printf("身長：%.2f\n", pstatus->Height);
	printf("体重：%.2f\n\n", pstatus->weight);
}
