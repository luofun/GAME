#pragma once

#include<queue>
#include<vector>


struct an
{
	int lu, ld, ru, rd;
};
struct pos
{
	int x;
	int y;
	an angle;
	int past;
	int jumplong;
};
class chessman
{
public:
	int num;
	pos xy;
	int color;
	int thisround;
	int fieat;
	int canj;
	int isking;

	chessman();
	~chessman();
	void changec(int color);
	int checkmove(int board[10][10]);
	int checkeat(int board[10][10]);
	void beking();
	int checkkingmove(int board[10][10]);
	int checkkingeat(int board[10][10]);
	void movechess(int* a);
	pos findjumplong(int board[10][10], int incolor, std::vector<pos> &Vpos);
	pos findkingjumplong(int board[10][10], int incolor, std::vector<pos> &Vpos);
	void clearsign();
	void changethiround();

private:

};
