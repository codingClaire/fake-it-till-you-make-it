#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Point
{
	double x, y;
	Point(double x=0,double y=0):x(x),y(y){}
};

typedef Point Vector;

Vector operator+(Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator-(Vector a, Vector b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator*(Vector a, double p) { return Vector(a.x *p, a.y *p); }
Vector operator/(Vector a, double p) { return Vector(a.x / p, a.y / p); }
bool operator<(const Point&a, const Point&b) { return a.x < b.x || (a.x == b.x&&a.y < b.y); }
double Dot(Vector A, Vector B){ return A.x*B.x + A.y*B.y;}
double Cross(Vector a, Vector b) { return a.x*b.y - a.y * b.x; };
Vector Rotate(Vector a, double rad) { return Vector(a.x*cos(rad) - a.y*sin(rad), a.x*sin(rad) + a.y*cos(rad)); }
double Length(Vector A) { return sqrt(Dot(A, A));}
double Distance_To_Line(Point A, Point B, Point P)
{
	Vector v1 = B - A,v2 = P - A;
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


int MAXN = 10000+5;

int main()
{
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		int n;
		scanf("%d", &n);//n¸öµã
		Point house[MAXN], ch[MAXN];
		for (int j = 0; j < n; j++)
		{
			scanf("%lf%lf", &house[j].x, &house[j].y);
		}
		int m=ConvexHull(house, n, ch);
		double dist=0,mindist;
		
		for (int j = 0; j < m-1; j++)
		{
			for (int k = 0; k < n; k++)
			{
				dist += Distance_To_Line(ch[j], ch[j + 1], house[k]);
			}
			
			if (j == 0) mindist = dist;
			else if (dist < mindist) 
				mindist = dist;
		}
		printf("case #%d ", i + 1);
		printf("%.3lf\n", mindist);
	}
}





