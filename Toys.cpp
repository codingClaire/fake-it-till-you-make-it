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
double Distance_To_Segment(Point A, Point B, Point P)
{
	if (A == B)
		return Length(P - A); //A、B重合
	Vector v1 = B - A,v2 = P - A, v3 = P - B;
	if (dcmp(Dot(v1, v2)) < 0)
		return Length(v2);//A点在P、B之间
	else if (dcmp(Dot(v1, v3)) > 0)
		return Length(v3);//B点在P、A之间
	else
		return fabs(Cross(v1, v2)) / Length(v1);
}
Point Get_Line_Projection(Point P, Point A, Point B)
{
	Vector v = B - A;
	return A + v*(Dot(v, P - A) / Dot(v, v));
}
bool Segment_Proper_Intersection(Point a1, Point a2, Point b1, Point b2)
{
	double c1 = Cross(a2 - a1, b2 - b1),
		c2 = Cross(a2 - a1, b2 - b1),
		c3 = Cross(b2 - b1, a1 - b1),
		c4 = Cross(b2 - b1, a2 - b1);
	return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}
bool On_Segment(Point P, Point A, Point B)
{//判断点是否在线段上，不包含端点
	return dcmp(Cross(A - P, B - P)) == 0 && dcmp(Dot(A - P, B - P)) < 0;
}
double PolygonArea(Point *p, int n)
{//多边形的有向面积
	double area = 0;
	for (int i = 1; i < n - 1; i++)
	{
		area += Cross(p[i] - p[0], p[i + 1] - p[0]);
		return area / 2;
	}
}


struct Line
{
	Point p;
	Vector v;
	double angle;
	Line(Point p, Vector v) :p(p), v(v)
	{
		angle = atan2(v.y, v.x);// double atan2(double y,double x) 返回的是原点至点(x,y)的方位角，即与 x 轴的夹角
	}
//	Line(double x1=0,double y1=0,double x2=0,double y2=0):p.x(x1),p.y(y1),v.x(x2-x1),v.y(y2-y1){}
	Line(double x1=0,double y1=0,double x2=0,double y2=0)
	{
		p.x=x1;
		p.y=x2;
		v.x=x2-x1;
		v.y=y2-y1;
	}

};

Point Unit_Vector(Point A) { return A / Length(A); }
Point Unit_Normal_Vector(Point A) { return Point(-A.y, A.x) / Length(A); }
Line Line_Translation_Distance(Line l, int d)
{//直线平移距离d
	Vector vl = Unit_Normal_Vector(l.v);
	Point p1 = l.p + vl*d, p2 = l.p - vl*d;
	Line newline = Line(p1, l.v);
	return newline;
}
Point Get_Line_Intersection(Line a, Line b)
{//直线交点
	return Get_Line_Intersection(a.p, a.v, b.p, b.v);
}
bool On_Left(const Line& L, const Point& p)
{//判断点p是否在有向直线的左边
	return Cross(L.v, p - L.p) >= 0;
}


Point up[5005], low[5005],toy[5005];
Line par[5005];
int num[5005] = { 0 };

int main()
{
	int n, m, x1, y1, x2, y2;
	
	while (scanf("%d", &n)!=EOF)
	{
		if(n==0) break;
		scanf("%d%d%d%d%d", &m, &x1, &y1, &x2, &y2);
		for (int i = 0; i < n; i++)
		{
			up[i].y = y1;
			low[i].y = y2;
			scanf("%lf%lf", &up[i].x, &low[i].x);
		//	par[i]=Line(up[i], up[i] - low[i]);
		par[i]=Line(up[i].x,up[i].y,low[i].x,low[i].y);
		}
		for (int i = 0; i < m; i++)
		{
			scanf("%lf%lf", &toy[i].x, &toy[i].y);
		}
		for (int i = 0; i < m; i++)
		{
			int j = 0;
		//	while (On_Left(par[j], toy[i]) == 0)
		while(((up[j].x-low[j].x)*(toy[i].y-up[j].y)-(up[j].y-low[j].y)*(toy[i].x-up[j].x))<=0)
			{
				j++;
			}
			num[j]++;
		}
		for (int i = 0; i <= n; i++)
			printf("%d: %d\n", i,num[i]);
	}
	return 0;
}
