#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxn=250*250;
const int INF=0X3F3F3F3F; 
int numA[maxn],a[maxn],g[maxn],d[maxn];

int main()
{
	int T;
	cin>>T;
	for(int i=0;i<T;i++)
	{
		int n,p,q;
		scanf("%d%d%d",&n,&p,&q);
		memset(numA,0,sizeof(numA));
		for(int j=0;j<p+1;j++)
		{
			scanf("%d",&a[j]);
		 } 
		 int f=0;
		for(int k=0;k<q+1;k++)//���Ǵ���ģ���Ϊֻ����b��Ԫ�ر�a�������²����� 
		{
			int x,flag=0;
			scanf("%d",&x);
			for(int m=0;m<p+1;m++)
			{
				if(x==a[m])
				{
					numA[f++]=m+1;
					flag=1;	
				}
			}
			if(flag==0)
			   numA[f++]=0;//����B��A��ͬԪ����A�е���� 
		}
		for(int j=1;j<=f;j++) g[i]=INF;
		int length=0;
		for(int k=0;k<f;k++)
		{
			int tmp=lower_bound(g+1,g+n+1,numA[i])-g;
			d[i]=tmp;
			g[tmp]=numA[i];
			length=max(length,d[i]);//�ҵ�d[i]���ֵ 
		}
		cout<<"Case "<<i+1<< ": "<< length<<endl;
	} 
	return 0;
}//Case 1: 4
/*��ʱ�� 
//����ת��Ϊ��numA�������������
		int longsub[f];
		for(int j=0;j<f;j++)
			longsub[j]=1;
		for(int j=1;j<f;j++)
		{
			for(int k=0;k<j;k++)
			{
				if(longsub[k]<longsub[j]+1&&numA[k]>=numA[j])
					longsub[j]=longsub[k]+1;
					//cout<<k<<" "<<longsub[k]<<endl;
			}
		}
		int length=0;
		for(int j=0;j<f;j++)
		{
			if(longsub[j]>length)
				length=longsub[j];
		}
		cout<<"case:"<<i+1<<" "<< length<<endl; */ 
