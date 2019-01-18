#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=110;
int s[maxn],a[maxn],d[maxn][maxn],vis[maxn][maxn],n;

int dp(int i,int j)
{
	if(vis[i][j])
	  return d[i][j];
	vis[i][j]=1;
	int m=0;
	for(int k=i+1;k<=j;k++)//从i+1遍历到j  
	  m=min(m,dp(k,j));//求出了最小的dp(k,j) 取了左边之后的情况？ 
	for(int k=i;k<j;k++)//从i遍历到j 
	 d[i][j]=s[j]-s[i-1]-m;//s[j]-s[i-1]表示的是i到 j的元素和 
	return d[i][j];
 } 
 
 int main()
 {
 	while (scanf("%d",&n)&&n)//输入 
 	{
 		s[0]=0;
 		for(int i=1;i<=n;i++)
 		{
 			scanf("%d",&a[i]);
 			s[i]=s[i-1]+a[i];//s[]存的是前n项和 这个预处理值得借鉴 
		 }
		 memset(vis,0,sizeof(vis));//初始化vis 
		 printf("%d\n",2*dp(1,n)-s[n]);//dp(1,n)-(sum(1,n)-dp(1,n)) 就是两个人分数的差 
	 }
	return 0;
 }
