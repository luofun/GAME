# include <Windows.h>  
# include <conio.h> 
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void showtitle();
void initM();
void getS();
void bullet();
void ship();
void logic();
void show();
void moveE();
void dataE(int from, int to);

int S = 0;
int T = 0;
//int Ma[50][50];
char Mc[20][50];

int m1 = 1;
int m2 = 2;
int Pos = 25;
COORD xy;

int main(int arcy, char* arcv)
{
	showtitle();

	Sleep(2000);
	system("cls");

	initM();
	dataE(10, 30);

	//getS();

	/*printf("1234567891011121314151617181920212223242526272829303132333435363738394041424344454647484950");
	printf("\n");
	putch('a');
	putch('a');
	putch('a');*/
	ship();
	show();

	while (1)
	{
		getS();
		
		if (S != 0)
		{
			system("cls");
			logic();
			moveE();
			show();
			Sleep(200);
		}
	
	}


	return 0;
}

void showtitle()
{
	printf("     _                 _   _             \n");
	printf(" ___| |__   ___   ___ | |_(_)_ __   __ _ \n");
	printf("/ __| '_ \\ / _ \\ / _ \\| __| | '_ \\ / _` |\n");
	printf("\\__ \\ | | | (_) | (_) | |_| | | | | (_| |\n");
	printf("|___/_| |_|\\___/ \\___/ \\__|_|_| |_|\\__, |\n");
	printf("                                   |___/ \n");

}

void initM()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			//Ma[i][j] = 0;
			Mc[i][j] = ' ';
		}
		Mc[1][i] = 0;
		Mc[2][i] = 0;
	}
}

void getS()
{
	if (kbhit())
		S = getch();
}

void logic()
{
	switch (S)
	{
	case 'w':
	case 'W':
		//up
		break;
	case 's':
	case 'S':
		//down
		break;
	case 'a':
	case 'A':
		//left
		Mc[19][Pos] = ' ';
		if (Pos == 0)
			Pos -= 0;
		else
			Pos -= 1;
		ship();
		break;
	case 'd':
	case 'D':
		//rigth
		Mc[19][Pos] = ' ';
		if (Pos == 49)
			Pos += 0;
		else
			Pos += 1;
		ship();
		break;
	case 'j':
	case 'J':
		//shoot
		ship();
		bullet();
		break;
	default:
		break;
	}
	//S = 0;
}

void dataE(int from, int to)
{
	for (int i = from; i < to; i++)
	{
		Mc[1][i] = '#';
		Mc[2][i] = '#';
	}
}

void moveE()
{
	if (Mc[1][0] == '#')
	
		m1 = 2;
		
	if (Mc[1][49] == '#')
	
		m1 = 1;
		
	if (m1 == 1)//left
	{
		for (int i = 0; i < 49; i++)
			Mc[1][i] = Mc[1][i + 1];
		if (Mc[1][49] == '#')
			Mc[1][49] = ' ';
			
	}
	if (m1 == 2)//right
	{
		for (int i = 49; i > 0; i--)
			Mc[1][i] = Mc[1][i - 1];
		if (Mc[1][0] == '#')
			Mc[1][0] = ' ';
	}
	if (Mc[2][0] == '#')
		m2 = 2;
	if (Mc[2][49] == '#')
		m2 = 1;
	if (m2 == 1)//left
	{
		for (int i = 0; i < 49; i++)
			Mc[2][i] = Mc[2][i + 1];
		if (Mc[2][49] == '#')
			Mc[2][49] = ' ';
	}
	if (m2 == 2)//right
	{
		for (int i = 49; i > 0; i--)
			Mc[2][i] = Mc[2][i - 1];
		if (Mc[2][0] == '#')
			Mc[2][0] = ' ';
	}
	// move 1 bit
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++)
		{
			if (i == 0 && Mc[i][j] == 'o')
			{
				Mc[i][j] = ' ';
			}
			else
				if (Mc[i][j] == 'o')
				{
					if (Mc[i - 1][j] == '#')
					{
						Mc[i][j] = ' ';
						Mc[i - 1][j] = ' ';
					}
					else
					{
						Mc[i - 1][j] = 'o';
						Mc[i][j] = ' ';
					}

				}
		}
	//move bullet;

}

void bullet()
{
	Mc[18][Pos] = 'o';
	T++;
}

void ship()
{
	Mc[19][Pos] = '@';
}

void show()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 50; j++)
			putch(Mc[i][j]);
		putch('\n');
	}
}