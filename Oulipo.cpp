#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;


const int maxp = 10000 + 10;
const int maxt = 1000000 + 10;
int cas;
char text[maxt], pattern[maxp];
int Next[maxt];
int lenp,lent; 

void construct_next()//����next����
{
	int j = 0, k = -1;
	Next[0] = -1;
	while (j < lenp)//jС��ģʽ���ĳ���
	{
		if (k == -1 || pattern[j] == pattern[k])
			Next[++j] = ++k;
		else
			k = Next[k];
	}
}

int kmp()
{
	int ans = 0;
	int i, j = 0;//i,j�൱��ָ���ı�����ģʽ����ָ��
	if (lenp == 1 && lent == 1)
	{
		if (pattern[0] == text[0])
			return 1;
		else return 0;
	}//��ֻ��һ���ַ������
	construct_next();
	for (int i = 0; i < lent; i++)
	{
		while (j > 0 && text[i] != pattern[j])
			j = Next[j];//���ֲ�ƥ������
		if (pattern[j] == text[i])
			j++;
		if (j == lenp)
		{
			ans++;//�ۼƳɹ�ƥ��ĸ���
			j = Next[j];
		}
	}
	return ans;
}

int main()
{
	cin>>cas;
	while (cas--)
	{
		cin>>pattern>>text;
		lenp = strlen(pattern);
		lent = strlen(text);
		printf("%d\n", kmp());
	}
	return 0;
}
