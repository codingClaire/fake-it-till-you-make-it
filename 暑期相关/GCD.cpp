/*��������N����1<=x,y<=N��Gcd(x,y)Ϊ������
����(x,y)�ж��ٶ�.

Input
һ������N

Output
����*/
//TLE����....
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

int  GCD(int num1,int num2)
 {
 	if(num2==0)
 		return num1;
 	return GCD(num2,num1%num2);
 	
 }
 

bool is_Prime(int num)
{
	if (num == 1) return false;
	if (num == 2) return true;
	for (int i = 2; i < sqrt(num) + 1; i++)
	{
		if (num%i == 0)
		{
			return false;
		}
	}
	return true;
}


int main()
{
	int n, ans=0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (is_Prime(GCD(i, j)))
				ans++;
		}
	}
	printf("%d\n", ans);
}
