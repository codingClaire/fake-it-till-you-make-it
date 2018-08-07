#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>

using namespace std;

const int maxn = 1000 + 10;
int fa[maxn*maxn];
int T;
int n, m;
int field[maxn][maxn];
int tol;//���� �ӱ�ǰ��ֵΪ0

struct Edge
{
	int start, endding, w;
}edge[maxn*maxn];


void addedge(int st, int en, int w)//���ӱ�
{
	edge[tol].start = st;
	edge[tol].endding = en;
	edge[tol].w = w;
	tol++;
}

bool cmp(Edge a, Edge b)
{
		return a.w < b.w; //������ ����Ȩֵ����	
}


int find(int x)//���ҽ��x�������ĸ��ڵ�
{
	//if (fa[x] == -1)
	if(x==fa[x])
	  return x;
	return fa[x] = find(fa[x]);
}

int Kruskal(int n)
{
	
	memset(fa, -1, sizeof(fa));//��ʼ�����鼯

	int cnt = 0;//��¼����ı�
	int ans = 0;//��¼��С�������ĳ���
	sort(edge,edge+tol,cmp);
	printf("1 cnt and n is %d %d",cnt,n);
	for (int i = 0; i < tol; i++)
	{
		int st = edge[i].start;
		int en = edge[i].endding;
		int w = edge[i].w;
		int t1 = find(st);
		int t2 = find(en);
		if (t1 != t2)//��ʼ����յ㲻����ͬһ����
		{
			ans += w;
			fa[t1] = t2;//�ϲ�
			cnt++;
			printf("sum is %d\n",ans);
			printf("cnt is %d\n",cnt);
		}
		if (cnt == n - 1)
			break;//����ıߵ��ڶ�������1 ˵���ҵ���������
	}
	printf("last ans %d\n",ans);
	printf("last cnt and n is %d %d\n",cnt,n);
	
	if (cnt < n - 1)
		return -1;//����������
	 return ans;
}


int find2(int x)
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
int main()
{
	scanf("%d", &T);
	int cas=1;
	while (T--)
	{
		//memset(edge,0,sizeof(edge));
		scanf("%d%d", &n, &m);
		tol=0;
		for (int i = 0; i < n; i++)
		{	
			for (int j = 0; j < m; j++)
			{
					
				scanf("%d", &field[i][j]);
				if (i == 0 && j == 0)
					continue;
				if (i == 0&&j!=0)
					addedge(j - 1, j, abs(field[i][j] - field[i][j - 1]));
				else if(j == 0&&i!=0)
					addedge(m*(i - 2), m*(i - 1), abs(field[i][j] - field[i - 1][j]));
				else if(i!=0&&j!=0)
				{
					addedge(m*(i - 1) + j - 1, m*(i - 1) + j, abs(field[i][j] - field[i][j - 1]));
					addedge(m*(i - 2) + j, m*(i-1) + j, abs(field[i][j] - field[i - 1][j]));
				}
			}
		}
	//	sort(edge,edge+tol,cmp);
		for(int i=0;i<tol;i++)
			printf("%d ",edge[i].w);
		printf("\n");	
		
		printf("Case #%d:\n",cas++);
		//printf("%d\n", sum);
		printf("%d\n",Kruskal(tol));

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


/*for(int i=0;i<=n*m;i++)
			fa[i]=i;
		int sum=0;
		printf("tol is %d\n",tol);
		for(int i=0;i<tol;i++)
		{
			int nx=find2(edge[i].start);
			int ny=find2(edge[i].endding);
			if(nx!=ny)
			{
				fa[nx]=ny;
				sum+=edge[i].w;
				printf("sum is %d\n",sum);
			}
		}*/
		
