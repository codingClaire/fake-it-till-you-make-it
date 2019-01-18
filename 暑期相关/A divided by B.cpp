#include<iostream>
#include<cstdio> 
using namespace std;

int T;

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		long long n, B;
		cin>>n>>B;
		for (int q = 0; q < 9973; q++)
		{
			if ((B*q - n) % 9973 == 0)
			{
				printf("%d\n", q);
				break;
			}
		}
	}
	return 0;
}
