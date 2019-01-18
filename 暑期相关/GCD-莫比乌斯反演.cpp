#include<cstdio>
#include<cstring>
#include<algorithm>

#define N 10000005

using namespace std;

int mu[N], p[N];
long long  n, ans, a[N];
bool bz[N];

int main() 
{
	scanf("%lld", &n); mu[1] = 1;
	for(int i = 2; i <= n;i++)
	{
		if (bz[i]==0) 
			p[++p[0]] = i, mu[i] = -1;
		for(int j=1;j<=p[0];j++) 
		{
			int k = i*p[j]; if (k>n) break; bz[k] = 1;
			if (!(i%p[j])) break; mu[k] = -mu[i];
		}
	}
	for (int i = 1; i <= p[0]; i++)
		for (int j = 1; j <= n / p[i];j++)
				a[p[i] * j] += mu[j];
	for (int i = 1; i <= n;i++) 
		a[i] += a[i - 1];
	
	for (long long  l = 1, r; l <= n; l = r + 1) 
	{
		long long x = n / l; 
		r = n / x;
		ans += (r - l + 1)*x*x*(a[r] - a[l - 1]);
	}
	printf("%lld", ans);
	return 0;
}
