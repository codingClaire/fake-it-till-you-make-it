#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Point
{
	double x, y;
	Point(double x = 0, double y = 0) :x(x), y(y) {}
};

typedef Point Vector;
Vector operator+(Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator-(Vector a, Vector b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator*(Vector a, double p) { return Vector(a.x *p, a.y *p); }
Vector operator/(Vector a, double p) { return Vector(a.x / p, a.y / p); }
bool operator<(const Point&a, const Point&b) { return a.x < b.x || (a.x == b.x&&a.y < b.y); }
double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Cross(Vector a, Vector b) { return a.x*b.y - a.y * b.x; };
Vector Rotate(Vector a, double rad) { return Vector(a.x*cos(rad) - a.y*sin(rad), a.x*sin(rad) + a.y*cos(rad)); }
double Length(Vector A) { return sqrt(Dot(A, A)); }
const double eps = 1e-10;
int dcmp(double x)
{
	if (fabs(x) < eps) return 0;
	else return x < 0 ? -1 : 1;
}
double Distance_To_Line(Point A, Point B, Point P)
{
	Vector v1 = B - A, v2 = P - A;
	return fabs(Cross(v1, v2) / Length(v1));
}
int ConvexHull(Point* p, int n, Point* ch)
{
	sort(p, p + n);
	int m = 0;
	for (int i = 0; i < n; i++)
	{
		while (m > 1 && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0)
			m--;
		ch[m++] = p[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; i--)
	{
		while (m > k&&Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0)
			m--;
		ch[m++] = p[i];
	}
	if (n > 1)
		m--;
	return m;
}
void change(double &A, double &B, double &C, Point a, Point b)
{
	A = b.y - a.y;
	B = a.x - b.x;
	C = b.x*a.y - a.x*b.y;
}

int MAXN = 10000 + 5;
const double pi = acos(-1.0);
const double INF = 1e9;
int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		int n;
		scanf("%d", &n);//n个点
		double sumx = 0, sumy = 0;
		Point house[MAXN], ch[MAXN];
		for (int j = 0; j < n; j++)
		{
			scanf("%lf%lf", &house[j].x, &house[j].y);
			sumx += house[j].x;
			sumy += house[j].y;
		}
		if (n <= 2)
		{
			printf("Case #%d: 0.000\n", i + 1);
			continue;
		}
		int m=ConvexHull(house, n,ch);
		double mindist=INF;
		
		for (int j = 0; j < m ; j++)
		{
			double A, B, C;
			change(A, B, C, ch[j], ch[(j + 1) % m]);
			double sumdist = fabs(A*sumx + B*sumy + C*n) / sqrt(A*A+B*B);//因为都是在同侧 去掉绝对值后Ax+By+C的值都是同号的，可以先合并，再取绝对值
			mindist = min(mindist, sumdist);
		}
		printf("Case #%d: ", i + 1);
		printf("%.3lf\n", mindist/n);//最后求的是平均距离
	}
}





