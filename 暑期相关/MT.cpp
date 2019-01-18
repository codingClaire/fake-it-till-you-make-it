#include<cstdio>
#include<cmath>
 
struct Point
{
	double x, y;
	Point(double x = 0,double y=0):x(x),y(y){}
};
typedef Point Vector;
Vector operator +(Point a,Point b)
{
	return Vector(a.x+b.x,a.y+b.y);
}
Vector operator *(Point a,double b)
{
	return Vector(a.x*b,a.y*b);
}
Vector operator -(Point a,Point b)
{
	return Vector(a.x-b.x,a.y-b.y);
}
 
double Dot(Vector a,Vector b)
{
	return a.x*b.x+a.y*b.y;
}
double Cross(Vector a,Vector b)
{
	return a.x*b.y-a.y*b.x;
}
double Length(Vector a)
{
	return sqrt(a.x*a.x+a.y*a.y);
}
Vector Rotate(Vector a,double rad)
{
	return Vector(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));
}
Point Get_Line_Intersection(Point p,Vector v,Point q,Vector w){
	Vector u= p-q;
	double t=Cross(w,u) / Cross(v,w);
	return p+v*t;
}
double Angle(Vector A, Vector B)
{
	return acos(Dot(A, B) / Length(A) / Length(B));
}
Point Get_Intersection(Point A,Point B,Point C)
{
	Vector BC=C-B;
	Vector BA=A-B;
	//double x=acos(Dot(BA,BC) / Length(BC) / Length(BA));
	double x=Angle(BA,BC);
	Vector BD= Rotate(BC,x/3);
 
	Vector CA=A-C;
	Vector CB=B-C;
	//x=acos(Dot(CB,CA) / Length(CB) / Length(CA) );
	x=Angle(CB,CA);
	Vector CD=Rotate(CB,-x/3);
 
	return Get_Line_Intersection(B,BD,C,CD);
}
int main()
{
	int T;
	scanf("%d",&T);
	Point a,b,c,d,e,f;
	while(T--)
	{		
		scanf("%lf%lf",&a.x,&a.y);
		scanf("%lf%lf",&b.x,&b.y);
		scanf("%lf%lf",&c.x,&c.y);
		d=Get_Intersection(a,b,c);
		e=Get_Intersection(b,c,a);
		f=Get_Intersection(c,a,b);
		printf("%.6lf %.6lf %.6lf %.6lf %.6lf %.6lf\n",d.x,d.y,e.x,e.y,f.x,f.y);
	}
	return 0;
}
