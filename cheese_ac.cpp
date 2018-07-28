/*题意：

在H * W的地图上有N个奶酪工厂，每个工厂分别生产硬度为1-N的奶酪。有一只老鼠准备从出发点吃遍每一个工厂的奶酪。老鼠有一个体力值，初始时为1，每吃一个工厂的奶酪体力值增加1（每个工厂只能吃一次），且老鼠只能吃硬度不大于当前体力值的奶酪。 

      老鼠从当前格到上下左右相邻的无障碍物的格需要时间1单位，有障碍物的格不能走。走到工厂上时即可吃到该工厂的奶酪，吃奶酪时间不计。问吃遍所有奶酪最少用时。 

输入：第一行三个整数H(1 <= H <= 1000)、W(1 <= W <=1000)、N(1 <= N <= 9)，之后H行W列为地图， “.“为空地， ”X“为障碍物，”S“为老鼠洞， 1-N代表硬度为1-N的奶酪的工厂。输出最少用时。 

题意翻译参考自 http://bbs.byr.cn/#!article/ACM_ICPC/73337?au=Milrivel */
/* 只能从1 吃到 n 
将大问题拆分成小问题 求整个最短路 即使求每一个小段的最短路
先求出相邻奶酪工厂的最短路 */

#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

const int maxn = 1005;
int row, column, n;
char map[maxn][maxn];
int dirx[4] = { -1,1,0,0 },diry[4] = { 0,0,1,-1 }, vis[maxn][maxn];

struct point
{
	int x, y, time;
};
     /*遍历出队列 while (!Q.empty()) Q.pop();*/
point BFS(int dx, int dy, char ch)
{
	memset(vis, 0, sizeof(vis));//vis初始化
	queue<point> q;
	point start = { dx,dy,0 };
	q.push(start);
	vis[dx][dy] = 1;
	while (!q.empty())
	{
		start = q.front();
		q.pop();//更新起始点 再遍历出队列
		if (map[start.x][start.y] == ch)
			return start;//吃到了
		for (int i = 0; i < 4; i++)
		{
			int tx = start.x + dirx[i];
			int ty = start.y + diry[i];//上下左右遍历
			if (tx < 0 || tx >= row || ty < 0 || ty >= column || map[tx][ty] == 'X')
				continue;
			point next = { tx,ty,start.time + 1 };//走了一步
			if (!vis[tx][ty] )
			{
				vis[tx][ty] = 1;
				q.push(next);//将新走的相邻点放入队列 等待起始点更新  
			}

		}
	}
}



int main()
{
	while (scanf("%d%d%d", &row, &column, &n)==3)
	{
		int dx, dy;
		for (int i = 0; i < row; i++)
		{
			scanf("%s", map[i]);
			for (int j = 0; j < column; j++)
			{
				if (map[i][j] == 'S')
				{
					dx = i; dy = j;
					map[i][j] = '0';//老鼠的家 相当于第0个起点
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			point next = BFS(dx, dy, map[dx][dy] + 1);//传入的是起点坐标和终点的字符 
			ans += next.time;
			dx = next.x;
			dy = next.y;//下一个终点又变成起点
		}
		printf("%d\n", ans);
	}
	return 0;
}
