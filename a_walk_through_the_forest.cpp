/*沿着满足如下条件的（A,B）道路走：存在一条从B出发回家的路，比所有从A出发回家的路径都短*/
/*d[B]最短的 要比d[A]最长的还短*/

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
	int n, m;//n点数 m边数
	vector<Edge> edges; //边列表
	vector<int> G[maxn];//每个节点出发的边编号
	bool done[maxn]; //是否已经永久标号
	int d[maxn];  //s到各个点的距离
	int p[maxn]; //最短路的上一条弧
	long long dp[maxn];

	void init(int n)
	{
		this->n = n;
		for (int i = 0; i < n; i++)
			G[i].clear();
		edges.clear();
		memset(dp, -1, sizeof(dp));//将dp数组的所有元素初始化为-1
	}

	void AddEdge(int from, int to, int dist)
	{
		edges.push_back((Edge) { from, to, dist });
		m = edges.size();
		G[from].push_back(m - 1);
	}
	void dijkstra(int s)
	{
		priority_queue<HeapNode> Q;//优先队列 
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
			if (done[u])//新取出来的节点已经被取出来过 应该直接扔掉 
				continue;//结束本次循环
			done[u] = true;
			for (int i = 0; i < G[u].size(); i++)
			{
				Edge& e = edges[G[u][i]];
				if (d[e.to] > d[u] + e.dist)
				{
					d[e.to] = d[u] + e.dist;//松弛操作
					p[e.to] = G[u][i];
					Q.push((HeapNode) { d[e.to], e.to });
				}
			}
		}
	}
	long long DP(int s)//比Dijkstra结构体多加入的部分
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
}Dij;//结构体结束

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
			Dij.AddEdge(endding, start, time);//无向图 添加边的时候要来回两次
		}
		Dij.dijkstra(1);
		cout << Dij.DP(0) << endl;
	}
	return 0;
}
