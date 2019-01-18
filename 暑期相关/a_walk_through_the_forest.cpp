/*�����������������ģ�A,B����·�ߣ�����һ����B�����ؼҵ�·�������д�A�����ؼҵ�·������*/
/*d[B]��̵� Ҫ��d[A]��Ļ���*/

#include<cstdio>
#include<iostream>
#include<queue>
#include<cstdlib>
#include<cstring>

using namespace std;

const int maxn = 1000;
const int maxdist = 1000000;
const int INF = 100000000;
int n, m;

struct Edge
{
	int from, to, dist;
	Edge(int u = 0, int v = 0,int d=0):from(u),to(v),dist(d){}
};

struct HeapNode
{
	int d, u;
	bool operator<(const HeapNode& rhs) const
	{
		return d > rhs.d;
	}
};

struct Dijkstra
{
	int n, m;//n���� m����
	vector<Edge> edges; //���б�
	vector<int> G[maxn];//ÿ���ڵ�����ı߱��
	bool done[maxn]; //�Ƿ��Ѿ����ñ��
	int d[maxn];  //s��������ľ���
	int p[maxn]; //���·����һ����
	long long dp[maxn];

	void init(int n)
	{
		this->n = n;
		for (int i = 0; i < n; i++)
			G[i].clear();
		edges.clear();
		memset(dp, -1, sizeof(dp));//��dp���������Ԫ�س�ʼ��Ϊ-1
	}

	void AddEdge(int from, int to, int dist)
	{
		edges.push_back((Edge) { from, to, dist });
		m = edges.size();
		G[from].push_back(m - 1);
	}
	void dijkstra(int s)
	{
		priority_queue<HeapNode> Q;//���ȶ��� 
		for (int i = 0; i < n; i++)
			d[i] = INF;
		d[s] = 0;
		memset(done, 0, sizeof(done));
		Q.push((HeapNode) { 0, s });
		while (!Q.empty())
		{
			HeapNode x = Q.top();
			Q.pop();
			int u = x.u;
			if (done[u])//��ȡ�����Ľڵ��Ѿ���ȡ������ Ӧ��ֱ���ӵ� 
				continue;//��������ѭ��
			done[u] = true;
			for (int i = 0; i < G[u].size(); i++)
			{
				Edge& e = edges[G[u][i]];
				if (d[e.to] > d[u] + e.dist)
				{
					d[e.to] = d[u] + e.dist;//�ɳڲ���
					p[e.to] = G[u][i];
					Q.push((HeapNode) { d[e.to], e.to });
				}
			}
		}
	}
	long long DP(int s)//��Dijkstra�ṹ������Ĳ���
	{
		if (s == 1) return 1;
		if (dp[s] != -1) return dp[s];
		else
		{
			dp[s] = 0;
			for (int i = 0; i < G[s].size(); i++)
			{
				Edge e = edges[G[s][i]];
				if (d[e.to] < d[s])
					dp[s] += DP(e.to);
			}
		}
		return dp[s];
	}
}Dij;//�ṹ�����

int main()
{
	while (scanf("%d%d", &n, &m)==2&&n)
	{
		Dij.init(n);
		int start, endding, time;
		for (int i = 0; i < m; i++)
		{
			scanf("%d%d%d", &start, &endding, &time);
			start--;
			endding--;//?????
			Dij.AddEdge(start, endding, time);
			Dij.AddEdge(endding, start, time);//����ͼ ��ӱߵ�ʱ��Ҫ��������
		}
		Dij.dijkstra(1);
		cout << Dij.DP(0) << endl;
	}
	return 0;
}
