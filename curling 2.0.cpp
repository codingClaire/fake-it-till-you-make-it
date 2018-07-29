#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int square[25][25];
const int dir[4][2] = {
	{ 0, -1 },
	{ 1,0 },
	{ 0, 1 },
	{ -1 ,0 },
};
int row, column;
int minstep;
int di,dj; 


void DFS(const int& r, const int& c, int step)
{
	if (step >= 10 || step > minstep) return;
	for (int i = 0; i < 4; i++)
	{
		int rr = r, cc = c;
		while (rr >= 0 && cc >= 0 && rr < row&&cc < column)
		{
			switch (square[rr][cc])
			{
			case 0://空格 继续往下走
			{
				rr += dir[i][0];
				cc += dir[i][1];
				break;
			}
			case 3://到达终点了
			{
				if (step + 1 < minstep)//如果step加上当前步骤比之前最小的步数还小，将其赋值给最小步数
					minstep = step + 1;
				rr = -1;//????
				break;
			}
			case 1://遇到石头了
			{
				if (!(rr - dir[i][1] == r&&cc - dir[i][0] == c))//?????
				{
					square[rr][cc] = 0;//石头变空格 再调用DFS函数
					DFS(rr - dir[i][1], cc - dir[i][0], step + 1);//球到不了放石头的地方，只能是在原来的方向上退一步
					square[rr][cc]=1; 
				}
				rr=-1;
				break;
			}
			default: {
				break;
			}
			}
		}
	}
}

int main()
{
	while (scanf("%d%d", &column, &row) != EOF)
	{
		if (column == 0 && row == 0)
			break;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				scanf("%d", &square[i][j]);
				if (square[i][j] == 2)
				{
					di = i;
					dj = j;//where the stone begins
				}
			}
		}
		square[di][dj] = 0;//此时已将该点设置为零 
		minstep=11;
		DFS(di, dj, 0);
	
		if (minstep > 10) minstep = -1;
		cout << minstep << endl;
	}
	return 0;
}
