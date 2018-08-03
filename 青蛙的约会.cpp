//��չŷ������㷨����֪a, b�����һ��x��y��ʹ�������� ax + by = gcd(a, b)
#include<iostream>
#include<cstdio>
using namespace std;


long long extended_gcd(long long int a,long long int b, long long int &x, long long int &y)
{
	if (b == 0)
	{
		x = 1; 
		y = 0;
		return a;
	}
	int gcd = extended_gcd(b, a%b, x, y);
	int x2 = x,y2 = y;
	x = y2;
	y = x2 - (a / b)*y2;
	return gcd;
}

long long int extgcd(long long a, long long b, long long &x, long long &y)
{
	int d = a;
	if (b != 0)
	{
		d = extgcd(b, a%b, y, x);
		y -= (a / b)*x;
	}
	else x = 1, y = 0;
	return d;
}

//���ܵ�Լ�� ��ϵʽ�� step*(m-n)+x-y=kL L��Բ�ܳ� k�������Ȧ��
		//x��y��m��n��֪
  //(n-m)*step+kL=x-y ����Ԫһ�η��� ����ʹ����չŷ������㷨


int main()
{
	long long x, y, m, n, L,A,B,C, gcd;
	while (cin>>x>>y>>m>>n>>L)
	{
		A = n - m;
		B = L;
		C = x - y;
		gcd = extended_gcd(A,B, x, y);
		if (C%gcd != 0)
			printf("Impossible\n");
		else
		{
			C = C / gcd;
			x *=C;
			x = (x%B + B) % B;
			printf("%d\n", x);
		}
	}
return 0;

}
