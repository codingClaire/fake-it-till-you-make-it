#include<iostream>
#include<algorithm>
using namespace std;

const int maxn=10002;
int dp[maxn];

int main()
{
	int n,k,m;
	while(scanf("%d%d%d",&n,&k,&m)==3&&n)
	{
		dp[1]=0;
		int last;
		for(int i=2;i<=n;i++)
			dp[i]=(dp[i-1]+k)%i;
		last=(m-k+1+dp[n])%n;
		if(last<=0)last+=n;
		
		cout<<last<<endl; 
	}
	return 0;
}




/*

using namespace std;

int lastOne(int n,int k)
{
	int last=0;
	for(int i=2;i<n;i++)
	{
		last=(last+k)%i;
	}
	return last;
}

int main()
{
	int m,n,k;
	while(cin>>n>>m>>k)
	{
		int t=lastOne(n,k)+m;
		if(t<n)
		cout<<t+1<<endl;
		else cout<<t-n+1<<endl;
	}
	return 0;
 } */
