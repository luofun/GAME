#include"logic.h"
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
//#include"chessman.h"

int randnum(int size)
{
	return (rand() % size);
}

void printflogo(void)
{
	system("color 17");
	Sleep(1000);
	printf("\n\n\n\n\n\n\n");
	printf("\t  ____ _               _                      ___   ___   _ \n");
	printf("\t / ___| |__   ___  ___| | _____ _ __  __   __/ _ \\ / _ \\ / |\n");
	printf("\t| |   | '_ \\ / _ \\/ __| |/ / _ \\ '__| \\ \\ / / | | | | | || |\n");
	printf("\t| |___| | | |  __/ (__|   <  __/ |     \\ V /| |_| | |_| || |\n");
	printf("\t \\____|_| |_|\\___|\\___|_|\\_\\___|_|      \\_/  \\___(_)___(_)_|\n\n");
	Sleep(5000);
	system("cls");
	printf("\nhello i'm chess-master\n\n");
}

void getposmove(int* a)
{
	int temp[2] = { -1, -1 };
	printf("\ninput your chess's pos, first y second x\n");
	
	scanf("%d %d", &(temp[0]), &(temp[1]));

	while (!(temp[0] < 10 && temp[0] >= 0 && (temp[0] + temp[1]) % 2 == 0 && temp[1] < 10 && temp[1] >= 0))
	{
		printf("\n wrong input new\n");
		scanf("%d %d", &(temp[0]), &(temp[1]));
	}
	a[0] = temp[0];
	a[1] = temp[1];
}

int checkposeat(int board[10][10], int color, pos &xy)
{
	int count = 0;
	
	if (color == 0)
	{
		if (xy.x > 1 && xy.y > 1)
			if (board[xy.y - 1][xy.x - 1] / 100 == 2 && board[xy.y - 2][xy.x - 2] == 1)
			{
				xy.angle.lu = 1;
				count++;
			}
		if (xy.x < 8 && xy.y > 1)
			if (board[xy.y - 1][xy.x + 1] / 100 == 2 && board[xy.y - 2][xy.x + 2] == 1)
			{
				xy.angle.ru = 1;
				count++;
			}
		if (xy.x > 1 && xy.y < 8)
			if (board[xy.y + 1][xy.x - 1] / 100 == 2 && board[xy.y + 2][xy.x - 2] == 1)
			{
				xy.angle.ld = 1;
				count++;
			}
		if (xy.x < 8 && xy.y < 8)
			if (board[xy.y + 1][xy.x + 1] / 100 == 2 && board[xy.y + 2][xy.x + 2] == 1)
			{
				xy.angle.rd = 1;
				count++;
			}
	}
	else if (color == 1)
	{
		if (xy.x > 1 && xy.y > 1)
			if (board[xy.y - 1][xy.x - 1] / 100 == 1 && board[xy.y - 2][xy.x - 2] == 1)
			{
				xy.angle.lu = 1;
				count++;
			}
		if (xy.x < 8 && xy.y > 1)
			if (board[xy.y - 1][xy.x + 1] / 100 == 1 && board[xy.y - 2][xy.x + 2] == 1)
			{
				xy.angle.ru = 1;
				count++;
			}
		if (xy.x > 1 && xy.y < 8)
			if (board[xy.y + 1][xy.x - 1] / 100 == 1 && board[xy.y + 2][xy.x - 2] == 1)
			{
				xy.angle.ld = 1;
				count++;
			}
		if (xy.x < 8 && xy.y < 8)
			if (board[xy.y + 1][xy.x + 1] / 100 == 1 && board[xy.y + 2][xy.x + 2] == 1)
			{
				xy.angle.rd = 1;
				count++;
			}
	}
	
	return count;
}

int checkposkingeat(int board[10][10], int color, pos &xy)
{
	int count = 0;
	
		if (color == 0)
		{
			for (int i = 1; (xy.x - i > 0) && (xy.y - i > 0); i++)
			{
				if (board[xy.y - i][xy.x - i] / 100 == 1)
					break;
				if (board[xy.y - i][xy.x - i] / 100 == 2)
				{
					if (board[xy.y - i - 1][xy.x - i - 1] / 100 == 2)
						break;
					if (board[xy.y - i - 1][xy.x - i - 1] == 1)
					{
						xy.angle.lu = 1;
						count++;
						break;
					}
				}
			}

			for (int i = 1; (xy.x + i < 9) && (xy.y - i > 0); i++)
			{
				if (board[xy.y - i][xy.x + i] / 100 == 1)
					break;
				if (board[xy.y - i][xy.x + i] / 100 == 2)
				{
					if (board[xy.y - i - 1][xy.x + i + 1] / 100 == 2)
						break;
					if (board[xy.y - i - 1][xy.x + i + 1] == 1)
					{
						xy.angle.ru = 1;
						count++;
						break;
					}
				}
			}

			for (int i = 1; (xy.x - i > 0) && (xy.y + i < 9); i++)
			{
				if (board[xy.y + i][xy.x - i] / 100 == 1)
					break;
				if (board[xy.y + i][xy.x - i] / 100 == 2)
				{
					if (board[xy.y + i + 1][xy.x - i - 1] / 100 == 2)
						break;
					if (board[xy.y + i + 1][xy.x - i - 1] == 1)
					{
						xy.angle.ld = 1;
						count++;
						break;
					}
				}
			}

			for (int i = 1; (xy.x + i < 9) && (xy.y + i < 9); i++)
			{
				if (board[xy.y + i][xy.x + i] / 100 == 1)
					break;
				if (board[xy.y + i][xy.x + i] / 100 == 2)
				{
					if (board[xy.y + i + 1][xy.x + i + 1] / 100 == 2)
						break;
					if (board[xy.y + i + 1][xy.x + i + 1] == 1)
					{
						xy.angle.rd = 1;
						count++;
						break;
					}
				}
			}
		}

		if (color == 1)
		{
			for (int i = 1; (xy.x - i > 0) && (xy.y - i > 0); i++)
			{
				if (board[xy.y - i][xy.x - i] / 100 == 2)
					break;
				if (board[xy.y - i][xy.x - i] / 100 == 1)
				{
					if (board[xy.y - i - 1][xy.x - i - 1] / 100 == 1)
						break;
					if (board[xy.y - i - 1][xy.x - i - 1] == 1)
					{
						xy.angle.lu = 1;
						count++;
						break;
					}
				}
			}

			for (int i = 1; (xy.x + i < 9) && (xy.y - i > 0); i++)
			{
				if (board[xy.y - i][xy.x + i] / 100 == 2)
					break;
				if (board[xy.y - i][xy.x + i] / 100 == 1)
				{
					if (board[xy.y - i - 1][xy.x + i + 1] / 100 == 1)
						break;
					if (board[xy.y - i - 1][xy.x + i + 1] == 1)
					{
						xy.angle.ru = 1;
						count++;
						break;
					}
				}
			}

			for (int i = 1; (xy.x - i > 0) && (xy.y + i < 9); i++)
			{
				if (board[xy.y + i][xy.x - i] / 100 == 2)
					break;
				if (board[xy.y + i][xy.x - i] / 100 == 1)
				{
					if (board[xy.y + i + 1][xy.x - i - 1] / 100 == 1)
						break;
					if (board[xy.y + i + 1][xy.x - i - 1] == 1)
					{
						xy.angle.ld = 1;
						count++;
						break;
					}
				}
			}

			for (int i = 1; (xy.x + i < 9) && (xy.y + i < 9); i++)
			{
				if (board[xy.y + i][xy.x + i] / 100 == 2)
					break;
				if (board[xy.y + i][xy.x + i] / 100 == 1)
				{
					if (board[xy.y + i + 1][xy.x + i + 1] / 100 == 1)
						break;
					if (board[xy.y + i + 1][xy.x + i + 1] == 1)
					{
						xy.angle.rd = 1;
						count++;
						break;
					}
				}
			}
		}
	
	
	return count;
}

void resetxy(pos &xy)
{
	xy.angle.ld = 0;
	xy.angle.lu = 0;
	xy.angle.rd = 0;
	xy.angle.ru = 0;
	xy.past = -1;
	xy.x = -1;
	xy.y = -1;
	xy.jumplong = 0;
}

int selectponit(int *a, chessman *AB, int board[10][10])
{
	int temppoi;
	
	printf("put your selectpoint: ");
	scanf("%d", &temppoi);
	while (temppoi > 20 || temppoi < 0 || AB[temppoi].thisround != 1)//need to add the justice for point
	{
		printf("wrong point, input again: ");
		scanf("%d", &temppoi);
	}

	getposmove(a);

	while ((board[a[0]][a[1]] > 1))//need to change
	{
		printf("put on other chessman, try again\n");
		getposmove(a);
	}
	return temppoi;
	
}