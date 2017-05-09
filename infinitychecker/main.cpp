#include<stdio.h>
#include"chessman.h"
#include"chessboard.h"
#include"logic.h"
#include<time.h>
#include<stdlib.h>
#include<Windows.h>


int main(int argc, char* argv[])
{
	chessboard newboard;
	/*int a[2] = { -1, -1 };
	clock_t start, end;
	srand((unsigned int)time(NULL));
	//printf("seed=%d\n", (unsigned int)time(NULL));
	//newboard.showbboard();
	//randnum(10);
	start = clock();
	printflogo();
	
	newboard.updateboard();
	newboard.showboard();
	newboard.checkall(0);
	newboard.checkall(1);
	//printf("\nAfail=%d\n", newboard.checkall(0));	
	//getposmove(a);
	//printf("pos now move y%d x%d\n", a[0], a[1]);
	//printf("test rand=%d\n", randnum(2));
	//printf("test move=%d\n", newboard.B[16].checkmove(newboard.borad));
	//newboard.borad[4][4] = 200;
	//newboard.borad[4][6] = 200;
	//newboard.borad[6][4] = 200;
	//newboard.borad[6][6] = 1;
	//newboard.borad[7][5] = 1;
	//newboard.B[10].fieat = 1;
	//newboard.updateboard();
	//newboard.A[17].isking = 1;
	//newboard.borad[6][2] = 1;
	//newboard.borad[5][3] = 210;
	//printf("test count=%d\n", newboard.A[17].checkkingeat(newboard.borad));
	//newboard.showboard();
	//newboard.checkall(0);
	std::vector<pos> Vtest;
	pos pend;
	//pend = newboard.A[17].findkingjumplong(newboard.borad, newboard.A[17].color, Vtest);
	//printf("test long=%d\n", pend.jumplong);
	//printf("Vsize=%d\tcap=%d\n", Vtest.size(),Vtest.capacity());	
	//std::vector<pos>().swap(Vtest);
	//printf("testend y=%d\t x=%d\n", pend.y, pend.x);
	//printf("Vsize=%d\tcap=%d\n", Vtest.size(),Vtest.capacity());
	//printf("testcheckall=%d\n", newboard.A[18].thisround);
	//newboard.showboard();
	//exit(0);

	end = clock();
	printf("\nused time =%lf\n", (double)(end - start) / CLOCKS_PER_SEC);*/
	newboard.gamebegin();
	return 0;
}