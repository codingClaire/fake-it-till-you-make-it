
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;

char a[25][25];
int dir[4][2] =
{
	{1,0},
	{-1,0},
	{0,1},
	{0,-1}
};
int row, column, num;

bool In_Boundary(int r, int c)
{
	if (r < row&&r >= 0 && c < column&&c >= 0)
		return true;
	return false;
}
/*深度优先搜索*/
void Depth_First_Search(int r, int c)
{
	a[r][c] = '#';//遍历过的直接赋值为#
	num++;
	int rr, cc;
	for (int i = 0; i < 4; i++)
	{//遍历四个方向
		int rr = r + dir[i][0];
		int cc = c + dir[i][1];
		if (In_Boundary(rr, cc) && a[rr][cc] == '.')//在范围内且是黑色
			Depth_First_Search(rr, cc);//递归
	}
}
/*广度优先搜索*/
struct node
{
	int x, y;
};

node q[500];

void Breath_First_Search(int r, int c)
{
	queue<node> q;
	node start, ending;
	start.x = r;
	start.y = c;
	q.push(start);
	while (!q.empty()) //队列不为空
	{
		start = q.front();//front()返回队列中的第一个元素
		q.pop();//队首元素出队
		for (int i = 0; i < 4; i++)
		{
			ending.x = start.x + dir[i][0];
			ending.y = start.y + dir[i][1];
			if (In_Boundary(ending.x, ending.y) && a[ending.x][ending.y] == '.')
			{
				a[ending.x][ending.y] = '#';
				sum++;
				q.push(ending);//ending入队并插到队尾
			}
		}
	}
}


int main()
{
	int di, dj;
	while (scanf("%d%d", &column, &row) != EOF)
	{
		getchar(); 
		if (column == 0 && row == 0)
			break;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				scanf("%c", &a[i][j]);
				if (a[i][j] == '@')
				{
					di = i;
					dj = j;//where I am
				}
			}
			getchar();
		}
		num = 0;
		//Depth_First_Search(di, dj);
		Breath_First_Search(di, dj);
		printf("%d\n", num);
	}
	return 0;
}
