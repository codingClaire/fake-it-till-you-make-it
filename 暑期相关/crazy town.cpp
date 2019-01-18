/*线段AB与直线相交的条数即是步数*/
#include<cstdio>
#include<cmath>
#include<iostream>

using namespace std;

const double eps = 1e-7;

int main()
{
	double x1, x2, y1, y2;
	scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
	int ans = 0;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		double a, b, c;
		scanf("%lf%lf%lf", &a, &b, &c);
		if ((a*x1 + b*y1 + c)*(a*x2 + b*y2 + c) < eps)
			ans++;
	}
	printf("%d\n", ans);
	return 0;
}

