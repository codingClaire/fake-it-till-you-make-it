#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>

using namespace std;

const int maxn = 1000;
int fa[maxn*maxn+10];
int T;
int n, m;
int field[maxn][maxn];
int tol;//���� �ӱ�ǰ��ֵΪ0
int cnt;//��¼����ı�
int ans;//��¼��С�������ĳ���


struct Edge
{
	int start, endding, w;
}edge[maxn*maxn+10];

bool cmp(Edge a, Edge b)
{
	return a.w < b.w; //������ ����Ȩֵ����	
}

int find(int x)//·��ѹ�� 
{
	int r=x;
	while(r!=fa[r])
		r=fa[r];
	int i=x,j;
	while(i!=r)
	{
		j=fa[i];
		fa[i]=r;
		i=j;
	}
	return r;
}

int Kruskal(int n)
{
	int cnt = 0;//��¼����ı�
	int ans = 0;//��¼��С�������ĳ���
	sort(edge,edge+tol,cmp);
	for (int i = 0; i < tol; i++)
	{
		int t1 = find(edge[i].start);
		int t2 = find(edge[i].endding);
		if (t1 != t2)//��ʼ����յ㲻����ͬһ����
		{
			ans +=edge[i].w;
			fa[t1] = t2;//�ϲ�
			cnt++;
		}
		if (cnt == n - 1)
			break;//����ıߵ��ڶ�������1 ˵���ҵ���������
	//if (cnt < n - 1) return -1;//����������
	}
	 return ans;
}
int main()
{
	scanf("%d", &T);
	int cas = 1;
	while (T--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &field[i][j]);
		tol=0;
		for(int i=0; i<n; i++)
			for(int k=0; k<m; k++)
			{
				// ���� 
				if (k + 1 < m)
				{
					edge[tol].start = i* m + k;
					edge[tol].endding= i * m + k + 1;
					edge[tol++].w = abs(field[i][k] - field[i][k+1]); 
				}
				
				// ����
				if (i+ 1 < n)
				{
					edge[tol].start = i * m + k;
					edge[tol].endding = (i + 1) * m + k;
					edge[tol++].w = abs(field[i+1][k] - field[i][k]);	
				}  
			}	
	for(int j=0; j<=n*m; j++)
			fa[j] = j;
		printf("Case #%d:\n", cas++);
		printf("%d\n",Kruskal(n*m));
	}
return 0;
}

	
		
/*
2
4  3
9 12 4
7 8 56
32 32 43
21 12 12
2  3
34 56 56
12 23 4
*/


	/*	int sum=0;
		for (int j = 0; j <= n*m; j++)
			fa[j] = j;//��ʼ�����鼯
		sort(edge, edge + tol, cmp);//������õı߰���Ȩֵ����
		for(int j=0; j<tol; j++)
		{
			int t1 = find(edge[j].start);
			int t2= find(edge[j].endding);
			if (t1 != t2)
			{
				fa[t1] = t2;
				sum += edge[j].w;
			}	
		}
		printf("Case #%d:\n", cas++);
		printf("%d\n",sum); */

