struct HeapNode
{
	int d, u;
	bool operator<(const HeapNode& rhs) const
	{
		return d > rhs.d;
	}
};//���ȶ����е�Ԫ������

struct Dijkstra//Ϊ��ʹ�÷��� ֱ�Ӱ��㷨�����õ������ݽṹ��װ��Dijkstra�ṹ����
{         
	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool done[maxn]; //�Ƿ��Ѿ����ñ��
	int d[maxn];  //s��������ľ���
	int p[maxn]; //���·����һ����

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
}//�ṹ�����

/*https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm */
/*Bellman-Ford Algorithm*/
for (int i = 0; i < n; i++)
	d[i] = INF;
d[0] = 0;
for��int k = 0; k < n - 1;k++)
	for (int i = 0; i < m; i++)
	{
		int x = u[i], y = v[i];
		if (d[x] < INF)
			d[y] = min(d[y], d[x] + w[i]);
	}
/*time complexity :O(mn)*/

/*FIFO���� ���������ѭ�����*/

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
/*��ÿ����֮������·*/

//��ʼ������ؽ��� ��P364

for (int k = 0; k < n; k++)
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
//����ĳ� d[i][j]=d[i][j]||(d[i][k]&&d[k][j]) ����ͼ�Ĵ��ݱհ�