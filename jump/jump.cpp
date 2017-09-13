#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#ifdef _DEBUG
#include<assert.h>
#endif // _DEBUG


char c1[5][5] = { { '_', '_', '#', '_', '_' },
{ '_', '#', '#', '#', '_' },
{ '_', '_', '#', '_', '_' },
{ '_', '_', '#', '_', '_' },
{ '_', '#', '_', '#', '_' } };
char t1[5][5];
char bg1[20][81];
char bg2[20][81];
int jumproad[3] = { 0 };
//char bg3[20][81];


void show1(IN char bg[][81], IN int hsize)
{
	for (int i = 0; i < hsize; i++)
	{
		printf("%s", bg[i]);
	}
}

void clearsrccen()
{
	system("cls");

}

void sdelay(IN float second)
{
	Sleep((unsigned long)(second * 1000));
}

int buttondown(void) {
	int key;

	if (_kbhit())
	{
		key = getch();
		switch (key)
		{
		case 32:
			return 1;
			//break;
		case 'q':
			return -1;
			//break;
		default:
			return 0;
			//break;
		}


	}


}

int myrand(IN int value)
{
	return rand() % value;
}

void datainit(IN OUT char bg[][81]) {
	memset(bg, '_', sizeof(char) * 81 * 20);
	for (int i = 0; i < 20; i++)
	{
		bg[i][80] = '\0';
	}
};

void inittree(IN OUT char t[][5]) {
	for (int x = 0; x < 5; x++)
	{
		for (int i = 0; i < 5; i++)
		{
			t[x][i] = '_';
		}
	}
};

void jumpinit(IN OUT int* road) {
	road[0] = 0;
	road[1] = 0;
	road[2] = 0;
}

void gameinit(void) {
	clearsrccen();
	srand(time(NULL));
	datainit(bg1);
	datainit(bg2);
	inittree(t1);
	jumpinit(jumproad);
}

void addbg1(IN OUT char bg[][81], IN char c[][5], IN int hpos) {
#ifdef _DEBUG
	assert(hpos >= 0);
#endif // _DEBUG

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			bg[15 - hpos + i][10 + j] = c[i][j];
		}
	}

};

int addbg2(IN OUT char bg[][81], IN char t[][5], IN int lpos, IN int num) {
#ifdef _DEBUG
	assert(lpos >= 0);
#endif // _DEBUG
	int sign = 0;

	for (int x = 0; x < num; x++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (bg[15 + i][79 - lpos - x] == '#' && t[x][i] != '_')
			{
				sign = 1;
			}
			if (bg[15 + i][79 - lpos - x] == '#'&&t[x][i] == '_')
			{
				bg[15 + i][79 - lpos - x] = '#';
			}
			else
			{
				bg[15 + i][79 - lpos - x] = t[x][i];
			}
		}
	}
	return sign;
};

int addbg(IN char bgbasic[][81], IN OUT char bg[][81], IN int hpos, IN int lpos, IN int num) {
	for (int i = 0; i<20; i++)
		for (int j = 0; j < 81; j++)
		{
			bg[i][j] = bgbasic[i][j];

		}
	addbg1(bg, c1, hpos);
	return addbg2(bg, t1, lpos, num);
};


int createneewtree(IN int num, IN int tall, IN OUT char t[][5]) {
	//assert(num<=5&&tall<=5)

	for (int i = 0; i < num; i++)
		for (int j = 4; j >= 4 - tall + 1; j--)
		{
			if (j == 4 - tall + 1)
				t[i][j] = '^';
			else
				t[i][j] = '|';
		}
	return num;
};

int createrandtalltree(IN int num, IN OUT char t[][5]) {

	int tall;

	for (int i = 0; i < num; i++)
	{
		tall = myrand(3) + 1;
		for (int j = 4; j >= 4 - tall + 1; j--)
		{
			if (j == 4 - tall + 1)
				t[i][j] = '^';
			else
				t[i][j] = '|';
		}
	}
	return num;
};

int createrandnumtree(IN int tall, IN OUT char t[][5]){
	int num = myrand(5) + 1;

	for (int i = 0; i < num; i++)
		for (int j = 4; j >= 4 - tall + 1; j--)
		{
			if (j == 4 - tall + 1)
				t[i][j] = '^';
			else
				t[i][j] = '|';
		}

	return num;
};

int jump(IN OUT int* road) {
	road[0] = myrand(3) + 2;
	road[1] = myrand(3) + 2;
	road[2] = myrand(3) + 2;
	return road[0] + road[1] + road[2];
}

void gameend(IN int socre) {
	clearsrccen();
	show1(bg2, 20);
	printf("\nend, sorce = %d\n\n", socre);
};

void gamebegin() {
	gameinit();
	int high = 0;
	int jumpstep = 0;
	int number = myrand(5) + 1;
	int i = 0;
	int jumpsign = 0;
	int curshsign = 0;
	int keysign = 0;
	int sorce = 0;

	createrandtalltree(number, t1);

	while (1)
	{
		sdelay(0.1);
		keysign = buttondown();

		if (keysign == -1)
		{
			clearsrccen();
			show1(bg2, 20);
			printf("\nend\n");
			break;
		}
		if (keysign == 1)
		{
			high = jump(jumproad);
			jumpsign = 1;
		}

		if (i < 79 - number + 1)
		{
			if (jumpsign == 1)
			{
				jumpstep = 0;
				keysign = 0;

				for (int x = 0; x < 3; x++)
				{
					jumpstep += jumproad[x];

					curshsign = addbg(bg1, bg2, jumpstep, i, number);
					if (curshsign == 1)
					{
						gameend(sorce);
						return;
					}
					clearsrccen();
					show1(bg2, 20);
					i++;
					if (i >= 79 - number + 1)
					{
						i = 0;
						number = myrand(5) + 1;
						inittree(t1);
						createrandtalltree(number, t1);
						sorce += 10;
					}
					sdelay(0.1);
				}

				for (int x = high - 1; x > 0; x--)
				{
					curshsign = addbg(bg1, bg2, x, i, number);
					if (curshsign == 1)
					{
						gameend(sorce);
						return;
					}
					clearsrccen();
					show1(bg2, 20);
					i++;
					if (i >= 79 - number + 1)
					{
						i = 0;
						number = myrand(5) + 1;
						inittree(t1);
						createrandtalltree(number, t1);
						sorce += 10;
					}
					sdelay(0.1);
				}
				jumpinit(jumproad);
			}

			clearsrccen();
			curshsign = addbg(bg1, bg2, 0, i, number);
			if (curshsign == 1)
			{
				gameend(sorce);
				return;
			}
			show1(bg2, 20);
			jumpsign = 0;
		}
		else
		{
			i = 0;
			number = myrand(5) + 1;
			inittree(t1);
			createrandtalltree(number, t1);
			sorce += 10;
		}

		i++;
	}
}

void main() {
	gamebegin();

}




