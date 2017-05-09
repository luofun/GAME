#include"chessboard.h"
#include<stdio.h>
#include <algorithm>
#include<time.h>
#include<Windows.h>

chessboard::chessboard()
{
	initchessman();
	initboard(10);
};

chessboard::~chessboard()
{
	delete[] A;
	delete[] B;
};

void chessboard::initchessman()
{
	A = new chessman[20];
	B = new chessman[20];
	for (int i = 0; i < 20; i++)
	{
		A[i].color = 0;
		B[i].color = 1;
		A[i].num = i;
		B[i].num = i;
		if (i < 5)
		{
			A[i].xy.x = 2 * i;
			A[i].xy.y = 0;
			B[i].xy.x = 2 * i;
			B[i].xy.y = 6;
		}
		else if (i < 10)
		{
			A[i].xy.x = 1 + 2 * (i - 5);
			A[i].xy.y = 1;
			B[i].xy.x = 1 + 2 * (i - 5);
			B[i].xy.y = 7;
		}
		else if (i < 15)
		{
			A[i].xy.x = 2 * (i - 10);
			A[i].xy.y = 2;
			B[i].xy.x = 2 * (i - 10);
			B[i].xy.y = 8;
		}
		else if (i < 20)
		{
			A[i].xy.x = 1 + 2 * (i - 15);
			A[i].xy.y = 3;
			B[i].xy.x = 1 + 2 * (i - 15);
			B[i].xy.y = 9;
		}
	}
};

void chessboard::initboard(int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if ((i + j) % 2 == 0)
			{
				bborad[i][j] = 1;
				borad[i][j] = 1;
			}
			else
			{
				bborad[i][j] = 0;
				borad[i][j] = 0;
			}
};

void chessboard::showbboard()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			printf("%d\t", this->bborad[i][j]);
		printf("\n");
	}
}

void chessboard::showboard()
{
	printf("   0\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d  ", i);
		for (int j = 0; j < 10; j++)
			printf("%d\t", this->borad[i][j]);
		printf("\n");
	}
}

void chessboard::testchess()
{
	printf("\n\ntest the chess valude\n\n");
	for (int i = 0; i < 20; i++)
	{
		printf("A[%d].num=%d \\.xy=%d %d \\.color=%d \\.bee=%d \\.fe=%d \\.cj=%d \\.ik=%d\n", i, A[i].num, A[i].xy.x, A[i].xy.y, A[i].color, A[i].thisround, A[i].fieat, A[i].canj, A[i].isking);		
	}
	printf("\n\n");
	for (int i = 0; i < 20; i++)
	{
		printf("B[%d].num=%d \\.xy=%d %d \\.color=%d \\.bee=%d \\.fe=%d \\.cj=%d \\.ik=%d\n", i, B[i].num, B[i].xy.x, B[i].xy.y, B[i].color, B[i].thisround, B[i].fieat, B[i].canj, B[i].isking);
	}
}

void chessboard::updateboard()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			borad[i][j] = bborad[i][j];
	for (int i = 0; i < 20; i++)
	{
		if (A[i].fieat == 0)
		{
			borad[A[i].xy.y][A[i].xy.x] = 100 + A[i].num;
		}
		if (B[i].fieat == 0)
		{
			borad[B[i].xy.y][B[i].xy.x] = 200 + B[i].num;
		}
	}
}

int chessboard::checkfail()
{
	int sign = 0, num = 0, count = 0;
	for (int i = 0; i < 20; i++)
	{
		if (A[i].fieat == 1)
			num++;
		if (A[i].checkeat(borad) > 0 || A[i].checkmove(borad) > 0)
			count++;
		if (A[i].checkkingeat(borad) > 0 || A[i].checkkingmove(borad) > 0)
			count++;
	}
	if (num == 20)
		sign = 1;
	if (count == 0)
		sign = 1;

	num = 0;
	count = 0;
	for (int i = 0; i < 20; i++)
	{
		if (B[i].fieat == 1)
			num++;
		if (B[i].checkeat(borad) > 0 || B[i].checkmove(borad) > 0)
			count++;
		if (B[i].checkkingeat(borad) > 0 || B[i].checkkingmove(borad) > 0)
			count++;
	}
	if (num == 20)
		sign = 2;
	if (count == 0)
		sign = 2;

	return sign;
}

int chessboard::checkall(int incolor)
{
	int tempsign = 0;
	int a = 0;
	int failsign = 0;
	
	if (incolor == 0)
	{
		a = 0;
		for (int i = 0; i < 20; i++)
		{
			
			A[i].checkeat(borad);
			A[i].checkkingeat(borad);
			
			if (A[i].canj > 0)
			{
				tempsign = 1;
			}
			
		}

		if (tempsign == 0)
		{
			for (int i = 0; i < 20; i++)
			{
				A[i].checkmove(borad);
				A[i].checkkingmove(borad);
			}
		}
		for (int i = 0; i < 20; i++)
		{
			A[i].changethiround();
		}
		for (int i = 0; i < 20; i++)
		{
			if (A[i].thisround > 0)
			{
				a = 1;
			}
		}
		if (a != 1)
			failsign = 1;
		resetthisroundsign(incolor);
		return failsign;
	}
	if (incolor == 1)
	{
		a = 0;
		for (int i = 0; i < 20; i++)
		{
			B[i].checkeat(borad);
			B[i].checkkingeat(borad);

			if (B[i].canj > 0)
			{
				tempsign = 1;
			}
		}

		if (tempsign == 0)
		{
			for (int i = 0; i < 20; i++)
			{
				B[i].checkmove(borad);
				B[i].checkkingmove(borad);
			}
		}
		for (int i = 0; i < 20; i++)
		{
			B[i].changethiround();
		}
		for (int i = 0; i < 20; i++)
		{
			if (B[i].thisround > 0)
			{
				a = 1;
			}
		}
		if (a != 1)
			failsign = 2;
		resetthisroundsign(incolor);
		return failsign;
	}
	resetthisroundsign(incolor);
	return failsign;
}

void chessboard::clearABvalue()
{
	for (int i = 0; i < 20; i++)
	{
		A[i].clearsign();
		
		B[i].clearsign();
	}
}

void chessboard::resetthisroundsign(int incolor)
{
	std::vector<int>::iterator temp1;
	std::vector<int> Vuse;
	std::vector<pos> Vtemppos;
	int temp = 0;
	
	if (incolor == 0)
	{
		
		for (int i = 0; i < 20; i++)
		{
			if (A[i].isking == 0)
				Vuse.push_back(A[i].findjumplong(borad, incolor, Vtemppos).jumplong);
			if (A[i].isking == 1)
				Vuse.push_back(A[i].findkingjumplong(borad, incolor, Vtemppos).jumplong);
		}
		std::vector<int>::iterator temp1 = std::max_element(std::begin(Vuse), std::end(Vuse));
		temp = *temp1;
		for (int i = 0; i < 20; i++)
		{
			if (Vuse[i] != temp)
			{
				A[i].thisround = 0;
			}
		}
	}

	if (incolor == 1)
	{
		
		for (int i = 0; i < 20; i++)
		{
			if (B[i].isking == 0)
				Vuse.push_back(B[i].findjumplong(borad, incolor, Vtemppos).jumplong);
			if (B[i].isking == 1)
				Vuse.push_back(B[i].findkingjumplong(borad, incolor, Vtemppos).jumplong);
		}
		std::vector<int>::iterator temp1 = std::max_element(std::begin(Vuse), std::end(Vuse));
		temp = *temp1;
		for (int i = 0; i < 20; i++)
		{
			if (Vuse[i] != temp)
			{
				B[i].thisround = 0;
			}
		}
		
	}
}


int chessboard::randomchoose(int incolor)
{
	int count = 0;
	int temp = 0;
	if (incolor == 0)
	{
		for (int i = 0; i < 20; i++)
		{
			if (A[i].thisround == 1)
			{
				count++;
			}
		}
		temp = randnum(count);
		count = 0;
		for (int i = 0; i < 20; i++)
		{
			if (A[i].thisround == 1)
			{
				count++;
			}
			if (temp == count - 1)
				return i;
		}
	}

	if (incolor == 1)
	{
		for (int i = 0; i < 20; i++)
		{
			if (B[i].thisround == 1)
			{
				count++;
			}
		}
		temp = randnum(count);
		count = 0;
		for (int i = 0; i < 20; i++)
		{
			if (B[i].thisround == 1)
			{
				count++;
			}
			if (temp == count - 1)
				return i;
		}
	}
	return -1;
}

void chessboard::freakai(int incolor)//random walk
{
	int temp = -1;
	int tempmove = -1;
	int a[2] = { -1, -1 };
	if (incolor == 0)//ai=A
	{
		temp = randomchoose(0);
		if (temp >= 0 && A[temp].canj > 0)
		{
			std::vector<pos> Vpos;
			pos end;
			if (A[temp].isking == 0)
			{
				end = A[temp].findjumplong(borad, incolor, Vpos);
			}
			if (A[temp].isking == 1)
			{
				end = A[temp].findkingjumplong(borad, incolor, Vpos);
			}
			setfieat(Vpos, end, incolor);
			a[0] = end.y;
			a[1] = end.x;
			A[temp].movechess(a);
		}
		else
		{
			if (A[temp].isking == 0)
			{
				if (A[temp].xy.angle.ld == 1 && A[temp].xy.angle.rd == 1)
				{
					tempmove = randnum(2);
					if (tempmove == 0)
					{
						a[0] = A[temp].xy.y + 1;
						a[1] = A[temp].xy.x - 1;
						A[temp].movechess(a);
					}
					if (tempmove == 1)
					{
						a[0] = A[temp].xy.y + 1;
						a[1] = A[temp].xy.x + 1;
						A[temp].movechess(a);
					}
				}
				if (A[temp].xy.angle.ld == 1 && A[temp].xy.angle.rd == 0)
				{
					a[0] = A[temp].xy.y + 1;
					a[1] = A[temp].xy.x - 1;
					A[temp].movechess(a);
				}
				if (A[temp].xy.angle.ld == 0 && A[temp].xy.angle.rd == 1)
				{
					a[0] = A[temp].xy.y + 1;
					a[1] = A[temp].xy.x + 1;
					A[temp].movechess(a);
				}
			}
			if (A[temp].isking == 1)
			{
				int tempan;
				int countpos = 0;
				tempan = A[temp].checkkingmove(borad);
				tempmove = randnum(tempan);
				if (tempan == 1)
				{
					if (A[temp].xy.angle.lu == 1)
					{
						for (int i = 1;; i++)
						{
							if (borad[A[temp].xy.y - i][A[temp].xy.x - i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = A[temp].xy.y - tempmove;
						a[1] = A[temp].xy.x - tempmove;
						A[temp].movechess(a);
					}
					if (A[temp].xy.angle.ru == 1)
					{
						for (int i = 1;; i++)
						{
							if (borad[A[temp].xy.y - i][A[temp].xy.x + i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = A[temp].xy.y - tempmove;
						a[1] = A[temp].xy.x + tempmove;
						A[temp].movechess(a);
					}
					if (A[temp].xy.angle.ld == 1)
					{
						for (int i = 1;; i++)
						{
							if (borad[A[temp].xy.y + i][A[temp].xy.x - i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = A[temp].xy.y + tempmove;
						a[1] = A[temp].xy.x - tempmove;
						A[temp].movechess(a);
					}
					if (A[temp].xy.angle.rd == 1)
					{
						for (int i = 1;; i++)
						{
							if (borad[A[temp].xy.y + i][A[temp].xy.x + i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = A[temp].xy.y + tempmove;
						a[1] = A[temp].xy.x + tempmove;
						A[temp].movechess(a);
					}
					
				}
				if (tempan == 2)
				{
					int in2sgin = 0;
					in2sgin = randnum(2) + 1;
					for (;;)
					{
						if (A[temp].xy.angle.lu == 1)
						{
							countpos++;
							if (in2sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[A[temp].xy.y - i][A[temp].xy.x - i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = A[temp].xy.y - tempmove;
								a[1] = A[temp].xy.x - tempmove;
								A[temp].movechess(a);
								break;
							}
						}
						if (A[temp].xy.angle.ru == 1)
						{
							countpos++;
							if (in2sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[A[temp].xy.y - i][A[temp].xy.x + i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = A[temp].xy.y - tempmove;
								a[1] = A[temp].xy.x + tempmove;
								A[temp].movechess(a);
								break;
							}
						}
						if (A[temp].xy.angle.ld == 1)
						{
							countpos++;
							if (in2sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[A[temp].xy.y + i][A[temp].xy.x - i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = A[temp].xy.y + tempmove;
								a[1] = A[temp].xy.x - tempmove;
								A[temp].movechess(a);
								break;
							}
						}
						if (A[temp].xy.angle.rd == 1)
						{
							countpos++;
							if (in2sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[A[temp].xy.y + i][A[temp].xy.x + i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = A[temp].xy.y + tempmove;
								a[1] = A[temp].xy.x + tempmove;
								A[temp].movechess(a);
								break;
							}
						}
					}
				}
				if (tempan == 3)
				{
					int in3sgin = 0;
					in3sgin = randnum(2) + 1;
					for (;;)
					{
						if (A[temp].xy.angle.lu == 1)
						{
							countpos++;
							if (in3sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[A[temp].xy.y - i][A[temp].xy.x - i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = A[temp].xy.y - tempmove;
								a[1] = A[temp].xy.x - tempmove;
								A[temp].movechess(a);
								break;
							}
						}
						if (A[temp].xy.angle.ru == 1)
						{
							countpos++;
							if (in3sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[A[temp].xy.y - i][A[temp].xy.x + i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = A[temp].xy.y - tempmove;
								a[1] = A[temp].xy.x + tempmove;
								A[temp].movechess(a);
								break;
							}
						}
						if (A[temp].xy.angle.ld == 1)
						{
							countpos++;
							if (in3sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[A[temp].xy.y + i][A[temp].xy.x - i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = A[temp].xy.y + tempmove;
								a[1] = A[temp].xy.x - tempmove;
								A[temp].movechess(a);
								break;
							}
						}
						if (A[temp].xy.angle.rd == 1)
						{
							countpos++;
							if (in3sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[A[temp].xy.y + i][A[temp].xy.x + i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = A[temp].xy.y + tempmove;
								a[1] = A[temp].xy.x + tempmove;
								A[temp].movechess(a);
								break;
							}
						}
					}
				}
				if (tempan == 4)
				{
					tempan = randnum(4);
					if (tempan == 0)
					{
						for (int i = 1;; i++)
						{
							if (borad[A[temp].xy.y - i][A[temp].xy.x - i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = A[temp].xy.y - tempmove;
						a[1] = A[temp].xy.x - tempmove;
						A[temp].movechess(a);
					}
					if (tempan == 1)
					{
						for (int i = 1;; i++)
						{
							if (borad[A[temp].xy.y - i][A[temp].xy.x + i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = A[temp].xy.y - tempmove;
						a[1] = A[temp].xy.x + tempmove;
						A[temp].movechess(a);
					}
					if (tempan == 2)
					{
						for (int i = 1;; i++)
						{
							if (borad[A[temp].xy.y + i][A[temp].xy.x - i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = A[temp].xy.y + tempmove;
						a[1] = A[temp].xy.x - tempmove;
						A[temp].movechess(a);
					}
					if (tempan == 3)
					{
						for (int i = 1;; i++)
						{
							if (borad[A[temp].xy.y + i][A[temp].xy.x + i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = A[temp].xy.y + tempmove;
						a[1] = A[temp].xy.x + tempmove;
						A[temp].movechess(a);
					}
				}
			}
		}
	}

	if (incolor == 1)//ai=B
	{
		temp = randomchoose(1);
		if (temp >= 0 && B[temp].canj > 0)
		{
			std::vector<pos> Vpos;
			pos end;
			if (B[temp].isking == 0)
			{
				end = B[temp].findjumplong(borad, incolor, Vpos);
			}
			if (B[temp].isking == 1)
			{
				end = B[temp].findkingjumplong(borad, incolor, Vpos);
			}
			setfieat(Vpos, end, incolor);
			a[0] = end.y;
			a[1] = end.x;
			B[temp].movechess(a);
		}
		else
		{
			if (B[temp].isking == 0)
			{
				if (B[temp].xy.angle.lu == 1 && B[temp].xy.angle.ru == 1)
				{
					tempmove = randnum(2);
					if (tempmove == 0)
					{
						a[0] = B[temp].xy.y - 1;
						a[1] = B[temp].xy.x - 1;
						B[temp].movechess(a);
					}
					if (tempmove == 1)
					{
						a[0] = B[temp].xy.y - 1;
						a[1] = B[temp].xy.x + 1;
						B[temp].movechess(a);
					}
				}
				if (B[temp].xy.angle.lu == 1 && B[temp].xy.angle.ru == 0)
				{
					a[0] = B[temp].xy.y - 1;
					a[1] = B[temp].xy.x - 1;
					B[temp].movechess(a);
				}
				if (B[temp].xy.angle.lu == 0 && B[temp].xy.angle.ru == 1)
				{
					a[0] = B[temp].xy.y - 1;
					a[1] = B[temp].xy.x + 1;
					B[temp].movechess(a);
				}
			}
			if (B[temp].isking == 1)
			{
				int tempan;
				int countpos = 0;
				tempan = B[temp].checkkingmove(borad);
				tempmove = randnum(tempan);
				if (tempan == 1)
				{
					if (B[temp].xy.angle.lu == 1)
					{
						for (int i = 1;; i++)
						{
							if (borad[B[temp].xy.y - i][B[temp].xy.x - i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = B[temp].xy.y - tempmove;
						a[1] = B[temp].xy.x - tempmove;
						B[temp].movechess(a);
					}
					if (B[temp].xy.angle.ru == 1)
					{
						for (int i = 1;; i++)
						{
							if (borad[B[temp].xy.y - i][B[temp].xy.x + i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = B[temp].xy.y - tempmove;
						a[1] = B[temp].xy.x + tempmove;
						B[temp].movechess(a);
					}
					if (B[temp].xy.angle.ld == 1)
					{
						for (int i = 1;; i++)
						{
							if (borad[B[temp].xy.y + i][B[temp].xy.x - i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = B[temp].xy.y + tempmove;
						a[1] = B[temp].xy.x - tempmove;
						B[temp].movechess(a);
					}
					if (B[temp].xy.angle.rd == 1)
					{
						for (int i = 1;; i++)
						{
							if (borad[B[temp].xy.y + i][B[temp].xy.x + i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = B[temp].xy.y + tempmove;
						a[1] = B[temp].xy.x + tempmove;
						B[temp].movechess(a);
					}

				}
				if (tempan == 2)
				{
					int in2sgin = 0;
					in2sgin = randnum(2) + 1;
					for (;;)
					{
						if (B[temp].xy.angle.lu == 1)
						{
							countpos++;
							if (in2sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[B[temp].xy.y - i][B[temp].xy.x - i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = B[temp].xy.y - tempmove;
								a[1] = B[temp].xy.x - tempmove;
								B[temp].movechess(a);
								break;
							}
						}
						if (B[temp].xy.angle.ru == 1)
						{
							countpos++;
							if (in2sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[B[temp].xy.y - i][B[temp].xy.x + i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = B[temp].xy.y - tempmove;
								a[1] = B[temp].xy.x + tempmove;
								B[temp].movechess(a);
								break;
							}
						}
						if (B[temp].xy.angle.ld == 1)
						{
							countpos++;
							if (in2sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[B[temp].xy.y + i][B[temp].xy.x - i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = B[temp].xy.y + tempmove;
								a[1] = B[temp].xy.x - tempmove;
								B[temp].movechess(a);
								break;
							}
						}
						if (B[temp].xy.angle.rd == 1)
						{
							countpos++;
							if (in2sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[B[temp].xy.y + i][B[temp].xy.x + i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = B[temp].xy.y + tempmove;
								a[1] = B[temp].xy.x + tempmove;
								B[temp].movechess(a);
								break;
							}
						}
					}
				}
				if (tempan == 3)
				{
					int in3sgin = 0;
					in3sgin = randnum(2) + 1;
					for (;;)
					{
						if (B[temp].xy.angle.lu == 1)
						{
							countpos++;
							if (in3sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[B[temp].xy.y - i][B[temp].xy.x - i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = B[temp].xy.y - tempmove;
								a[1] = B[temp].xy.x - tempmove;
								B[temp].movechess(a);
								break;
							}
						}
						if (B[temp].xy.angle.ru == 1)
						{
							countpos++;
							if (in3sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[B[temp].xy.y - i][B[temp].xy.x + i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = B[temp].xy.y - tempmove;
								a[1] = B[temp].xy.x + tempmove;
								B[temp].movechess(a);
								break;
							}
						}
						if (B[temp].xy.angle.ld == 1)
						{
							countpos++;
							if (in3sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[B[temp].xy.y + i][B[temp].xy.x - i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = B[temp].xy.y + tempmove;
								a[1] = B[temp].xy.x - tempmove;
								B[temp].movechess(a);
								break;
							}
						}
						if (B[temp].xy.angle.rd == 1)
						{
							countpos++;
							if (in3sgin == countpos)
							{
								countpos = 0;
								for (int i = 1;; i++)
								{
									if (borad[B[temp].xy.y + i][B[temp].xy.x + i] > 1)
										break;
									countpos++;
								}
								tempmove = randnum(countpos) + 1;
								a[0] = B[temp].xy.y + tempmove;
								a[1] = B[temp].xy.x + tempmove;
								B[temp].movechess(a);
								break;
							}
						}
					}
				}
				if (tempan == 4)
				{
					tempan = randnum(4);
					if (tempan == 0)
					{
						for (int i = 1;; i++)
						{
							if (borad[B[temp].xy.y - i][B[temp].xy.x - i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = B[temp].xy.y - tempmove;
						a[1] = B[temp].xy.x - tempmove;
						B[temp].movechess(a);
					}
					if (tempan == 1)
					{
						for (int i = 1;; i++)
						{
							if (borad[B[temp].xy.y - i][B[temp].xy.x + i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = B[temp].xy.y - tempmove;
						a[1] = B[temp].xy.x + tempmove;
						B[temp].movechess(a);
					}
					if (tempan == 2)
					{
						for (int i = 1;; i++)
						{
							if (borad[B[temp].xy.y + i][B[temp].xy.x - i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = B[temp].xy.y + tempmove;
						a[1] = B[temp].xy.x - tempmove;
						B[temp].movechess(a);
					}
					if (tempan == 3)
					{
						for (int i = 1;; i++)
						{
							if (borad[B[temp].xy.y + i][B[temp].xy.x + i] > 1)
								break;
							countpos++;
						}
						tempmove = randnum(countpos) + 1;
						a[0] = B[temp].xy.y + tempmove;
						a[1] = B[temp].xy.x + tempmove;
						B[temp].movechess(a);
					}
				}


			}
		}
	}
	updateboard();
}

void chessboard::setfieat(std::vector<pos> Vpos, pos endp, int incolor)
{
	pos temp;
	int a = 0, b = 0;
	temp = endp;
	if (incolor == 0)
	{
		while (temp.past != -1)
		{
			a = temp.x - Vpos[temp.past].x;
			b = temp.y - Vpos[temp.past].y;
			for (int i = 1;; i++)
			{

				if (a < 0 && b < 0)//lu
				{
					if (borad[temp.y + i][temp.x + i] > 1)
					{
						B[borad[temp.y + i][temp.x + i] % 100].fieat = 1;
						break;
					}
				}

				if (a > 0 && b < 0)//ru
				{
					if (borad[temp.y + i][temp.x - i] > 1)
					{
						B[borad[temp.y + i][temp.x - i] % 100].fieat = 1;
						break;
					}
				}

				if (a < 0 && b > 0)//ld
				{
					if (borad[temp.y - i][temp.x + i] > 1)
					{
						B[borad[temp.y - i][temp.x + i] % 100].fieat = 1;
						break;
					}
				}

				if (a > 0 && b > 0)//rd
				{
					if (borad[temp.y - i][temp.x - i] > 1)
					{
						B[borad[temp.y - i][temp.x - i] % 100].fieat = 1;
						break;
					}
				}
			}

			temp = Vpos[temp.past];
		}
	}

	if (incolor == 1)
	{
		while (temp.past != -1)
		{
			a = temp.x - Vpos[temp.past].x;
			b = temp.y - Vpos[temp.past].y;
			for (int i = 1;; i++)
			{

				if (a < 0 && b < 0)//lu
				{
					if (borad[temp.y + i][temp.x + i] > 1)
					{
						A[borad[temp.y + i][temp.x + i] % 100].fieat = 1;
						break;
					}
				}

				if (a > 0 && b < 0)//ru
				{
					if (borad[temp.y + i][temp.x - i] > 1)
					{
						A[borad[temp.y + i][temp.x - i] % 100].fieat = 1;
						break;
					}
				}

				if (a < 0 && b > 0)//ld
				{
					if (borad[temp.y - i][temp.x + i] > 1)
					{
						A[borad[temp.y - i][temp.x + i] % 100].fieat = 1;
						break;
					}
				}

				if (a > 0 && b > 0)//rd
				{
					if (borad[temp.y - i][temp.x - i] > 1)
					{
						A[borad[temp.y - i][temp.x - i] % 100].fieat = 1;
						break;
					}
				}
			}
			temp = Vpos[temp.past];
		}
	}
}

void chessboard::gamebegin()
{
	int playercolor = -1;
	int playerchioce = -1;
	pos endpoint;
	resetxy(endpoint);
	std::vector<pos> Vpossave;
	int ab[2] = { -1, -1 };
	int gamesign = -1;

	printflogo();
	printf("do your selection A=0 or B=1 (A walk first):");
	scanf("%d", &playercolor);
	
	while (!(playercolor == 0 || playercolor == 1))
	{
		printf("input the 0 or 1 :");
		scanf("%d", &playercolor);
	}
	Sleep(1000);
	system("cls");
	updateboard();
	showboard();
	
	if (playercolor == 0)
	{
		while (1)
		{
			//playerchioce = -1;
			for (int i = 0; i < 20; i++)
			{
				A[i].beking();
				B[i].beking();
			}
			gamesign = checkall(0);
			if (gamesign == 1)
			{
				printf("\nA lost this game!!!!\n");
				Sleep(5000);
				exit(0);
			}
			playerchioce = selectponit(ab, A, borad);
			if (A[playerchioce].canj == 1)
			{
				if (A[playerchioce].isking == 0)
				{
					endpoint = A[playerchioce].findjumplong(borad, playercolor, Vpossave);
					while (isrigthpos(endpoint, ab) != 1)
					{
						printf("thisround not allow, input again : ");
						getposmove(ab);//!!!!
						//endpoint = A[playerchioce].findjumplong(borad, playercolor, Vpossave);
					}
				}
				if (A[playerchioce].isking == 1)
				{
					endpoint = A[playerchioce].findkingjumplong(borad, playercolor, Vpossave);
					while (isrigthpos(endpoint, ab) != 1)
					{
						printf("thisround not allow, input again : ");
						getposmove(ab);//!!!!
						//endpoint = A[playerchioce].findkingjumplong(borad, playercolor, Vpossave);
					}
				}
				setfieat(Vpossave, endpoint, playercolor);
				A[playerchioce].movechess(ab);
			}
			else
			{
				while (isrightposmove(A[playerchioce], ab) != 1)
				{
					printf("wrong pos input again : ");
					getposmove(ab);//!!!!
				}
				A[playerchioce].movechess(ab);
			}
			updateboard();
			system("cls");
			showboard();
			


			gamesign = checkall(1);
			if (gamesign == 2)
			{
				printf("\nB lost this game!!!!\n");
				Sleep(5000);
				exit(0);
			}
			freakai(1);
			system("cls");
			showboard();

			clearABvalue();

		}
	}

	if (playercolor == 1)
	{

		while (1)
		{
			//playerchioce = -1;
			for (int i = 0; i < 20; i++)
			{
				A[i].beking();
				B[i].beking();
			}
			gamesign = checkall(0);
			if (gamesign == 1)
			{
				printf("\nA lost this game!!!!\n");
				Sleep(5000);
				exit(0);
			}
			freakai(0);
			system("cls");
			showboard();

			gamesign = checkall(1);
			if (gamesign == 2)
			{
				printf("\nB lost this game!!!!\n");
				Sleep(5000);
				exit(0);
			}
			
			playerchioce = selectponit(ab, B, borad);
			if (B[playerchioce].canj == 1)
			{
				if (B[playerchioce].isking == 0)
				{
					endpoint = B[playerchioce].findjumplong(borad, playercolor, Vpossave);
					while (isrigthpos(endpoint, ab) != 1)
					{
						printf("thisround not allow, input again : ");
						getposmove(ab);//!!!!
						//endpoint = B[playerchioce].findjumplong(borad, playercolor, Vpossave);
					}
				}
				if (B[playerchioce].isking == 1)
				{
					endpoint = B[playerchioce].findkingjumplong(borad, playercolor, Vpossave);
					while (isrigthpos(endpoint, ab) != 1)
					{
						printf("thisround not allow, input again : ");
						getposmove(ab);//!!!!
						//endpoint = B[playerchioce].findkingjumplong(borad, playercolor, Vpossave);
					}
				}
				setfieat(Vpossave, endpoint, playercolor);
				B[playerchioce].movechess(ab);
			}
			else
			{
				while (isrightposmove(B[playerchioce], ab) != 1)
				{
					printf("wrong pos input again : ");
					getposmove(ab);//!!!!
				}
				B[playerchioce].movechess(ab);
			}
			updateboard();
			system("cls");
			showboard();

			clearABvalue();
		}
	}
}

int chessboard::isrigthpos(pos endp, int *a)
{
	if (endp.y == a[0] && endp.x == a[1] && a[0] != -1 && a[1] != -1)
		return 1;
	return 0;
}

int chessboard::isrightposmove(chessman AB, int *a)
{
	if (AB.isking == 0)
	{
		if (AB.xy.y - 1 == a[0] && AB.xy.x - 1 == a[1] && AB.xy.angle.lu == 1)
		{
			return 1;
		}
		if (AB.xy.y - 1 == a[0] && AB.xy.x + 1 == a[1] && AB.xy.angle.ru == 1)
		{
			return 1;
		}
		if (AB.xy.y + 1 == a[0] && AB.xy.x - 1 == a[1] && AB.xy.angle.ld == 1)
		{
			return 1;
		}
		if (AB.xy.y + 1 == a[0] && AB.xy.x + 1 == a[1] && AB.xy.angle.rd == 1)
		{
			return 1;
		}
	}
	if (AB.isking == 1)
	{
		int tempy = -1;
		int tempx = -1;
		int count = 0;
		tempy = a[0] - AB.xy.y;
		tempx = a[1] - AB.xy.x;
		if (abs(tempy) == abs(tempx))
		{
			if (tempy < 0 && tempx < 0 && AB.xy.angle.lu == 1)
			{
				for (int i = 1; i <= abs(tempy); i++)
					if (borad[AB.xy.y - i][AB.xy.x - i] > 1)
					{
						count = 1;
					}
				if (count == 0)
					return 1;
				else
					return 0;

			}
			if (tempy < 0 && tempx > 0 && AB.xy.angle.ru == 1)
			{
				for (int i = 1; i <= abs(tempy); i++)
					if (borad[AB.xy.y - i][AB.xy.x + i] > 1)
					{
						count = 1;
					}
				if (count == 0)
					return 1;
				else
					return 0;
			}
			if (tempy > 0 && tempx < 0 && AB.xy.angle.ld == 1)
			{
				for (int i = 1; i <= abs(tempy); i++)
					if (borad[AB.xy.y + i][AB.xy.x - i] > 1)
					{
						count = 1;
					}
				if (count == 0)
					return 1;
				else
					return 0;
			}
			if (tempy > 0 && tempx > 0 && AB.xy.angle.rd == 1)
			{
				for (int i = 1; i <= abs(tempy); i++)
					if (borad[AB.xy.y + i][AB.xy.x + i] == 1)
					{
						count = 1;
					}
				if (count == 0)
					return 1;
				else
					return 0;
			}
		}
		else
			return 0;
	}

	return 0;
}

void chessboard::tureaiset(int incolor)
{
	//undone
}