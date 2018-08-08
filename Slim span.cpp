#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<set>
using namespace std;

const int maxn = 100 + 5;
const int maxm = 5000+ 10;
const int INF = 1000000000;
int fa[maxm];
int n, m;
int maxedge, minedge;
int diff,cnt,ans;

int max(int a,int b)
{
return a>b?a:b;
}

int min(int a,int b)
{
return a<b?a:b;
}
struct Edge
{
	int start, endding;
	double w;
}edge[maxm + 10];

int find(int x)//·��ѹ�� 
{
	int r = x;
	while (r != fa[r])
		r = fa[r];
	int i = x, j;
	while (i != r)
	{
		j = fa[i];
		fa[i] = r;
		i = j;
	}
	return r;
}

bool cmp(Edge a, Edge b)
{
	return a.w < b.w;
}//�Ƚ�

void Kruskal(int n)
{
	cnt = 0;//��¼����ı�
	ans = 0;//��¼��С�������ĳ���
	maxedge=0, minedge=INF;//ע�������ʼ��
	for(int i=1;i<=n;i++)
        fa[i]=i;//���鼯�ĳ�ʼ�� 
	sort(edge, edge + m, cmp);
	for (int i = n; i <= m; i++)
	{
		int t1 = find(edge[i].start);
		int t2 = find(edge[i].endding);
		if (t1 != t2)
		{
			ans += edge[i].w;
			maxedge = max(maxedge, edge[i].w);
			minedge = min(minedge, edge[i].w);
			fa[t1] = t2;//�ϲ�
			cnt++;
		}
		diff = INF;//����Сֵʱ���ĳ�ֵ��INF
		if (cnt == n - 1)
			//break;//����ıߵ��ڶ�������1 ˵���ҵ���������
			diff = min(diff, maxedge - minedge);
	}
}

int main()
{
	while (scanf("%d%d", &n, &m) == 2 && n != 0 && m != 0)
	{
		for (int i = 0; i < m; i++)
			scanf("%d%d%d", &edge[i].start, &edge[i].endding, &edge[i].w);
		for (int i = 1; m - i + 1 >= n - 1; i++)
			Kruskal(i);//?????

		if (diff == INF)
			printf("-1\n");
		else
			printf("the result is%d\n", diff);
	}
	return 0;
}
