struct HeapNode
{
	int d, u;
	bool operator<(const HeapNode& rhs) const
	{
		return d > rhs.d;
	}
};//优先队列中的元素类型

struct Dijkstra//为了使用方便 直接把算法中运用到的数据结构封装在Dijkstra结构体中
{         
	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool done[maxn]; //是否已经永久标号
	int d[maxn];  //s到各个点的距离
	int p[maxn]; //最短路的上一条弧

	void init(int n)
	{
		this->n = n;
		for (int i = 0; i < n; i++)
			G[i].clear();
		edges.clear();
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
}//结构体结束

/*https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm */
/*Bellman-Ford Algorithm*/
for (int i = 0; i < n; i++)
	d[i] = INF;
d[0] = 0;
for（int k = 0; k < n - 1;k++)
	for (int i = 0; i < m; i++)
	{
		int x = u[i], y = v[i];
		if (d[x] < INF)
			d[y] = min(d[y], d[x] + w[i]);
	}
/*time complexity :O(mn)*/

/*FIFO队列 代替上面的循环检查*/

bool bellman_ford(int s)
{
	queue<int>	Q;
	memset(inq, 0, sizeof(inq));
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; i++)
		d[i] = INF;
	d[s] = 0;
	inq[s] = true;
	Q.push(s);

	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		inq[u] = false;//???
		for (int i = 0; i < G[u].size(); i++)
		{
			Edge& e = edges[G[u][i]];
			if (d[u]<INF&&d[e.to]>d[u] + e.dist)
			{
				d[e.to] = d[u] + e.dist;
				p[e.to] = G[u][i];
				if (!inq[e.to])
				{
					Q.push(e.to);
					inq[e.to] = true;
					if (++cnt[e.to] > n)
						return false;
				}
			}
		}
	}
	return true;
}

struct BellmanFord
{
	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool inq[maxn];
	int d[maxn];
	int p[maxn];
	int cnt[maxn];

	void init(int n)
	{
		this->n = n;
		for (int i = 0; i < n; i++)
			G[i].clear();
		edges.clear();
	}

	void AddEdge(int n)
	{
		edges.push_back((Edge) { from, to, dist });
		m = edges.size();
	}
};









/*Floyd algorithm*/
/*求每两点之间的最短路*/

//初始化的相关解释 紫P364

for (int k = 0; k < n; k++)
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
//如果改成 d[i][j]=d[i][j]||(d[i][k]&&d[k][j]) 有向图的传递闭包