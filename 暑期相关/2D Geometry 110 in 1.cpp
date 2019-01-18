#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const double eps = 1e-10;
const double pi = acos(-1.0);

struct Point
{
	double x, y;
	Point(double x = 0, double y = 0) :x(x), y(y) {}
};
typedef Point Vector1;

Vector1 operator+(Vector1 A, Vector1 B){return Vector1(A.x + B.x, A.y + B.y);}
Vector1 operator-(Vector1 A, Vector1 B) { return Vector1(A.x - B.x, A.y - B.y); }
Vector1 operator*(Vector1 A, double p){ return Vector1(A.x *p, A.y *p);}
Vector1 operator/(Vector1 A, double p){ return Vector1(A.x / p, A.y / p);}
bool operator <(const Point& a, const Point& b)
{
	return a.x < b.x || (a.x == b.x&&a.y < b.y);
}

int dcmp(double x)
{
	if (fabs(x) < eps) return 0;
	else return x < 0 ? -1 : 1;
}
bool operator==(const Point&a,const Point&b){return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;}
double Dot(Vector1 A, Vector1 B){return A.x*B.x + A.y*B.y;}
double Length(Vector1 A){return sqrt(Dot(A, A));}
double Angle(Vector1 A, Vector1 B){return acos(Dot(A, B) / Length(A) / Length(B));}
double Cross(Vector1 A, Vector1 B){return A.x * B.y - A.y*B.x;}
Vector1 Rotate(Vector1 A, double rad)
{
	return Vector1(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.y*cos(rad));
}
Vector1 Normal(Vector1 A)
{
	double L = Length(A);
	return Vector1(-A.y / L, A.x / L);
}
Point Get_Line_Intersection(Point P, Vector1 v, Point Q, Vector1 w)
{//直线的交点 【P+tv和Q+tw的交点 Cross(v,w)!=0且有唯一交点】
	Vector1 u = P - Q;
	double t = Cross(w, u) / Cross(v, w);
	return P + v*t;
}
double Distance_To_Line(Point A, Point B, Point P)
{//点到直线的距离
	Vector1 v1 = B - A, v2 = P - A;
	return fabs(Cross(v1, v2) / Length(v1));
}
double Distance_To_Segment(Point A, Point B, Point P)
{//点到线段的距离
	if (A == B)
		return Length(P - A); //A、B重合
	Vector1 v1 = B - A, v2 = P - A, v3 = P - B;
	if (dcmp(Dot(v1, v2)) < 0)
		return Length(v2);//A点在P、B之间
	else if (dcmp(Dot(v1, v3)) > 0)
		return Length(v3);//B点在P、A之间
	else
		return fabs(Cross(v1, v2)) / Length(v1);
}
Point Get_Line_Projection(Point P, Point A, Point B)
{//求点在直线上的投影点
	Vector1 v = B - A;
	return A + v*(Dot(v, P - A) / Dot(v, v));
}
bool Segment_Proper_Intersection(Point a1, Point a2, Point b1, Point b2)
{//相交线段判定
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

struct Circle
{
	Point c;
	double r;
	Circle(Point c, double r) :c(c), r(r) {}
	Point point(double a)
	{
		return Point(c.x + cos(a)*r, c.y + sin(a)*r);
	}
};

struct Line
{
	Point p;
	Vector1 v;
	double angle;
	Line(Point p, Vector1 v) :p(p), v(v)
	{
		angle = atan2(v.y, v.x);// double atan2(double y,double x) 返回的是原点至点(x,y)的方位角，即与 x 轴的夹角
	}
	Point point(double a)
	{
		return p + (v*a);
	}
	bool operator<(const Line& L)const
	{
		return angle < L.angle;
	}
};

//单位向量
Point Unit_Vector(Point A) { return A / Length(A); }
//单位法向量
Point Unit_Normal_Vector(Point A) { return Point(-A.y, A.x) / Length(A); }

Line Line_Translation_Distance(Line l, int d)
{//直线平移距离d
	Vector1 vl = Unit_Normal_Vector(l.v);
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

int Get_Line_Circle_Intersection(Line L, Circle C, double& t1, double& t2, vector<Point>& sol)
{//直线和圆的交点
/*函数返回交点的个数，参数sol存放的是交点本身 没有清空sol 可以反复调用把所有交点放在一个sol中*/
	double a = L.v.x,
		b = L.p.x - C.c.x,
		c = L.v.y,
		d = L.p.y - C.c.y;
	double e = a*a + c*c,
		f = 2 * (a*b + c*d),
		g = b*b + d*d - C.r*C.r;
	double delta = f*f - 4. * e*g;//判别式法
	if (dcmp(delta) < 0) return 0;//相离
	if (dcmp(delta) == 0)//相切
	{
		t1 = t2 = -f / (2 * e);
		sol.push_back(L.point(t1));
		return 1;
	}
	//相交
	t1 = (-f - sqrt(delta)) / (2 * e);
	sol.push_back(L.point(t1));
	t2 = (-f + sqrt(delta)) / (2 * e);
	sol.push_back(L.point(t2));
	return 2;
}
double angle(Vector1 v) 
{ /*求向量的极角*/return atan2(v.y, v.x); }
int	Get_Two_Circles_Intersection(Circle c1, Circle c2, vector<Point>& sol)
{//两圆相交
	double d = Length(c1.c - c2.c);
	if (dcmp(d) == 0)
	{
		if(dcmp(c1.r-c2.r)==0) return -1;
		return 0;
	}
		if (dcmp(c1.r + c2.r - d) < 0) return 0;
		if (dcmp(fabs(c1.r - c2.r) - d) > 0) return 0;
		double a = angle(c2.c - c1.c);//c1c2的极角
		double da = acos((c1.r*c1.r + d*d - c2.r*c2.r) / (2 * c1.r*d));//c1c2到c1p1的角
		Point p1 = c1.point(a - da), p2 = c1.point(a + da);

		sol.push_back(p1);
		if (p1 == p2)
			return 1;
		sol.push_back(p2);
		return 2;
}
int Get_Tangents(Point p, Circle C, Vector1* v)
{//过定点做圆的切线
/*过p作到圆C的切线，v[i]是第i条切线的向量，返回切线条数*/
	Vector1 u = C.c - p;
	double dist = Length(u);
	if (dist < C.r) return 0;//点p在圆的内部
	else if (dcmp(dist - C.r) == 0)//点p在圆上
	{
		v[0] = Rotate(u, pi / 2);
		return 1;
	}
	else//点p在圆外
	{
		double ang = asin(C.r / dist);
		v[0] = Rotate(u, -ang);
		v[1] = Rotate(u, +ang);
		return 2;
	}
}
int Get_Tangents(Circle A, Circle B, Point* a, Point* b)
{//两圆的公切线
	int cnt = 0;
	if (A.r < B.r)
	{
		swap(A, B);
		swap(a, b);
	}
	int d2 = (A.c.x - B.c.x)*(A.c.x - B.c.x) + (A.c.y - B.c.y)*(A.c.y - B.c.y);//圆心距的平方
	int rdiff = A.r - B.r;//半径差
	int rsum = A.r + B.r;//半径和
	if (d2 < rdiff*rdiff) return 0;  //两圆内含

	double base = atan2(B.c.y - A.c.y, B.c.x - A.c.x);
	if (d2 == 0 && A.r == B.r)//两圆重合
		return -1;
	if (d2 == rdiff*rdiff)//两圆内切
	{
		a[cnt] = A.point(base);
		b[cnt] = B.point(base);
		cnt++;
		return 1;
	}
	//有外公切线
	double ang = acos((A.r - B.r) / sqrt(d2));
	a[cnt] = A.point(base + ang); b[cnt] = B.point(base + ang); cnt++;
	a[cnt] = A.point(base - ang); b[cnt] = B.point(base - ang); cnt++;

	if (d2 == rsum*rsum)//两圆外切 一条内公切线
	{
		a[cnt] = A.point(base); b[cnt] = B.point(pi + base); cnt++;
	}
	else if (d2 > rsum*rsum)//两圆内切 两条内公切线
	{
		double ang = acos((A.r - B.r) / sqrt(d2));
		a[cnt] = A.point(base + ang); b[cnt] = B.point(pi + base + ang); cnt++;
		a[cnt] = A.point(base - ang); b[cnt] = B.point(pi + base - ang); cnt++;
	}
	return cnt;
}

//已知三点求外接圆 求圆心思路见笔记本【联立方程式 克拉默法则 各种化简 当黑盒子用也可
Circle CircumscribedCircle(Point p1, Point p2, Point p3)
{
	double Bx = p2.x - p1.x,
		By = p2.y - p1.y,
		Cx = p3.x - p1.x,
		Cy = p3.y - p1.y;
	double D = 2 * (Bx*Cy - By*Cx);
	double cx = (Cy*(Bx*Bx + By*By) - By*(Cx*Cx + Cy*Cy)) / D + p1.x;
	double cy = (Bx*(Cx*Cx + Cy*Cy) - Cx*(Bx*Bx + By*By)) / D + p1.y;
	Point p = Point(cx, cy);
	return Circle(p, Length(p1 - p));
}

//已知三点求内切圆
Circle InscribedCircle(Point p1, Point p2, Point p3)
{
	double a = Length(p2 - p3);
	double b = Length(p3 - p1);
	double c = Length(p1 - p2);
	Point p = (p1*a + p2*b + p3*c) / (a + b + c);
	return Circle(p, Distance_To_Line(p1, p2, p));
}

double RtoDegree(double x)
{
	return x / pi*180.;
}

char op[200];
double num[10];
Vector1 v[10];
double degree[10];
vector<Point> sol;

int main()
{
	while (scanf("%s", op) != EOF)
	{
		if (strcmp(op, "CircumscribedCircle") == 0)
		{
			for (int i = 0; i < 6; i++)
				scanf("%lf", &num[i]);
			Circle C = CircumscribedCircle(Point(num[0], num[1]), Point(num[2], num[3]), Point(num[4], num[5]));
			printf("(%.6lf,%.6lf,%.6lf)\n", C.c.x, C.c.y, C.r);
		}
		else if (strcmp(op, "InscribedCircle") == 0)
		{
			for (int i = 0; i < 6; i++)
				scanf("%lf", &num[i]);
			Circle C = InscribedCircle(Point(num[0], num[1]), Point(num[2], num[3]), Point(num[4], num[5]));
			printf("(%.6lf,%.6lf,%.6lf)\n", C.c.x, C.c.y, C.r);
		}
		else if (strcmp(op, "TangentLineThroughPoint") == 0)
		{
			for (int i = 0; i < 5; i++)
				scanf("%lf", &num[i]);
			int linenum = Get_Tangents(Point(num[3], num[4]), Circle(Point(num[0], num[1]), num[2]), v);
				for (int i = 0; i < linenum; i++)
				{
					double de = RtoDegree(angle(v[i]));//转换成角度制表示
					if (dcmp(de) < 0) de += 180.;
					else while (dcmp(de - 180.) >= 0)
						de -= 180.;
					degree[i] = de;
				}
			sort(degree, degree + linenum);
			putchar('[');
			if (linenum == 0) putchar(']');
			for (int i = 0; i < linenum; i++)
				printf("%.6lf%c", degree[i], (i != linenum - 1) ? ',' : ']');//机智
			putchar(10);//换行
		}
		else if (strcmp(op, "CircleThroughAPointAndTangentToALineWithRadius") == 0)
		{
			for (int i = 0; i < 7; i++)
				scanf("%lf", &num[i]);
			Point A = Point(num[2], num[3]), B = Point(num[4], num[5]);
			Circle C(Point(num[0], num[1]), num[6]);

			Point normal = Unit_Normal_Vector(B - A);
			normal = normal / Length(normal)*num[6];
			
			Point ta = A + normal, tb = B + normal;
			Line l1 = Line(ta, tb - ta);
			ta = A - normal, tb = B - normal;
			Line l2 = Line(ta, tb - ta);

			sol.clear();
			double t1, t2;
			int pointnum1 = Get_Line_Circle_Intersection(l1, C, t1, t2, sol);
			int	pointnum2 = Get_Line_Circle_Intersection(l2, C, t1, t2, sol);
			
			sort(sol.begin(), sol.end());
			putchar('[');
			for (int i = 0, pointnum = sol.size(); i < pointnum; i++)
			{
				if (i) putchar(',');
				printf("(%.6lf,%.6lf)", sol[i].x, sol[i].y);
			}
			putchar(']');
			putchar(10);

		}
		
		
		else if (strcmp(op, "CircleTangentToTwoLinesWithRadius") == 0)
		{
			for (int i = 0; i < 9; i++)
				scanf("%lf", &num[i]);
			Line l1 = Line(Point(num[0], num[1]), Point(num[2], num[3]) - Point(num[0], num[1]));
			Line l2 = Line(Point(num[4], num[5]), Point(num[6], num[7]) - Point(num[4], num[5]));
			Line l11 = Line_Translation_Distance(l1, num[8]),
				l12 = Line_Translation_Distance(l1, -num[8]),
				l21 = Line_Translation_Distance(l2, num[8]),
				l22 = Line_Translation_Distance(l2, -num[8]);

			sol.clear();
			sol.push_back(Get_Line_Intersection(l11, l21));
			sol.push_back(Get_Line_Intersection(l11, l22));
			sol.push_back(Get_Line_Intersection(l12, l21));
			sol.push_back(Get_Line_Intersection(l12, l22));
			sort(sol.begin(), sol.end());

			putchar('[');
			for (int i = 0, linenum = sol.size(); i < linenum; i++)
			{
				if (i) putchar(',');
				printf("(%.6lf,%.6lf)", sol[i].x,sol[i].y);
			}
			putchar(']');
			putchar(10);
		}
		else if (strcmp(op, "CircleTangentToTwoDisjointCirclesWithRadius") == 0)
		{
			for (int i = 0; i < 7; i++)
				scanf("%lf", &num[i]);
			Circle c1 = Circle(Point(num[0], num[1]), num[2] + num[6]);
			Circle c2 = Circle(Point(num[3], num[4]),num[5] + num[6]);
			sol.clear();
			Get_Two_Circles_Intersection(c1, c2, sol);
			sort(sol.begin(), sol.end());
			putchar('[');
			for (int i = 0, pointnum = sol.size(); i < pointnum; i++)
			{
				if (i) putchar(',');
				printf("(%.6lf,%.6lf)", sol[i].x, sol[i].y);
			}
			putchar(']');
			putchar(10);
		}
	}
	return 0;
}

