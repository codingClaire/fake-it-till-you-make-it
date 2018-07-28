#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;

const double eps = 1e-10;

struct Point
{
	double x, y;
	Point(double x = 0,double y = 0) :x(x), y(y) {}
};

typedef Point Vector;

Vector operator+(Vector A, Vector B)
{
return Vector(A.x + B.x, A.y + B.y);
}
Vector operator-(Vector A, Vector B)
{
	return Vector(A.x - B.x, A.y - B.y);
}
Vector operator*(Vector A, double p)
{
	return Vector(A.x *p, A.y *p);
}
Vector operator/(Vector A, double p)
{
	return Vector(A.x / p, A.y / p);
}
bool operator <(const Point& a, const Point& b)
{
	return a.x < b.x || (a.x == b.x&&a.y < b.y);
}
int dcmp(double x)
{
	if (fabs(x) < eps) return 0;
	else return x < 0 ? -1 : 1;
}
bool operator ==(const Point &a, const Point &b)
{
	return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
double Dot(Vector A, Vector B)
{
	return A.x*B.x + A.y*B.y;
}
double Length(Vector A)
{
	return sqrt(Dot(A, A));
}
double Angle(Vector A, Vector B)
{
	return acos(Dot(A, B) / Length(A) / Length(B));
}
double Cross(Vector A, Vector B)
{
	return A.x * B.y - A.y*B.x; 
}
double paraArea(Point A, Point B, Point C)
{
	return Cross(B - A, C - A);
}
Vector Rotate(Vector A, double rad)
{
	return Vector(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.x*cos(rad));
}
Vector Normal(Vector A)
{
	double L = Length(A);
	return Vector(-A.y / L, A.x / L);
}
Point Get_Line_Intersection(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P - Q;
	double t = Cross(w, u) / Cross(v, w);
	return P + v*t;
}
double Distance_To_Line(Point A, Point B, Point P)
{
	Vector v1 = B - A,v2 = P - A;
	return fabs(Cross(v1, v2) / Length(v1));
}

Point up[5005], low[5005],toy[5005];

int main()
{
	int n, m, x1, y1, x2, y2;
	
	while (scanf("%d", &n)!=EOF)
	{
		int num[5005] = { 0 };
		if(n==0) break;
		scanf("%d%d%d%d%d", &m, &x1, &y1, &x2, &y2);
		for (int i = 0; i < n; i++)
		{
			up[i].y = y1;
			low[i].y = y2;
			scanf("%lf%lf", &up[i].x, &low[i].x);
		}
		for (int i = 0; i < m; i++)
		{
			scanf("%lf%lf", &toy[i].x, &toy[i].y);
		}
		for (int i = 0; i < m; i++)
		{
			int j = 0;
		    while(((up[j].x-low[j].x)*(toy[i].y-up[j].y)-(up[j].y-low[j].y)*(toy[i].x-up[j].x))<0)
			{
				j++;
				if(j>n-1)
				break;
			}
			num[j]++;
		}
		for (int i = 0; i <= n; i++)
			printf("%d: %d\n", i,num[i]);
	 printf("\n");
	}
	return 0;
}
