#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

struct cube
{
	int x, y, z;
	void init(int x,int y,int z)
	{
		this->x=x;
		this->y=y;
		this->z=z;
	}
};

bool comp(struct cube a, struct cube b)
{
	return a.x*a.y < b.x*b.y;
}//按底面积从大到小

cube block[200];
int dp[200];
int n;

int main()
{
	int cas = 1;
	while (scanf("%d", &n) == 1 && n)
	{
		int m = 0;
		for (int i = 0; i < n; i++)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			block[m++].init(a, b, c);
			block[m++].init(a, c, b);
			block[m++].init(b, a, c);
			block[m++].init(b, c, a);
			block[m++].init(c, a, b);
			block[m++].init(c, b, a);
		}
		sort(block, block + m, comp);

		int maxheight = 0;

		for (int i = 0; i < m; i++)
		{
			dp[i] = block[i].z;
			for (int j = 0; j < i; j++)
			{
				if (block[i].x > block[j].x&&block[i].y > block[j].y)
					dp[i] = max(dp[i], dp[j] + block[i].z);//直接用了一维数组 机智啊 
			}
			if (maxheight < dp[i])
				maxheight = dp[i];
		}
		printf("Case %d: maximum height = %d\n", cas++, maxheight);
		memset(dp, 0, sizeof(dp));
	}
	return 0;
}




/*int maxn = 32;
int dp[maxn][maxn];//dp[i][j] 当底面积是i时 dp[i][j]存放的是总的高度
int block[maxn][3];
int n;


int main()
{
	memset(dp, 0, sizeof(dp));
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));
	memset(z, 0, sizeof(z));
	int cas = 1;
	while (scanf("%d", &n) == 1 && n)
	{
		for (int i = 0; i < n; i++)
		{
			for(int j = 0; j < 3; j++)
				scanf("%d", &block[i][j]);
			sort(block[i], block[i] + 3);//三条边从小到大排序
		}



	}


	printf("case %d")
	return 0;
}*/
