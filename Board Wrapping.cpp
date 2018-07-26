#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-10;

struct Point
{
	double x, y;
	Point(double x = 0,double y=0):x(x),y(y){}
};

typedef Point Vector;

Vector operator+(Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator-(Vector a, Vector b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator*(Vector a, double p) { return Vector(a.x *p, a.y *p); }
Vector operator/(Vector a, double p) { return Vector(a.x/p, a.y/p); }
bool operator<(const Point&a, const Point&b) { return a.x < b.x || (a.x == b.x&&a.y < b.y); }

double Cross(Vector a, Vector b) { return a.x*b.y - a.y * b.x ;};
Vector Rotate(Vector a, double rad) { return Vector(a.x*cos(rad) - a.y*sin(rad), a.x*sin(rad) + a.y*cos(rad)); }
double polygonArea(Point* p, int n)
{
	double area = 0;
	for (int i = 1; i < n - 1; i++)
		area += Cross(p[i] - p[0], p[i + 1] - p[0]);
	return area / 2;
}

double to_rad(double deg) { return deg / 180 * pi; }//角度转弧度

int ConvexHull(Point* p, int n, Point* ch)
{
	sort(p, p + n);		//先比较x坐标，再比较y坐标 
	int m = 0;
	for (int i = 0; i < n; i++) {
		while (m > 1 && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) m--;
		ch[m++] = p[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; i--) {
		while (m > k && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 1]) <= 0) m--;
		ch[m++] = p[i];
	}
	if (n > 1) m--;
	return m;
}



int main()
{
	int T;
	scanf("%d", &T);
	Point P[2500], ch[2500];

	while (T--)
	{
		int tmp = 0;
		double area1 = 0, area2 = 0;
		int n;//n块木板
		scanf("%d", &n);
		for(int i=0;i<n;i++)
		{
			double x, y, w, h, j,ang;
			scanf("%lf%lf%lf%lf%lf", &x, &y, &w, &h, &j);
			Point center(x, y);
			ang = -to_rad(j);//将逆时针转为顺时针 并且将角度值换为了弧度制
			P[tmp++] = center + Rotate(Vector(-w / 2, -h / 2), ang);
			P[tmp++] = center + Rotate(Vector(w / 2, -h / 2), ang);
			P[tmp++] = center + Rotate(Vector(-w / 2, h / 2), ang);
			P[tmp++] = center + Rotate(Vector(w / 2, h / 2), ang);
			area1 += w*h;
		}
		int m = ConvexHull(P, tmp, ch);
		area2 = polygonArea(ch, m);
		printf("%.1f %%\n",area1*100/area2);
	}
	return 0;
}
