#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct
{
	char Lastname[20];		//�c��
	char Firstname[20];		//���O
	int Age ;
	float Height;
	float weight;
}STATUS;

void Input(STATUS *pstatus);
void Output(STATUS *pstatus);

int main(void)
{
	
	bool Fg = false;
	printf("������l�f�[�^����͂��Ă��炢�܂��B\n\n");
	printf("���͂���l����ݒ肵�Ă�������(1�`10) >");
	while (Fg==false)
	{
		int number;
		scanf("%d", &number);
		if (1 <= number&& number <= 10)
		{
			STATUS status[10];
			printf("�l�f�[�^����͂��Ă�������\n\n");
			for (int i = 0; i < number; i++)
			{
				printf("%d�l�ڂ̃f�[�^����͂��Ă�������",i+1);
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
			printf("���������꒼���āA�ǂ���\n\n");
		}
	}


	rewind(stdin);
	getchar();
}


void Input(STATUS *pstatus)
{
	printf("\n�E�c������͂��Ă��������i���p���[�}���j>");
	scanf("%s", pstatus->Lastname);
	printf("\n\n�E���O����͂��Ă��������i���p���[�}���j>");
	scanf("%s", pstatus->Firstname);
	printf("\n\n�N�����͂��Ă�������");
	scanf("%d", &pstatus->Age);
	printf("\n\n�g������͂��Ă��������i�������ʂ܂�[160.5�Ȃ�]�j>");
	scanf("%f.2", &pstatus->Height);
	printf("\n\n�̏d����͂��Ă��������i�������ʂ܂�[74.5�Ȃ�]�j>");
	scanf("%f.2", &pstatus->weight);
}

void Output(STATUS *pstatus)
{
	printf("�l�f�[�^��\�����܂�");
	printf("�����F%s %s\n", pstatus->Lastname, pstatus->Firstname);
	printf("�N��F%d\n", pstatus->Age);
	printf("�g���F%.2f\n", pstatus->Height);
	printf("�̏d�F%.2f\n\n", pstatus->weight);
}
