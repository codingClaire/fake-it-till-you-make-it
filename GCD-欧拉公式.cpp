#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
int flag[10000001], prime[6000000], tot;
int phi[10000001];
void solve(long long end) 
{
	for (int i = 1; i <= end; i++)
		flag[i] = 1;//flag初始化全部置1 
	for (int i = 2; i <= end; i++) 
	{
		if (flag[i] == 1) 
		{
			prime[++tot] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= tot && prime[j] * i <= end; j++) 
		{
			flag[i*prime[j]] = 0;
			if (i%prime[j] == 0)
			{
				phi[i*prime[j]] = prime[j] * phi[i]; 
				break;
			}
			else phi[i*prime[j]] = (prime[j] - 1) * phi[i];
		}
	}
}
long long f[10000001];

int main() {
	long long n;
	scanf("%lld",&n); 
	solve(n);
	f[1] = 1;
	for (long long i = 2; i <= n; i++) 
		f[i] = f[i - 1] + phi[i] * 2;
	
	long long ans = 0;

	for (long long i = 1; i <= tot; i++) 
		ans = ans + f[n / prime[i]];
	printf("%d\n",ans);
	return 0;
}
