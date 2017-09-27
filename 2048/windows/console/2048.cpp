#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<winsock2.h>
#include<Windows.h>  
#include<conio.h> 

int testrand(int seed);
int randnum(int msize);
void initscreen();
int** init(int msize);
void show(int** matrix);
void logic(int** matrix, int sign);
void getsign(int* sign);
int haveaempty(int** matrix);
void putrand(int** matrix);

COORD coord;
int T = 0;
int S = 0;

int main(int arcy, char* arcv)
{
	int** matrix = NULL;
	srand(time(NULL));
	putch('\n');
	printf(" ____   ___  _  _    ___  \n");
	printf("|___ \\ / _ \\| || |  ( _ ) \n");
	printf("  __) | | | | || |_ / _ \\ \n");
	printf(" / __/| |_| |__   _| (_) |\n");
	printf("|_____|\\___/   |_|  \\___/ \n");//2048 logo

	Sleep(2000);
	system("cls");

	matrix = init(4);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			printf("matrix=%4d\n", matrix[i][j]);
	Sleep(1000);
	system("cls");

	putrand(matrix);
	putrand(matrix);
	initscreen();
	show(matrix);
	while (1)
	{
		getsign(&S);
		if (T == 1)
		{
			logic(matrix, S);
			if (haveaempty(matrix))
				putrand(matrix);
			else
				break;
			show(matrix);
		}
		
	}
	

	return 0;
}

int** init(int msize)
{
	int** tm;
	tm = (int**)malloc(msize*sizeof(int*));
	for (int i = 0; i < msize; i++)
		tm[i] = (int*)malloc(msize*sizeof(int));
	for (int i = 0; i < msize; i++)
		for (int j = 0; j < msize; j++)
			tm[i][j] = 0;
	return tm;
}

void freeall(int** matrix, int msize)
{
	for (int i = 0; i < msize; i++)
		free(matrix[i]);
	free(matrix);
}

int randnum(int msize)
{
	int num;
	num = rand() % (msize*msize);
	return num;
}//work!

int testrand(int seed)
{
	int num;
	num = (seed * 16807L) % (16);
	return num;
}

void initscreen()
{
	printf("++    ++    ++    ++    ++\n++++++++++++++++++++++++++\n++    ++    ++    ++    ++\n++++++++++++++++++++++++++\n++    ++    ++    ++    ++\n++++++++++++++++++++++++++\n++    ++    ++    ++    ++\n");
}

void logic(int** matrix, int sign)
{
	int index;
	int index2;
	T = 0;
	switch (sign)
	{
	case 1:
		//up
		for (int j = 0; j < 4; j++)
		{
			index = -1;
			for (int i = 0; i < 4; i++)
			{
				if (matrix[i][j] == 0)
					continue;
				else
					if (index == -1)
						index = i;
					else
						if (matrix[i][j] == matrix[index][j])
						{
							matrix[index][j] += matrix[i][j];
							matrix[i][j] = 0;
							index = -1;
						}
						else
							index = i;

			}
			index2 = 0;
			for (int i = 0; i < 4; i++)
			{
				if (matrix[i][j] != 0)
					if (i != index2)
					{
						matrix[index2][j] = matrix[i][j];
						matrix[i][j] = 0;
						index2++;
					}
					else
						index2++;
			}
		}
		break;
	case 2:
		//down;
		for (int j = 0; j < 4; j++)
		{
			index = -1;
			for (int i = 0; i < 4; i++)
			{
				if (matrix[3 - i][j] == 0)
					continue;
				else
					if (index == -1)
						index = 3 - i;
					else
						if (matrix[3 - i][j] == matrix[index][j])
						{
							matrix[index][j] += matrix[3 - i][j];
							matrix[3 - i][j] = 0;
							index = -1;
						}
						else
							index = 3 - i;

			}
			index2 = 3;
			for (int i = 0; i < 4; i++)
			{
				if (matrix[3 - i][j] != 0)
					if ((3 - i) != index2)
					{
						matrix[index2][j] = matrix[3 - i][j];
						matrix[3 - i][j] = 0;
						index2--;
					}
					else
						index2--;
			}
		}
		break;
	case 3:
		//left
		for (int i = 0; i < 4; i++)
		{
			index = -1;
			for (int j = 0; j < 4; j++)
			{
				if (matrix[i][j] == 0)
					continue;
				else
					if (index == -1)
						index = j;
					else
						if (matrix[i][j] == matrix[i][index])
						{
							matrix[i][index] += matrix[i][j];
							matrix[i][j] = 0;
							index = -1;
						}
						else
							index = j;

			}
			index2 = 0;
			for (int j = 0; j < 4; j++)
			{
				if (matrix[i][j] != 0)
					if (j != index2)
					{
						matrix[i][index2] = matrix[i][j];
						matrix[i][j] = 0;
						index2++;
					}
					else
						index2++;
			}
		}
		break;
	case 4:
		//right
		for (int i = 0; i < 4; i++)
		{
			index = -1;
			for (int j = 0; j < 4; j++)
			{
				if (matrix[i][3 - j] == 0)
					continue;
				else
					if (index == -1)
						index = 3 - j;
					else
						if (matrix[i][3 - j] == matrix[i][index])
						{
							matrix[i][index] += matrix[i][3 - j];
							matrix[i][3 - j] = 0;
							index = -1;
						}
						else
							index = 3 - j;

			}
			index2 = 3;
			for (int j = 0; j < 4; j++)
			{
				if (matrix[i][3 - j] != 0)
					if ((3 - j) != index2)
					{
						matrix[i][index2] = matrix[i][3 - j];
						matrix[i][3 - j] = 0;
						index2--;
					}
					else
						index2--;
			}
		}
		break;
	default:
		break;
	}
}

void getsign(int* sign)
{
	if (kbhit())
	{
		*sign = getch();
		T = 1;
	}
	else
		T = 0;

	switch (*sign)
	{
	case 'w':
	case 'W':
		//up
		*sign = 1;
		break;
	case 's':
	case 'S':
		//down
		*sign = 2;
		break;
	case 'a':
	case 'A':
		//left
		*sign = 3;
		break;
	case 'd':
	case 'D':
		//rigth
		*sign = 4;
		break;
	default:
		*sign = 0;
		break;
	}
}

void show(int** matrix)
{
	for (int i = 0; i < 4; i++)
	{
		coord.X = 2;
		coord.Y = i * 2;
		for (int j = 0; j < 4; j++)
		{
			
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			printf("%04d",matrix[i][j]);
			coord.X += 6;
		
		}

	}
}

void putrand(int** matrix)
{
	int x, y;
	x = randnum(2);
	y = randnum(2);
	while (1)
	{
		if (matrix[x][y] == 0)
		{
			matrix[x][y] = 2;
			break;
		}
		else
		{
			x = randnum(2);
			y = randnum(2);
		}
	}

}

int haveaempty(int** matrix)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (matrix[i][j] == 0)
				return 1;
	return 0;
}
