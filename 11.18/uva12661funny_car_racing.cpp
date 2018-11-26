#include<vector>
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;

const int maxn = 300 + 10;
const int INF = 1000000000;

struct edge
{
	int from, to, start,end,time;
	edge(int u, int v, int a, int b, int t):from(u), to(v), start(a), end(b), time(t){}
};

vector<edge> edges;
vector<int> G[maxn];
bool inq[maxn];
int n, m, s, t, d[maxn];

void init()
{
	edges.clear();
	for (int i = 0; i < n; i++) G[i].clear();
}

void AddEdge(int u, int v, int a, int b, int t)
{
	edges.push_back(edge(u, v, a, b, t));
	int m = edges.size();
	G[u].push_back(m - 1);
}

void SPFA()
{
	memset(inq, false, sizeof(inq));
	for (int i = 0; i < n; i++)
		d[i] = INF;
	queue<int> q;
	d[s] = 0;
	inq[s] = true;
	q.push(s);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		inq[u] = false;
		for (int i = 0; i < G[u].size(); i++)
		{
			edge& e = edges[G[u][i]];
			int v = e.to;
			int a = e.start;
			int b = e.end;
			int t = e.time;
			if (a < t) continue;
			int now = d[u] % (a + b);
			if (now + t <= a)
			{
				if (d[v] > d[u] + t)
				{
					d[v] = d[u] + t;
					q.push(v);
					inq[v] = true;
				}
			}
			else
			{
				int wait = a + b - now;
				if (d[v] > d[u] + wait + t)
				{
					d[v] = d[u] + wait + t;
					q.push(v);
					inq[v] = true;
				}
			}
		}
	}
}

int main()
{

	int cas = 0;
	while (scanf("%d%d%d%d", &n, &m, &s, &t) == 4)
	{
		s--;
		t--;
		init();
		for (int i = 0; i < m; i++)
		{
			int u, v, a, b, t;
			scanf("%d%d%d%d%d", &u, &v, &a, &b, &t);
			AddEdge(u - 1, v - 1, a, b, t);

		}
		SPFA();
		printf("Case %d: %d\n", ++cas, d[t]);
	}
	return 0;
}
