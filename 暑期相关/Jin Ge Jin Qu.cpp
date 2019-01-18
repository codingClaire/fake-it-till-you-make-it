//�ڸ�����Ŀ

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn = 180 * 50 + 5;
int n, maxtime;
int t[55];

struct Node
{
	int num;
	int time;
	bool operator<(const Node &rhs)const
	{ 
		return num<rhs.num||(num==rhs.num&&time<rhs.time); 
	}
};//�ȿ��ǳ������׸��� �ڴ˻������ٿ���ʱ����������

Node dp[maxn];
int songnum,remain;


int main()
{
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++)
	{
		memset(dp, 0, sizeof(dp));
		scanf("%d%d", &songnum,&maxtime);//�����ʱ�� ֱ�ӳ�ʼ��maxtime ����Ҳ���Գ���ʱ����������ʱ��
		int sum=0;
		for (int i = 1; i <= songnum; i++)
		{
			scanf("%d", &t[i]);
			sum += t[i];
		}

		maxtime = min(sum, maxtime - 1);//??????

		for (int i = 1; i <= songnum; i++)
		{
			for (int j = maxtime; j >= t[i]; j--)
			{
				Node tmp;
				tmp.num = dp[j - t[i]].num + 1;
				tmp.time = dp[j - t[i]].time + t[i];
				if (dp[j] < tmp)//�������غ���  
					dp[j] = tmp;
			}
		}
		printf("Case %d: %d %d\n", cas,dp[maxtime].num + 1, dp[maxtime].time + 678);
	}
	return 0;
}
