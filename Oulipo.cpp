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

void construct_next()//构造next数组
{
	int j = 0, k = -1;
	Next[0] = -1;
	while (j < lenp)//j小于模式串的长度
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
	int i, j = 0;//i,j相当于指向文本串和模式串的指针
	if (lenp == 1 && lent == 1)
	{
		if (pattern[0] == text[0])
			return 1;
		else return 0;
	}//都只有一个字符的情况
	construct_next();
	for (int i = 0; i < lent; i++)
	{
		while (j > 0 && text[i] != pattern[j])
			j = Next[j];//出现不匹配的情况
		if (pattern[j] == text[i])
			j++;
		if (j == lenp)
		{
			ans++;//累计成功匹配的个数
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
