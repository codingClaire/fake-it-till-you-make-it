#include<iostream>
using namespace std;


long long extend_gcd(long long a, long long b, long long &x, long long &y)
{
	if (a == 0 && b == 0) return -1;
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	long long d = extend_gcd(b, a%b, y, x);
	y -= a / b*x;
}


int main()
{
	scanf("%d", cas);
	while (cas--)
	{
		scanf("%d%d%d", &n, &a, &b);

		if
			printf("Case #%d: Iaka\n", cas+1);
		else
			printf("Case #%d: Yuwgna\n", cas+1);
	}
}