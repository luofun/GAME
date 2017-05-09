#include"chessman.h"
#include"logic.h"

chessman::chessman()
{
	thisround = 0;
	canj = 0;
	fieat = 0;
	isking = 0;
	xy.angle.ld = 0;
	xy.angle.lu = 0;
	xy.angle.rd = 0;
	xy.angle.ru = 0;
	color = -1;
	num = -1;
	xy.x = -1;
	xy.y = -1;
	xy.past = -1;
	xy.jumplong = 0;
}

chessman::~chessman()
{

}

void chessman::changec(int color)
{
	this->color = color;
}

int chessman::checkmove(int board[10][10])
{
	if (canj == 1)
		return 0;
	if (fieat == 1)
		return 0;

	//int count = 0;

	if (isking == 0)
	{
		if (color == 0)
		{
			if (xy.x == 0 && board[xy.y + 1][xy.x + 1] == 1)
			{
				xy.angle.rd = 1;
				return 2;
			}
			else if (xy.x == 9 && board[xy.y + 1][xy.x - 1] == 1)
			{
				xy.angle.ld = 1;
				return 1;
			}
			else if (board[xy.y + 1][xy.x - 1] == 1 && board[xy.y + 1][xy.x + 1] == 1)
				{
					xy.angle.ld = 1;
					xy.angle.rd = 1;
					return 3;
				}
			else if (board[xy.y + 1][xy.x - 1] == 1)
			{
				xy.angle.ld = 1;
				return 1;
			}
			else if (board[xy.y + 1][xy.x + 1] == 1)
			{
				xy.angle.rd = 1;
				return 2;
			}
		}
		else if (color == 1)
		{
			if (xy.x == 0 && board[xy.y - 1][xy.x + 1] == 1)
			{
				xy.angle.ru = 1;
				return 2;
			}
			else if (xy.x == 9 && board[xy.y - 1][xy.x - 1] == 1)
			{
				xy.angle.lu = 1;
				return 1;
			}
			else if (board[xy.y - 1][xy.x - 1] == 1 && board[xy.y - 1][xy.x + 1] == 1)
				{
					xy.angle.lu = 1;
					xy.angle.ru = 1;
					return 3;
				}
			else if (board[xy.y - 1][xy.x - 1] == 1)
			{
				xy.angle.lu = 1;
				return 1;
			}
			else if (board[xy.y - 1][xy.x + 1] == 1)
			{
				xy.angle.ru = 1;
				return 2;
			}
		}
	}

	return 0;
}

int chessman::checkeat(int board[10][10])
{
	if (fieat == 1)
		return 0;
	int count = 0;
	if (isking == 1)
		return count;
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
	if (count > 0)
	{
		canj = 1;
		xy.jumplong = 1;
	}
	return count;
}

void chessman::beking()
{
	if (color == 0)
		if (xy.y == 9)
			isking = 1;
	if (color == 1)
		if (xy.y == 0)
			isking = 1;
}

int chessman::checkkingmove(int board[10][10])
{
	if (fieat == 1)
		return 0;
	int count = 0;
	if (canj == 1)
		return count;
	if (isking == 1)
	{
		for (int i = 1; (xy.x - i >= 0) && (xy.y - i >= 0); i++)
		{
			if (board[xy.y - i][xy.x - i] > 1)
				break;
			if (board[xy.y - i][xy.x - i] == 1)
			{
				xy.angle.lu = 1;
				count++;
				break;
			}

		}

		for (int i = 1; (xy.x + i < 10) && (xy.y - i >= 0); i++)
		{
			if (board[xy.y - i][xy.x + i]>1)
				break;
			if (board[xy.y - i][xy.x + i] == 1)
			{
				xy.angle.ru = 1;
				count++;
				break;
			}
		}

		for (int i = 1; (xy.x - i >= 0) && (xy.y + i < 10); i++)
		{
			if (board[xy.y + i][xy.x - i] > 1)
				break;
			if (board[xy.y + i][xy.x + i] == 1)
			{
				xy.angle.ld = 1;
				count++;
				break;
			}
		}

		for (int i = 1; (xy.x + i < 10) && (xy.y + i < 10); i++)
		{
			if (board[xy.y + i][xy.x + i] > 1)
				break;
			if (board[xy.y + i][xy.x + i] == 1)
			{
				xy.angle.rd = 1;
				count++;
				break;
			}
		}
	}
	return count;
}

int chessman::checkkingeat(int board[10][10])
{
	if (fieat == 1)
		return 0;
	int count = 0;
	if (isking == 1)
	{
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
	}
	if (count > 0)
	{
		canj = 1;
		xy.jumplong = 1;
	}
	return count;
}

void chessman::movechess(int* a)
{
	if (fieat == 0)
	{
		xy.y = a[0];
		xy.x = a[1];
	}

}

pos chessman::findjumplong(int board[10][10], int incolor, std::vector<pos> &Vpos)
{
	std::vector<pos>().swap(Vpos);
	pos endpoint;
	resetxy(endpoint);
	//this->checkeat(board);

	if (canj == 0 || isking == 1)
		return endpoint;

	//int count = 0;
	std::queue<pos> eatqueue;
	
	int templong = 1;
	int tcount = 0;
	an tempangle;
	
	pos xypop, xytemp;
	
	eatqueue.push(this->xy);
	Vpos.push_back(this->xy);
	
	//need to add avoid the circle
	while (eatqueue.empty() != 1)
	{
		resetxy(xypop);
		
		templong = eatqueue.front().jumplong;
		xypop = eatqueue.front();
		
		checkposeat(board, incolor, xypop);
		

		if (eatqueue.size() == 1)
		{
			endpoint = xypop;
			endpoint.jumplong = templong;
		}

		eatqueue.pop();

		if (xypop.angle.lu == 1 && ((xypop.past == -1) ? 1 : (Vpos[xypop.past].angle.rd != 1)))
		{
			//push
			resetxy(xytemp);
			xytemp.x = xypop.x - 2;
			xytemp.y = xypop.y - 2;
			xytemp.jumplong = templong + 1;
			xytemp.past = tcount;
			checkposeat(board, incolor, xytemp);
			eatqueue.push(xytemp);
			Vpos.push_back(xytemp);
		}

		if (xypop.angle.ru == 1 && ((xypop.past == -1) ? 1 : (Vpos[xypop.past].angle.ld != 1)))
		{
		
			resetxy(xytemp);
			xytemp.x = xypop.x + 2;
			xytemp.y = xypop.y - 2;
			xytemp.jumplong = templong + 1;
			xytemp.past = tcount;
			checkposeat(board, incolor, xytemp);
			eatqueue.push(xytemp);
			Vpos.push_back(xytemp);
		}

		if (xypop.angle.ld == 1 && ((xypop.past == -1) ? 1 : (Vpos[xypop.past].angle.ru != 1)))
		{
			
			resetxy(xytemp);
			xytemp.x = xypop.x - 2;
			xytemp.y = xypop.y + 2;
			xytemp.jumplong = templong + 1;
			xytemp.past = tcount;
			checkposeat(board, incolor, xytemp);
			eatqueue.push(xytemp);
			Vpos.push_back(xytemp);
		}

		if (xypop.angle.rd == 1 && ((xypop.past == -1) ? 1 : (Vpos[xypop.past].angle.lu != 1)))
		{
			
			resetxy(xytemp);
			xytemp.x = xypop.x + 2;
			xytemp.y = xypop.y + 2;
			xytemp.jumplong = templong + 1;
			xytemp.past = tcount;
			checkposeat(board, incolor, xytemp);
			eatqueue.push(xytemp);
			Vpos.push_back(xytemp);
		}

		tempangle = xypop.angle;
		tcount++;

	}
	return endpoint;

}

pos chessman::findkingjumplong(int board[10][10], int incolor, std::vector<pos> &Vpos)
{
	std::vector<pos>().swap(Vpos);
	pos endpoint;
	resetxy(endpoint);
	if (canj == 0 || isking == 0)
		return endpoint;
	int tcount = 0;
	int templong = 1;
	int temp1 = 0;
	pos xypop, xytemp;

	std::queue<pos> kingeatqueue;

	kingeatqueue.push(this->xy);
	Vpos.push_back(this->xy);

	while (kingeatqueue.empty() != 1)
	{
		resetxy(xypop);
		//resetxy(xytemp);
		templong = kingeatqueue.front().jumplong;
		xypop = kingeatqueue.front();

		checkposkingeat(board, incolor, xypop);

		if (kingeatqueue.size() == 1)
		{
			endpoint = xypop;
			endpoint.jumplong = templong;
		}

		kingeatqueue.pop();
		
		//need to add avoid the circle
		if (xypop.angle.lu == 1)
		{
			temp1 = 0;
			for (int i = 1; (xypop.x - i > 0) && (xypop.y - i > 0); i++)
			{
				if (board[xypop.y - i][xypop.x - i] >= 100)
				{
					temp1 = i;
					for (int j = temp1 + 1; (xypop.x - j >= 0) && (xypop.y - j >= 0); j++)
					{
						if (board[xypop.y - j][xypop.x - j] == 1 && ((xypop.past == -1) ? 1 : (Vpos[xypop.past].angle.rd != 1)))
						{
							resetxy(xytemp);
							xytemp.x = xypop.x - j;
							xytemp.y = xypop.y - j;
							xytemp.jumplong = templong + 1;
							xytemp.past = tcount;
							checkposkingeat(board, incolor, xytemp);
							kingeatqueue.push(xytemp);
							Vpos.push_back(xytemp);
						}
						if (board[xypop.y - j][xypop.x - j] >= 100)
							break;
					}
					break;
				}		
			}
		}

		if (xypop.angle.ru == 1)
		{
			temp1 = 0;
			for (int i = 1; (xypop.x + i < 9) && (xypop.y - i > 0); i++)
			{
				if (board[xypop.y - i][xypop.x + i] >= 100)
				{
					temp1 = i;
					for (int j = temp1 + 1; (xypop.x + j < 10) && (xypop.y - j >= 0); j++)
					{
						if (board[xypop.y - j][xypop.x + j] == 1 && ((xypop.past == -1) ? 1 : (Vpos[xypop.past].angle.ld != 1)))
						{
							resetxy(xytemp);
							xytemp.x = xypop.x + j;
							xytemp.y = xypop.y - j;
							xytemp.jumplong = templong + 1;
							xytemp.past = tcount;
							checkposkingeat(board, incolor, xytemp);
							kingeatqueue.push(xytemp);
							Vpos.push_back(xytemp);
						}
						if (board[xypop.y - j][xypop.x + j] >= 100)
							break;
					}
					break;
				}
			}
		}

		if (xypop.angle.ld == 1)
		{
			temp1 = 0;
			for (int i = 1; (xypop.x - i > 0) && (xypop.y + i < 9); i++)
			{
				if (board[xypop.y + i][xypop.x - i] >= 100)
				{
					temp1 = i;
					for (int j = temp1 + 1; (xypop.x - j >= 0) && (xypop.y + j < 10); j++)
					{
						if (board[xypop.y + j][xypop.x - j] == 1 && ((xypop.past == -1) ? 1 : (Vpos[xypop.past].angle.ru != 1)))
						{
							resetxy(xytemp);
							xytemp.x = xypop.x - j;
							xytemp.y = xypop.y + j;
							xytemp.jumplong = templong + 1;
							xytemp.past = tcount;
							checkposkingeat(board, incolor, xytemp);
							kingeatqueue.push(xytemp);
							Vpos.push_back(xytemp);
						}
						if (board[xypop.y + j][xypop.x - j] >= 100)
							break;
					}
					break;
				}
			}
		}

		if (xypop.angle.rd == 1)
		{
			temp1 = 0;
			for (int i = 1; (xypop.x + i < 9) && (xypop.y + i < 9); i++)
			{
				if (board[xypop.y + i][xypop.x + i] >= 100)
				{
					temp1 = i;
					for (int j = temp1 + 1; (xypop.x + j < 10) && (xypop.y + j < 10); j++)
					{
						if (board[xypop.y + j][xypop.x + j] == 1 && ((xypop.past == -1) ? 1 : (Vpos[xypop.past].angle.lu != 1)))
						{
							resetxy(xytemp);
							xytemp.x = xypop.x + j;
							xytemp.y = xypop.y + j;
							xytemp.jumplong = templong + 1;
							xytemp.past = tcount;
							checkposkingeat(board, incolor, xytemp);
							kingeatqueue.push(xytemp);
							Vpos.push_back(xytemp);
						}
						if (board[xypop.y + j][xypop.x + j] >= 100)
							break;
					}
					break;
				}
			}
		}

		tcount++;
	}
	return endpoint;

}

void chessman::clearsign()
{
	canj = 0;
	thisround = 0;
	xy.angle.ld = 0;
	xy.angle.lu = 0;
	xy.angle.rd = 0;
	xy.angle.ru = 0;
	xy.jumplong = 0;
	//xy.x = -1;
	//xy.y = -1;
	xy.past=-1;
}

void chessman::changethiround()
{
	if (canj > 0 || xy.angle.ld > 0 || xy.angle.lu > 0 || xy.angle.rd > 0 || xy.angle.ru > 0)
	{
		thisround = 1;
	}
}