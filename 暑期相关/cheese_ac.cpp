/*���⣺

��H * W�ĵ�ͼ����N�����ҹ�����ÿ�������ֱ�����Ӳ��Ϊ1-N�����ҡ���һֻ����׼���ӳ�����Ա�ÿһ�����������ҡ�������һ������ֵ����ʼʱΪ1��ÿ��һ����������������ֵ����1��ÿ������ֻ�ܳ�һ�Σ���������ֻ�ܳ�Ӳ�Ȳ����ڵ�ǰ����ֵ�����ҡ� 

      ����ӵ�ǰ�������������ڵ����ϰ���ĸ���Ҫʱ��1��λ�����ϰ���ĸ����ߡ��ߵ�������ʱ���ɳԵ��ù��������ң�������ʱ�䲻�ơ��ʳԱ���������������ʱ�� 

���룺��һ����������H(1 <= H <= 1000)��W(1 <= W <=1000)��N(1 <= N <= 9)��֮��H��W��Ϊ��ͼ�� ��.��Ϊ�յأ� ��X��Ϊ�ϰ����S��Ϊ���󶴣� 1-N����Ӳ��Ϊ1-N�����ҵĹ��������������ʱ�� 

���ⷭ��ο��� http://bbs.byr.cn/#!article/ACM_ICPC/73337?au=Milrivel */
/* ֻ�ܴ�1 �Ե� n 
���������ֳ�С���� ���������· ��ʹ��ÿһ��С�ε����·
������������ҹ��������· */

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
     /*���������� while (!Q.empty()) Q.pop();*/
point BFS(int dx, int dy, char ch)
{
	memset(vis, 0, sizeof(vis));//vis��ʼ��
	queue<point> q;
	point start = { dx,dy,0 };
	q.push(start);
	vis[dx][dy] = 1;
	while (!q.empty())
	{
		start = q.front();
		q.pop();//������ʼ�� �ٱ���������
		if (map[start.x][start.y] == ch)
			return start;//�Ե���
		for (int i = 0; i < 4; i++)
		{
			int tx = start.x + dirx[i];
			int ty = start.y + diry[i];//�������ұ���
			if (tx < 0 || tx >= row || ty < 0 || ty >= column || map[tx][ty] == 'X')
				continue;
			point next = { tx,ty,start.time + 1 };//����һ��
			if (!vis[tx][ty] )
			{
				vis[tx][ty] = 1;
				q.push(next);//�����ߵ����ڵ������� �ȴ���ʼ�����  
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
					map[i][j] = '0';//����ļ� �൱�ڵ�0�����
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			point next = BFS(dx, dy, map[dx][dy] + 1);//����������������յ���ַ� 
			ans += next.time;
			dx = next.x;
			dy = next.y;//��һ���յ��ֱ�����
		}
		printf("%d\n", ans);
	}
	return 0;
}
