#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

bool is_Prime(int num)
{
	if(num==1) return false;
	if(num==2) return true;
	for (int i = 2; i < sqrt(num)+1; i++)
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
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		int num;
		scanf("%d", &num);
		if (is_Prime(num))
			printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
