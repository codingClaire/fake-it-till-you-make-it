
#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	int aMatrix[100][10], aPre[100][10];
	int r, c;
	while(scanf("%d%d", &r, &c)!=EOF && r&&c)
	{
	
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
			scanf("%d", &aMatrix[j][i]);
	}//输入
	 
	for (int j = c - 2; j >= 0; j--) 
	{
		for (int i = 0; i < r; i++)
		{
			int *p = &aMatrix[j + 1][0];//小技巧 临时指针变量 
			int nMin = (i - 1 + r) % r, d = (i + 1) % r;
			if (p[i] < p[nMin] || (p[i] == p[nMin] && i < nMin))//右方一格 
				nMin = i;
			if (p[d] < p[nMin] || (p[d] == p[nMin] && d < nMin))//右下方一格 
				nMin = d;
				//当前一列的值 为最末一列到当前列的最小值 
			aMatrix[j][i] += p[nMin];
			aPre[j][i] = nMin;
		}
	}
	int nMin = min_element(&aMatrix[0][0], &aMatrix[0][r]) - &aMatrix[0][0];
	int nWeight = aMatrix[0][nMin];
	printf("%d",nMin + 1);
	for (int j = 1; j < c; j++)
	{
		nMin = aPre[j - 1][nMin];
		printf(" %d", nMin + 1);
	}
	printf("\n");
	printf("%d\n", nWeight);
	}
}
