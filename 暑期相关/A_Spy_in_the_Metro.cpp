//d(i,j)��ʾ��ʱ��i,�ڳ�վj���ٻ���Ҫ�ȵ�ʱ�� �߽�������d(T,n)=0 ����d(T,i)Ϊ������
//���־��ߣ�1����һ���� 2��������յ㷽�򿪵� 3���������㷽�򿪵�

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 55;
const int maxt = 205;

int n,T;//n number of station
int t[maxn], d[maxn], e[maxn];
int m1, m2;
bool has_train[401][maxn][2];
int dp[maxt][maxn];

void init()
{
	memset(has_train, 0, sizeof(has_train));
	memset(dp, 63, sizeof(dp));//?????
	memset(t, 0, sizeof(t));
	memset(d, 0, sizeof(d));
	memset(e, 0, sizeof(e));
}


void timetable()
{
	for (int i = 0; i < m1; i++)
	{
		int time = d[i];
		for (int j = 1; j <= n; j++)
		{
			has_train[time][j][0] = true;//����㵽�յ�ĳ� 
			time += t[j];
		}
	}
	for (int i = 0; i < m2; i++)
	{
		int time = e[i];
		for (int j = n; j >= 1; j--)
		{
			
			has_train[time][j][1] = true;//���յ㵽���ĳ� 
			time += t[j - 1];
		}
	}
}


int main()
{
	int cas = 1;
	while (scanf("%d", &n) != EOF && n)
	{
		init();
		scanf("%d", &T);
		for (int i =1; i < n; i++)
			scanf("%d", &t[i]); 
 
		scanf("%d", &m1);
		for (int i = 0; i < m1; i++)
			scanf("%d", &d[i]);
		scanf("%d", &m2);
		for (int i = 0; i <m2; i++)
			scanf("%d", &e[i]);

		timetable();

	for (int i = 1; i <= n - 1; i++)
		dp[T][i] = INF;
	dp[T][n] = 0;

	for (int i = T - 1; i >= 0; i--)
		for (int j = 1; j <= n; j++)
		{
			dp[i][j] = dp[i + 1][j] + 1;//�ȴ�һ����
			if (j < n&&has_train[i][j][0] && i + t[j] <= T)
				dp[i][j] = min(dp[i][j], dp[i + t[j]][j + 1]);//����㵽�յ� 
			if (j > 1 && has_train[i][j][1] && i + t[j - 1] <= T)
				dp[i][j] = min(dp[i][j], dp[i + t[j - 1]][j - 1]);//���յ㵽��� 
		}


	printf("Case Number %d: ", cas++);
	if (dp[0][1] >= INF) printf("impossible\n");
	else printf("%d\n", dp[0][1]); 
	}
	return 0;
}
