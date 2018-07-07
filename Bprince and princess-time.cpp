#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

int main()
{
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;i++)
	{
		int n,p,q;
	//	scanf("%d%d%d",&n,&p,&q);
	scanf("%d%d",&p,&q);
		int a[p+1],b[q+1];
		for(int j=0;j<p+1;j++)
			scanf("%d",&a[i]);
		for(int k=0;k<q+1;k++)
	    	scanf("%d",&b[k]);//序列输入 
	    int c[p+2][q+2]={0};
	    for(int j=1;j<p+2;j++)
	    {
	    	for(int k=1;k<q+2;k++)
	    	{
	    		if(a[j-1]==b[k-1])
	    		    c[j][k]=c[j-1][k-1]+1;
	    		else
	    			c[j][k]=max(c[j-1][k],c[j][k-1]);
			}
		}
		for(int j=0;j<p+2;j++)
		{
			for(int k=0;k<q+2;k++)
			{
				printf("%d ",c[j][k]);
			}
			printf("\n");
	   }
	}
 return 0;
}
/* LCSmethod
using namespace std;

int main()
{
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;i++)
	{
		int n,p,q;
		scanf("%d%d%d",&n,&p,&q);
		int a[p+1],b[q+1];
		for(int j=0;j<p+1;j++)
			scanf("%d",&a[i]);
		for(int k=0;k<q+1;k++)
	    	scanf("%d",&b[k]);//序列输入 
	    int c[p+2][q+2]={0};
	    for(int j=1;j<p+2;j++)
	    {
	    	for(int k=1;k<q+2;k++)
	    	{
	    		if(a[j-1]==b[k-1])
	    		    c[j][k]=c[j-1][k-1]+1;
	    		else
	    			c[j][k]=max(c[j-1][k],c[j][k-1]);
			}
		}
		for(int j=0;j<p+2;j++)
		{
			for(int k=0;k<q+2;k++)
			{
				printf("%d ",c[j][k]);
			}
			printf("\n");
	   }
	}
 return 0;
}*/

