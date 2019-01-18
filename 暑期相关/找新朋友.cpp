#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;
//欧拉公式的应用
int oulafunction(int num)
{
	int ret = num;
	for (int i = 2; i <=num ; i++)
		if (num%i == 0)
		{
			//ret = ret*(1 - 1 / i);
			ret=ret-ret/i;
			do
				num =num/ i;
			while (num%i == 0);
		}
	//	if (num > 1)
	//		ret= ret*(1 - 1 / num);
		return ret;
}

int main()
{
	int cn;
	scanf("%d", &cn);
	while (cn--)
	{
		int n;
		scanf("%d", &n);
		cout << oulafunction(n) << endl;
	}
	return 0;
}
