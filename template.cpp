#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;

struct Point
{
	double x, y;
	Point(double x = 0,double y=0):x(x),y(y){}
};

typedef Point Vector;
//向量加法
Vector operator+(Vector A, Vector B)
{
	return Vector(A.x + B.x, A.y + B.y);
}
//向量减法
Vector operator-(Vector A, Vector B)
{
	return Vector(A.x - B.x, A.y - B.y);
}
//向量数乘
Vector operator*(Vector A, double p)
{
	return Vector(A.x *p, A.y *p);
}
//向量数除
Vector operator/(Vector A, double p)
{
	return Vector(A.x /p, A.y /p);
}
//比较【a在b的左上角返回1】
bool operator <(const Point& a, const Point& b)
{
	return a.x < b.x || (a.x == b.x&&a.y < b.y);
}
//精度比较
const double eps = 1e-10;
int dcmp(double x)
{
	if (fabs(x) < eps) return 0;
	else return x < 0 ? -1 : 1;
}

bool operator ==(const Point &a, const Point &b)
{
	return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
//向量点积
double Dot(Vector A, Vector B)
{
	return A.x*B.x + A.y*B.y;
}
//向量长度
double Length(Vector A)
{
	return sqrt(Dot(A, A));
}
//夹角
double Angle(Vector A, Vector B)
{
	return acos(Dot(A, B) / Length(A) / Length(B));
}
//向量叉乘
double Cross(Vector A, Vector B)
{
	return A.x+B.y-A.y*B.x;
}
//向量围成的平行四边形面积
double paraArea(Point A, Point B, Point C)
{
	return Cross(B - A, C - A);
}
//向量的旋转
Vector Rotate(Vector A, double rad)
{
	return Vector(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.x*cos(rad));
}
//向量的单位法线 【A为非零向量】
Vector Normal(Vector A)
{
	double L = Length(A);
	return Vector(-A.y / L, A.x / L);
}
//直线的交点 【P+tv和Q+tw的交点 Cross(v,w)!=0且有唯一交点】
Point Get_Line_Intersection(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P - Q;
	double t = Cross(w, u) / Cross(v, w);
	return P + v*t;
}
//点到直线的距离
double Distance_To_Line(Point A, Point B, Point P)
{
	Vector v1 = B - A,v2 = P - A;
	return fabs(Cross(v1, v2) / Length(v1));
}
//点到线段的距离
double Distance_To_Segment(Point A, Point B, Point P)
{
	if (A == B)
		return Length(P - A); //A、B重合
	Vector v1 = B - A,v2 = P - A,v3 = P - B;
	if (dcmp(Dot(v1, v2)) < 0)
		return Length(v2);//A点在P、B之间
	else if (dcmp(Dot(v1, v3)) > 0)
		return Length(v3);//B点在P、A之间
	else
		return fabs(Cross(v1, v2)) / Length(v1);
}
//求点在直线上的投影点
Point Get_Line_Projection(Point P, Point A, Point B)
{
	Vector v = B - A;
	return A + v*(Dot(v, P - A) / Dot(v, v));
}
//相交线段判定
bool Segment_Proper_Intersection(Point a1, Point a2, Point b1, Point b2)
{
	double c1 = Cross(a2 - a1, b2 - b1),
		c2 = Cross(a2 - a1, b2 - b1),
		c3 = Cross(b2 - b1, a1 - b1),
		c4 = Cross(b2 - b1, a2 - b1);
	return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}
//判断点是否在线段上，不包含端点
bool On_Segment(Point P, Point A, Point B)
{
	return dcmp(Cross(A - P, B - P)) == 0 && dcmp(Dot(A - P, B - P)) < 0;
}
//多边形的有向面积
double PolygonArea(Point *p, int n)
{
	double area = 0;
	for (int i = 1; i < n - 1; i++)
	{
		area += Cross(p[i] - p[0], p[i + 1] - p[0]);
		return area / 2;
	}
}




