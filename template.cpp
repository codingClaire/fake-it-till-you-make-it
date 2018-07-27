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
//�����ӷ�
Vector operator+(Vector A, Vector B)
{
	return Vector(A.x + B.x, A.y + B.y);
}
//��������
Vector operator-(Vector A, Vector B)
{
	return Vector(A.x - B.x, A.y - B.y);
}
//��������
Vector operator*(Vector A, double p)
{
	return Vector(A.x *p, A.y *p);
}
//��������
Vector operator/(Vector A, double p)
{
	return Vector(A.x /p, A.y /p);
}
//�Ƚϡ�a��b�����ϽǷ���1��
bool operator <(const Point& a, const Point& b)
{
	return a.x < b.x || (a.x == b.x&&a.y < b.y);
}
//���ȱȽ�
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
//�������
double Dot(Vector A, Vector B)
{
	return A.x*B.x + A.y*B.y;
}
//��������
double Length(Vector A)
{
	return sqrt(Dot(A, A));
}
//�н�
double Angle(Vector A, Vector B)
{
	return acos(Dot(A, B) / Length(A) / Length(B));
}
//�������
double Cross(Vector A, Vector B)
{
	return A.x+B.y-A.y*B.x;
}
//����Χ�ɵ�ƽ���ı������
double paraArea(Point A, Point B, Point C)
{
	return Cross(B - A, C - A);
}
//��������ת
Vector Rotate(Vector A, double rad)
{
	return Vector(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.x*cos(rad));
}
//�����ĵ�λ���� ��AΪ����������
Vector Normal(Vector A)
{
	double L = Length(A);
	return Vector(-A.y / L, A.x / L);
}
//ֱ�ߵĽ��� ��P+tv��Q+tw�Ľ��� Cross(v,w)!=0����Ψһ���㡿
Point Get_Line_Intersection(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P - Q;
	double t = Cross(w, u) / Cross(v, w);
	return P + v*t;
}
//�㵽ֱ�ߵľ���
double Distance_To_Line(Point A, Point B, Point P)
{
	Vector v1 = B - A,v2 = P - A;
	return fabs(Cross(v1, v2) / Length(v1));
}
//�㵽�߶εľ���
double Distance_To_Segment(Point A, Point B, Point P)
{
	if (A == B)
		return Length(P - A); //A��B�غ�
	Vector v1 = B - A,v2 = P - A,v3 = P - B;
	if (dcmp(Dot(v1, v2)) < 0)
		return Length(v2);//A����P��B֮��
	else if (dcmp(Dot(v1, v3)) > 0)
		return Length(v3);//B����P��A֮��
	else
		return fabs(Cross(v1, v2)) / Length(v1);
}
//�����ֱ���ϵ�ͶӰ��
Point Get_Line_Projection(Point P, Point A, Point B)
{
	Vector v = B - A;
	return A + v*(Dot(v, P - A) / Dot(v, v));
}
//�ཻ�߶��ж�
bool Segment_Proper_Intersection(Point a1, Point a2, Point b1, Point b2)
{
	double c1 = Cross(a2 - a1, b2 - b1),
		c2 = Cross(a2 - a1, b2 - b1),
		c3 = Cross(b2 - b1, a1 - b1),
		c4 = Cross(b2 - b1, a2 - b1);
	return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}
//�жϵ��Ƿ����߶��ϣ��������˵�
bool On_Segment(Point P, Point A, Point B)
{
	return dcmp(Cross(A - P, B - P)) == 0 && dcmp(Dot(A - P, B - P)) < 0;
}
//����ε��������
double PolygonArea(Point *p, int n)
{
	double area = 0;
	for (int i = 1; i < n - 1; i++)
	{
		area += Cross(p[i] - p[0], p[i + 1] - p[0]);
		return area / 2;
	}
}




