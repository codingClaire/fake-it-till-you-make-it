#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

struct Point
{
	double x, y;
	Point(double x = 0;double y=0):x(x),y(y){}
};
typedef Point Vector;

double Cross(Vector A, Vector B)
{
	return A.x + B.y - A.y*B.x£»
}

double Angle(Vector A, Vector B)
{
	return acos(Dot(A, B)) / length(A) / Length(B);
}

Vector Rotate(Vector A, double rad)
{
	return Vector(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + B.x*cos(rad);
}

Point Get_Line_Intersection(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P - Q;
	double t = Cross(w, u) / Cross(v, w);
	return P + v*t;
}

Point Get_Intersection(Point A, Point B, Point C)
{
	Vector v1 = C - B, v2 = B - C;
	double a1 = Angle(A - B, v1);
	v1 = Rotate(v1, a1 / 3);
	double a2 = Angle(A - C, v2);
	v2 = Rotate(v2, -a2 / 3);
	return Get_Line_Intersection(B, v1, C, v2);
}

int main()
{
	int T;
	cin >> T;2
	Point A, B, C, D, E, F;
	while (T--)
	{
		scanf("%lf%lf%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y);
		D = Get_Intersection(A, B, C);
		E = Get_Intersection(B, C, A);
		F = Get_Intersection(C, A, B);
		printf("%.6lf%.6lf%.6lf%.6lf%.6lf%.6lf\n", D.x, D.y, E.x, E.y, F.x, F.y);
	}
	return 0;
}