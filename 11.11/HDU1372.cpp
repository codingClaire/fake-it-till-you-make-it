#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
 
struct node
{
	char bx,tx;
	int  by,ty,num;
};

int dir[8][2] =
{
	{ 1,2 },{ 1,-2 },
	{-1,2},{-1,-2},
	{2,1},{2,-1},
	{-2,1},{-2,-1}
};

char from,to;
int  f,t;

void dfs()
{
	queue<node> q;
	node step,p;
	p.bx=from;
	p.by=f;
	p.num=0;
	q.push(p);
	while(!q.empty())
	{
		p=q.front();
		q.pop();
		if(p.bx==to&&p.by==t)
		{
			cout<<"To get from "<<from<<f<<" to "<<to<<t<<" takes "<<p.num<<" knight moves.\n";
			break;
		}
		for(int i=0;i<8;i++)
		{
			step.bx=p.bx+dir[i][0];
			step.by=p.by+dir[i][1];
			if(step.bx>='a'&&step.bx<='h'&&step.by>=1&&step.by<=8)//判断有没有过界； 
				{
					step.num=p.num+1;
					step.tx=p.tx;
					step.ty=p.ty;
					q.push(step);
				}
		}
	}
}

int main()
{
	while(scanf("%c%d %c%d",&from,&f,&to,&t)!=EOF)
		dfs();
	return 0;
}

