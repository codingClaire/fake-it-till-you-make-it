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
	for(int k=i+1;k<=j;k++)//��i+1������j  
	  m=min(m,dp(k,j));//�������С��dp(k,j) ȡ�����֮�������� 
	for(int k=i;k<j;k++)//��i������j 
	 d[i][j]=s[j]-s[i-1]-m;//s[j]-s[i-1]��ʾ����i�� j��Ԫ�غ� 
	return d[i][j];
 } 
 
 int main()
 {
 	while (scanf("%d",&n)&&n)//���� 
 	{
 		s[0]=0;
 		for(int i=1;i<=n;i++)
 		{
 			scanf("%d",&a[i]);
 			s[i]=s[i-1]+a[i];//s[]�����ǰn��� ���Ԥ����ֵ�ý�� 
		 }
		 memset(vis,0,sizeof(vis));//��ʼ��vis 
		 printf("%d\n",2*dp(1,n)-s[n]);//dp(1,n)-(sum(1,n)-dp(1,n)) ���������˷����Ĳ� 
	 }
	return 0;
 }
