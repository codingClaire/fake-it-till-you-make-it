
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
	}//����
	 
	for (int j = c - 2; j >= 0; j--) 
	{
		for (int i = 0; i < r; i++)
		{
			int *p = &aMatrix[j + 1][0];//С���� ��ʱָ����� 
			int nMin = (i - 1 + r) % r, d = (i + 1) % r;
			if (p[i] < p[nMin] || (p[i] == p[nMin] && i < nMin))//�ҷ�һ�� 
				nMin = i;
			if (p[d] < p[nMin] || (p[d] == p[nMin] && d < nMin))//���·�һ�� 
				nMin = d;
				//��ǰһ�е�ֵ Ϊ��ĩһ�е���ǰ�е���Сֵ 
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
