#include<iostream>
#include<cstdio>
#define maxn 10000+5

using namespace std;
int S[maxn];
int left, right;
int n;

void MaxSubsequenceSum(const int A[], int n)
{
	int i;
	S[0] = A[0];
	for (i = 1; i < n; i++)//�洢�����������е�����  
	{
		if (S[i - 1] <=0) 
			S[i] = A[i];//���¿�ʼ
		else	
			S[i] = S[i - 1] + A[i];

	}
	for (right = i = 0; i < n; i++)
	{
		if (S[i] > S[right])
			right = i;//�ұ߽�
	}
	for (i = right; i >= 0; i--) 
	{
		if (S[i] < 0)
			break;
	}
	left = i + 1;//��߽�

	if (S[right] < 0)//ȫ��Ԫ�ض��Ǹ���
	{
		left = 0;
		right = n - 1;
		S[right] = 0;
	}
}

int main()
{
	while (scanf("%d", &n) != -1&&n)
	{
		int a[n];
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &a[j]);
		}
		MaxSubsequenceSum(a, n);
		printf("%d %d %d",S[right], a[left], a[right]);
	}
}