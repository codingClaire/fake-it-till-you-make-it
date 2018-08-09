#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxl=1000000+10; 
int len;
char pattern[maxl];
int Next[maxl];



void construct_next()//构造next数组
{
	int j = 0, k = -1;
	Next[0] = -1;
	while (j < len)//j小于模式串的长度
	{
		if (k == -1 || pattern[j] == pattern[k])
			Next[++j] = ++k;
		else
			k = Next[k];
	}
}

int main()
{
	int cas = 1;
	while (scanf("%d", &len) != EOF&&len)
	{
		scanf("%s", &pattern);
		construct_next();
		printf("Test case #%d\n", cas++);

		for (int i = 2; i <= len; i++)
			if ((i % (i - Next[i]) == 0) && (Next[i] != 0))
				printf("%d %d\n", i, i / (i - Next[i]));

		printf("\n");
	}
	return 0;
}
