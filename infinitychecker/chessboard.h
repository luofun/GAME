#pragma once
#include"chessman.h"
#include<math.h>
#include"logic.h"

class chessboard
{
public:
	chessman *A;
	chessman *B;
	int borad[10][10];
	int bborad[10][10];

	chessboard();
	~chessboard();
	void showbboard();
	void testchess();
	void updateboard();
	void showboard();
	int checkfail();
	void tureaiset(int incolor);
	int randomchoose(int incolor);
	void freakai(int incolor);
	void gamebegin();
	void resetthisroundsign(int incolor);
	int checkall(int incolor);
	void clearABvalue();
	void setfieat(std::vector<pos> Vpos, pos endp, int incolor);
	int isrigthpos(pos endp, int *a);
	int isrightposmove(chessman AB, int *a);
	

private:
	void initchessman();
	void initboard(int size);

};

