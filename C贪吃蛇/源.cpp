#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<stdio.h>

#define U 1
#define D 2
#define L 3
#define R 4
typedef struct SNAKE
{
	int x;
	int y;
	struct SNAKE *next;
}snake;
int score = 0, add = 10;
int status, sleeptime = 200;
snake *head, *food;
snake *q;
int endgamestatus = 0;
void Pos(int x,int y);
void creatMap();
void initsnake();
int biteself();
void createfood();
void cantcrosswall();
void snakemove();
void pause();
void gamecircle();
void welcometogame();
void endgame();
void gamestart();
HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
void Pos(int x, int y)
{
	COORD pos;
	HANDLE houtput;
	pos.X = x;
	pos.Y = y;
	houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(houtput, pos);
}
void creatMap()
{
	int i,j;
	for (i = 0; i < 58; i += 2)
	{
		for (j = 0; j < 26; j++)
		{
			Pos(i, j);
			//SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("��");
		}
	}
}
void initsnake()
{
	snake *tail;
	int i;
	tail = (snake*)malloc(sizeof(snake));
	tail->x = 24;
	tail->y = 5;
	tail->next = NULL;
	for (i = 1; i <= 4; i++)
	{
		head = (snake*)malloc(sizeof(snake));
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = 5;
		tail = head;
	}
	while (tail != NULL)
	{
		Pos(tail->x, tail->y);
		printf("��");
		tail = tail->next;
	}
}
int biteself()
{
	snake *self;
	self = head->next;
	while (self != NULL)
	{
		if (self->x == head->x&&self->y == head->y)
		{
			return 1;
		}

		self = self->next;
	}
	return 0;
}
void createfood()

{

	snake *food_1;

	srand((unsigned)time(NULL));

	food_1 = (snake*)malloc(sizeof(snake));

	while ((food_1->x % 2) != 0)    //��֤��Ϊż����ʹ��ʳ��������ͷ����

	{

		food_1->x = rand() % 52 + 2;

	}

	food_1->y = rand() % 24 + 1;

	q = head;

	while (q->next !=NULL)

	{

		if (q->x == food_1->x && q->y == food_1->y) //�ж������Ƿ���ʳ���غ�

		{

			free(food_1);

			createfood();
			q = head;

		}

		q = q->next;

	}

	Pos(food_1->x, food_1->y);

	food = food_1;
	SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED |FOREGROUND_BLUE);
	printf("��");
	SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

}


void cantcrosswall()
{
	if (head->x == 0 || head->x ==56 || head->y == 0 || head->y == 26)
	{
		endgamestatus = 1;
		 endgame();
	}
}
void snakemove()
{
	snake *nexthead;
	cantcrosswall();
	nexthead = (snake*)malloc(sizeof(snake));
	if (status == U)
	{
		SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		nexthead->x = head->x;
		nexthead->y = head->y - 1; 
		if (nexthead->x == food->x&&nexthead->y == food->y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			Pos(q->x, q->y);
			printf("��");
			score = score + add;
			createfood();
		}
		else
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("��");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("��");
			SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
			free(q->next);
			q->next = NULL;
		}
	}
	if (status== D)
	{
		SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		nexthead->x = head->x;
		nexthead->y = head->y + 1;
		if (nexthead->x == food->x&&nexthead->y == food->y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != head)
			{
				Pos(q->x, q->y);
				//SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );
				printf("��");
				q = q->next;
			}
			score = score + add;
			createfood();
		}
		else
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("��");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("��");
			SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == L)
	{
		SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE );
		nexthead->x = head->x-2;
		nexthead->y = head->y;
		if (nexthead->x == food->x&&nexthead->y == food->y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != head)
			{
				Pos(q->x, q->y);
				printf("��");
				q = q->next;
			}
			score = score + add;
			createfood();
		}
		else
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("��");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("��");
			SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
			free(q->next);
			q->next = NULL;
		}
	}
	if (status == R)
	{
		SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
		nexthead->x = head->x+2;
		nexthead->y = head->y;
		if (nexthead->x == food->x&&nexthead->y == food->y)
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q != head)
			{
				Pos(q->x, q->y);
				printf("��");
				q = q->next;
			}
			score = score + add;
			createfood();
		}
		else
		{
			nexthead->next = head;
			head = nexthead;
			q = head;
			while (q->next->next != NULL)
			{
				Pos(q->x, q->y);
				printf("��");
				q = q->next;
			}
			Pos(q->next->x, q->next->y);
			SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("��");
			SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
			free(q->next);
			q->next = NULL;
		}
	}
	if (biteself() == 1)
	{
		endgamestatus = 1;
		endgame();
	}
}
void pause()
{
	while (1)
	{
		Sleep(300);
		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}
	}

}
void gamecircle()
{
	Pos(64, 15);
	//SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_RED);
	printf("���ܴ�ǽ������ҧ���Լ�\n");
	Pos(64, 16);
	printf("�á�.��.��.���ֱ�����ߵ��ƶ�\n");
	Pos(64, 17);
	printf("f1���٣�f2����\n");
	Pos(64, 18);
	printf("esc:�˳���Ϸ��space����ͣ��Ϸ\n");
	status = R;
	while (1)
	{
		Pos(64, 10);
		printf("�÷֣�%d", score);
		Pos(64, 11);
		printf("ÿ��ʳ��÷֣�%d", add);
		if (GetAsyncKeyState(VK_UP) && status != D)
		{
			status = U;
		}
		else if (GetAsyncKeyState(VK_DOWN) && status != U)
		{
			status = D;
		}
		else if (GetAsyncKeyState(VK_LEFT) && status != R)
		{
			status = L;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && status != L)
		{
			status = R;
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			 pause();
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			endgamestatus = 1;
			break;
		}
		else if (GetAsyncKeyState(VK_F1))
		{
			if (sleeptime >= 50)
			{
				sleeptime -= 30;
				add += 2;
				if (sleeptime == 320)
				{
					add = 2;
				}
			}
		}
		else if (GetAsyncKeyState(VK_F2))
		{
			if (sleeptime < 350)
			{
				sleeptime =sleeptime+ 30;
				add =add+ 2;
				if (sleeptime == 350)
				{
					add = 1;
				}
			}
		}
		Sleep(sleeptime);
		SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	    snakemove();

	}
	
}



void welcometogame()//��ʼ����

{

	Pos(40, 12);



	system("title ̰����");
	SetConsoleTextAttribute(Handle, FOREGROUND_RED);

	//printf("��ӭ����̰ʳ����Ϸ��");
	Pos(5, 10); printf("                                                                                   ");
	Pos(5, 11); printf(" ��      ��      ��  ��������  ��        ������    ������        ��      ��      ��������   ");
	Pos(5, 12); printf(" ��      ��      ��  ��        ��       ��        ��      ��   ��  ��  ��  ��    ��    ");
	Pos(5, 13); printf("   ��  ��  ��  ��    ��������  ��       ��        ��      ��   ��  ��  ��  ��    ��������  ");
	Pos(5, 14); printf("   ��  ��  ��  ��    ��        ��       ��        ��      �� ��      ��      ��  ��  ");
	Pos(5, 15); printf("     ��      ��      ��������  ��������   ������    ������   ��      ��      ��  ��������  ");
	SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	Pos(40, 25);
	system("pause");

	system("cls");

	Pos(25, 12);

	printf("�á�.��.��.���ֱ�����ߵ��ƶ��� F1 Ϊ���٣�2 Ϊ����\n");

	Pos(25, 13);

	printf("���ٽ��ܵõ����ߵķ�����\n");

	system("pause");

	system("cls");

}



void endgame()//������Ϸ

{



	system("cls");

	Pos(45, 12);

	if (endgamestatus == 1)

	{
		SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_RED);

		//printf("��Ϸ����");
		Pos(20, 10); printf("                                                        ");
		Pos(20, 11); printf("    ������      ��      ��      ��������      ��������  ");
		Pos(20, 12); printf("  ��      ��    ��      ��      ��            ��    ��  ");
		Pos(20, 13); printf("  ��      ��      ��  ��        ��������      ��������  ");
		Pos(20, 14); printf("  ��      ��      ��  ��        ��            ����      ");
		Pos(20, 15); printf("    ������          ��          ��������      ��  ����   ");

	}

	/*else if (endgamestatus == 2)

	{

		printf("�Բ�����ҧ���Լ��ˡ���Ϸ����.");

	}

	else if (endgamestatus == 3)

	{

		printf("�����Ѿ���������Ϸ��");

	}*/

	Pos(43, 20);

	printf("���ĵ÷���%2d\n", score);

	exit(0);

}



void gamestart()//��Ϸ��ʼ��

{

	system("mode con cols=100 lines=30");

	welcometogame();

	creatMap();

	initsnake();

	createfood();

}



int main()

{
	gamestart();

	gamecircle();

	endgame();

	return 0;

}
