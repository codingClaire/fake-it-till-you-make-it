#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

const int INF = 0x3f3f3f3f;
int d[55][55];
int cut[55];
bool visit[55][55];
int L, n;

int dp(int i, int j)
{
	if ((j - i) <= 1) return 0;
	if (visit[i][j] == true) 
		return d[i][j];
	visit[i][j] = true;//����true�Ļ� ��visit[i][j]��ֵΪtrue
	//��ʾ�Ѿ����ʹ�
	for (int k = i + 1; k < j; k++)
		d[i][j] = min(d[i][j], dp(i, k) + dp(k, j) + cut[j] - cut[i]);
	//cut[j]-cut[i]��������i-j�ε�һ������Ҫ���ĵĽ�Ǯ  Ȼ���ٰ�����ֳ���i-k�κ�k-j�ε������� �����ӽṹ 
	return d[i][j];
}

int main()
{
	while (~scanf("%d", &L) && L)
	{
		scanf("%d", &n);
		for (int i = 1; i<=n; i++)
			scanf("%d", &cut[i]);
		cut[0] = 0;
		cut[n + 1] = L;
		memset(visit, false, sizeof(visit));
		memset(d, INF, sizeof(d));
		int ans = dp(0, n + 1);
		printf("The minimum cutting is %d.\n", ans);

	}
	return 0;
}

	/*for(int i=n-1;i>=0;i--)
		{
			for(int j=i+2;j<=n+1;j++)
			{
				d[i][j]=1005;
				for(int k=i+1;k<j;k++)
					d[i][j]=min(d[i][j],d[i][k]+d[k][j]+cut[j]-cut[i]);
			}
	    }	
		printf("The minimum cutting is %d.\n", d[0][n+1]); */ 
