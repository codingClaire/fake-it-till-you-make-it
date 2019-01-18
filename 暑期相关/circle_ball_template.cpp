#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

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
	Vector v;
	double angle;
	Line(Point p, Vector v) :p(p), v(v)
	{
		angle= atan2(v.y, v.x);// double atan2(double y,double x) ���ص���ԭ������(x,y)�ķ�λ�ǣ����� x ��ļн�
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

//��λ����
Point Unit_Vector(Point A) { return A / Length(A); }
//��λ������
Point Unit_Normal_Vector(Point A) { return Point(-A.y, A.x) / Length(x); }



//ֱ��ƽ�ƾ���d
Line Line_Translation_Distance(Line l, int d)
{
	Vector vl = Unit_Normal_Vector(l.v);
	Point p1 = l.p + vl*d, p2 = l.p - vl*d;
	Line newline = Line(p1, l.v);
	return newline;
}
//ֱ�߽���
Point Get_Line_Intersection(Line a, Line b)
{
	return Get_Line_Intersection(a.p, a.v, b.p, b.v);
}
//�жϵ�p�Ƿ�������ֱ�ߵ����
bool On_Left(const Line& L, const Point& p)
{
	return Cross(L.v, p - L.p) >= 0;
}






//ֱ�ߺ�Բ�Ľ���
/*�������ؽ���ĸ���������sol��ŵ��ǽ��㱾�� û�����sol ���Է������ð����н������һ��sol��*/
int Get_Line_Circle_Intersection(Line L, Circle C, double& t1, double& t2, vector<Point>& sol)
{
	double a = L.v.x,
		b = L.p.x - C.c.x,
		c = L.v.y,
		d = L.p.y - C.c.y;
	double e = a*a + c*c,
		f = 2 * (a*b + c*d),
		g = b*b + d*d - C.r*C.r;
	double delta = f*f - 4 * e*g;//�б�ʽ��
	if (dcmp(delta) < 0) return 0;//����
	if (dcmp(delta) == 0)//����
	{
		t1 = t2 = -f / (2 * e);
		sol.push_back(L.Point(t1));
		return 1;
	}
	//�ཻ
	t1 = (-f - sqrt(delta)) / (2 * e);
	sol.push_back(L.Point(t1));
	t2 = (-f + sqrt(delta)) / (2 * e);
	sol.push_back(L.Point(t2));
		return 2;
}

//��Բ�ཻ
/*�������ļ���*/
double angle(Vector v) { return atan2(v.y, v.x); }

int	Get_Two_Circles_Intersection(Circle c1, Circle c2, vector<Point>& sol)
{
	double d = Length(c1.c - c2.c);
	if (dcmp(d) == 0)
	{
		if (dcmp(c1.r + c2.r - d) < 0) return 0;
		if (dcmp(fabs(c1.r - c2.r) - d) > 0) return 0;
		double a = angle(c2.c - c1.c);//c1c2�ļ���
		double da = acos((c1.r*c1.r + d*d - c2.r*c2.r) / (2 * c1.r*d));//c1c2��c1p1�Ľ�
		Point p1 = c1.point(a - da), p2 = c1.point(a + da);

		sol.push_back(p1);
		if (p1 == p2)
			return 1;
		sol.push_back(p2);
		return 2;
	}
}

//��������Բ������
	/*��p����ԲC�����ߣ�v[i]�ǵ�i�����ߵ�������������������*/
	int Get_Tangents(Point p, Circle C, Vector* v)
	{
		Vector u = C.c - p;
		double dist = Length(u);
		if (dist < C.r) return 0;//��p��Բ���ڲ�
		else if (dcmp(dist - C.r) == 0)//��p��Բ��
		{
			v[0] = Rotate(u, pi / 2);
			return 1;
		}
		else//��p��Բ��
		{
			double ang = asin(C.r / dist);
			v[0] = Rotate(u, -ang);
			v[1] = Rotate(u, +ang);
			return 2;
		}
	}

	//��Բ�Ĺ�����
	int Get_Tangents(Circle A, Circle B, Point* a, Point* b)
	{
		int cnt = 0;
		if (A.r < B.r)
		{
			swap(A, B);
			swap(a, b);
		}
		int d2 = (A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y);//Բ�ľ��ƽ��
		int rdiff = A.r - B.r;//�뾶��
		int rsum = A.r + B.r;//�뾶��
		if (d2 < rdiff*rdiff) return 0;  //��Բ�ں�

		double base = atan2(B.y - A.y, B.x - A.x);
		if (d2 == 0 && A.r == B.r)//��Բ�غ�
			return -1;
		if (d2 == rdiff*rdiff)//��Բ����
		{
			a[cnt] = A.getPoint(base);
			b[cnt] = B.getPoint(base);
			cnt++;
			return 1;
		}
		//���⹫����
		double ang = acos((A.r - B.r) / sqrt(d2));
		a[cnt] = A.getPoint(base + ang); b[cnt] = B.getPoint(base + ang); cnt++;
		a[cnt] = A.getPoint(base - ang); b[cnt] = B.getPoint(base - ang); cnt++;

		if (d2 == rsum*rsum)//��Բ���� һ���ڹ�����
		{
			a[cnt] = A.getPoint(base); b[cnt] = B.getPoint(PI + base); cnt++;
		}
		else if (d2 > rsum*rsum)//��Բ���� �����ڹ�����
		{
			double ang = acos((A.r - B.r) / sqrt(d2));
			a[cnt] = A.getPoint(base + ang); b[cnt] = B.getPoint(pi + base + ang); cnt++;
			a[cnt] = A.getPoint(base - ang); b[cnt] = B.getPoint(pi + base - ang); cnt++
		}
		return cnt;
	}











