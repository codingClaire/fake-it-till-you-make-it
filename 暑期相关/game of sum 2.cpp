#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=110;
int n,dp[maxn][maxn],sum[maxn],a[maxn];

int main(){
     while(scanf("%d",&n)&&n)
	 {
         for(int i=1;i<=n;++i)
         {
         	scanf("%d",&a[i]);
         	sum[i]=sum[i-1]+a[i];
         	dp[i][i]=a[i];
         }
         for(int len=1;len<n;len++)
		 {
             for(int l=1;l<=n-len;l++)
			 {
                int tmp=0;
                 for(int k=1;k<=len;k++)
				 {
                     tmp=min(tmp,min(dp[l+k][l+len],dp[l][l+len-k]));
                 }
                 dp[l][l+len]=sum[l+len]-sum[l-1]-tmp;
             }
         }
         cout<<dp[1][n]*2-sum[n]<<endl;
     }
  return 0;
 }
