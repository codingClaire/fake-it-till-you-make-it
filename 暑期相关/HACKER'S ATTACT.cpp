#include <cstdio>
#include <cstring>
#include <algorithm>
#include<cmath>
 
using namespace std;
 
int n,ct=0;
const int maxn=1000;
int P[maxn],cover[maxn],f[maxn];
 
int main()
{
	while(scanf("%d", &n)==1&&n)
	{
	 	for (int i = 0; i < n;i++)
		{
			int m, x;
			scanf("%d", &m);
			P[i] == 1 << i;	
			while (m--)
			{
				scanf("%d", &x);
				P[i] |= (1 << x);
			}
		}
		for (int S=0; S<(1<<n);S++)
		{
			cover[S]=0;
			for (int i=0; i<n; i++)
			{
				if (S&(1 << i)) 
					cover[S] |= P[i];
			}
		}
		f[0] = 0;
		int ALL = (1<<n)-1;
		int S;
		for (S=1; S<(1<<n);S++)
		{
			f[S]=0;
			for(int S0=S;S0;S0=(S0-1)&S)
				if (cover[S0]==ALL)
					f[S] = max(f[S], f[S^S0] + 1);
		}
	printf("Case %d: %d\n",++ct,f[S-1]);
	}
	return 0;
}
/*ACversion*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int node[20];
int ans[1<<17],cover[1<<17];//cover 预处理所有状态下集合并情况
/*位运算符 :用于二进制运算 左移 << 相当于 a << b = a * (2的b次方) 右移 >> 相当于 a >> b = a /(2的b次方)*/ 
int n;
int main()
{
    int C=0;
    while(scanf("%d",&n)==1&&n)
    {
        int m,i,j,t;
        for(i=0;i<n;i++)
        {
            node[i]=1<<i;
            scanf("%d",&m);
            for(j=0;j<m;j++)
            {
                scanf("%d",&t);
                node[i]|=1<<t;
            }
        }
        int ALL=(1<<n)-1,S,S0;
        for(S=1;S<=ALL;S++) //预处理
        {
            cover[S]=0;
            for(i=0;i<n;i++)
                if(S&(1<<i))cover[S]|=node[i];
        }
        /*for(S=1;S<=Max;S++) //dp
        {
            ans[S]=0;
            for(S0=S;S0;S0=(S0-1)&S)
            {
                if(cover[S0]==Max)
				    ans[S]=max(ans[S],ans[S^S0]+1);
            }
        }*/
		for (S=1; S<=ALL;S++)
		{
			ans[S]=0;
			for(int S0=S;S0;S0=(S0-1)&S)
				if (cover[S0]==ALL)
					ans[S] = max(ans[S], ans[S^S0] + 1);
		} 
        printf("Case %d: %d\n",++C,ans[ALL]);
    }
    return 0; 
}

