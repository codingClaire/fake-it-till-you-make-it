#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int MAXN = 505;
const int MAXM = 5005;
const int INF = 0x3f3f3f3f;
int n, start, endding;
int head[MAXN], len;
int dis_s[MAXN], dis_r[MAXN], path_s[MAXN], path_r[MAXN];//s����㵽�������֮ǰ r �������֮���յ� 


struct edge
{
	int to, val, next;
}e[MAXM];

struct node
{
	int from;
	int val;
	node(int f, int v) { from = f; val = v; }
	bool operator <(const node& b)const
	{
		return val > b.val;
	}
};

void add(int from, int to, int val)
{
	e[len].to = to;
	e[len].val = val;
	e[len].next = head[from];
	head[from] = len++;
}


void dijkstra(int start, int dist[], int path[])
{
	bool vis[MAXN] = { 0 };
	dist[start] = 0;

	priority_queue<node> q;
	q.push(node(start, 0));//��ʼ�� 
	int num = 0;
	while (!q.empty())
	{
		node temp = q.top();
		q.pop();

		if (vis[temp.from])
			continue;
		vis[temp.from] = true;
		if (num == n)
			break;
		for (int i = head[temp.from]; i != -1; i = e[i].next)
		{
			if (!vis[e[i].to] && dist[temp.from] + e[i].val < dist[e[i].to])
			{
				dist[e[i].to] = dist[temp.from] + e[i].val;
				path[e[i].to] = temp.from;
				q.push(node(e[i].to, dist[e[i].to]));
			}
		}
	}
}

void print(int now)
{
	if (path_s[now] != -1)
		print(path_s[now]);
	if (now != endding)
		printf("%d ", now);
	else
		printf("%d\n", now);
}

int main()
{
	bool not_first = false;
	while (~scanf("%d%d%d", &n, &start, &endding))
	{
		if (not_first)
			printf("\n");
		not_first = true;
		
		len = 0;
		for (int i = 1; i <= n; i++)
		{
			dis_s[i] = dis_r[i] = INF;
			head[i] = path_r[i] = path_s[i] = -1;
		}
		int eco;//����
		scanf("%d", &eco);
		for (int i = 1; i <= eco; i++)
		{
			int from, to, time;
			scanf("%d%d%d", &from, &to, &time);
			add(from, to, time);//��
			add(to, from, time);//��
		}
		dijkstra(start, dis_s, path_s);
		dijkstra(endding, dis_r, path_r);

		int commercial;//����
		scanf("%d", &commercial);
		int commercial_from = -1, commercial_to, commercial_time, sigmatime = dis_s[endding];

		for (int i = 0; i < commercial; i++)
		{
			int from, to, time, temp;
			scanf("%d%d%d", &from, &to, &time);
			temp = dis_s[from] + dis_r[to] + time;//����ʱ����� 
			//��
			if (temp < sigmatime)
			{
				sigmatime = temp;//�ɳڲ���
				commercial_from = from;
				commercial_to = to;//���������ϳ��� 
				commercial_time = time;
			}
			temp = dis_s[to] + dis_r[from] + time;
			//��
			if (temp < sigmatime)
			{
				sigmatime = temp;
				commercial_from = to;
				commercial_to = from;
				commercial_time = time;
			}
		}

		if (commercial_from ==-1)
			print(endding);
		else
		{
			print(commercial_from);
			int now = commercial_to;
			while (now != endding)
			{
				printf("%d ", now);
				now = path_r[now];
			}//���ʳ�վ��˳��
			printf("%d\n", endding);
		}
		if (commercial_from == -1)//�����񳵵�û�иı� 
			printf("Ticket Not Used\n");
		else
			printf("%d\n", commercial_from);//�����ϳ���
		printf("%d\n", sigmatime);//��ʱ��
	}
	return 0;
}

