#pragma once
#include"chessman.h"
#include<math.h>

int randnum(int size);
void printflogo(void);
void getposmove(int* a);
int checkposeat(int board[10][10], int color, pos &xy);
int checkposkingeat(int board[10][10], int color, pos &xy);
void resetxy(pos &xy);
int selectponit(int *a, chessman *AB, int board[10][10]);
