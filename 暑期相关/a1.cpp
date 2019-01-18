#include<iostream>
#include<algorithm>

using namespace std;

/*int lastOne(int n,int k)
{
	int last=0;
	for(int i=2;i<n;i++)
	{
		last=(last+k)%i;
	}
	return last;
}*/

int main()
{
	int m,n,k;
	while(cin>>n>>m>>k)
	{
	    int dp[1000];
	    for(int i=2;i<=n;i++)
	    {
	    	dp[i]=(dp[i-1]+k)%i;
		}
		int last=(m-k+1+dp[n])%n;
		if (last<0) last+=n;
		cout<<last<<endl;
	}
	return 0;
 } 
