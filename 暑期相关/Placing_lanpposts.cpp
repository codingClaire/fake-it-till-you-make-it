/*树型动态规划*/ 
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

vector<int> adj[1010];
int vis[1010][2],d[1010][2],n,m;

int dp(int nodei,int j,int father)
{
	if(vis[nodei][j])
		return d[nodei][j];
	vis[nodei][j]=1;
	int& ans=d[nodei][j];
	ans=2000;
	for(int k=0;k<(int)adj[nodei].size();k++)
		if(adj[nodei][k]!=father)
			ans+=dp(adj[nodei][k],1,nodei);//所有i为父结点的子结点 
	//for over
		if(!j&&father>=0) ans++;
		
		if(j||father<0)
		{
			int sum=0;
			for(int k=0;k<(int)adj[nodei].size();k++)
				if(adj[nodei][k]!=father)
					sum+=dp(adj[nodei][k],0,nodei);
				if(father>=0) sum++;
				ans=min(ans,sum);
		} 
	return ans;
}

int main()
{
	int T,x,y;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)
		  adj[i].clear();
		for(int i=0;i<m;i++)
		{
			scanf("%d%d",&x,&y);
			adj[x].push_back(y);
			adj[y].push_back(x);	 
		}
	memset(vis,0,sizeof(vis));
	int ans=0;
	for(int i=0;i<n;i++)
		if(!vis[i][0])
			ans+=dp(i,0,-1);//i是根节点 
	printf("%d %d %d\n",ans/2000,m-ans%2000,ans%2000);
	}
	return 0;
}
