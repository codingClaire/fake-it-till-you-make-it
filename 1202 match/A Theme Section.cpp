#include<iostream>
#include<cstring>

using namespace std;

int n;
char x[1000005];
int nex[1000005];

void kmp_pre()
{
	int i, j;
	j = nex[0] = -1;
	i = 0;
	while (x[i])
	{
		while (-1 != j&&x[i] != x[j])
			j = nex[j];
		nex[++i] = ++j;
	}
}

int kmp()
{
	kmp_pre();
	int len=strlen(x);
	int i=nex[len],j;

	for(j = i << 1; j <= len - i; ++j)
	{
		if(nex[j] == i) return i;
		else if(j==len-i) i=nex[i];
	}	
			
}
int main()
{
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", x);
		printf("%d\n", kmp());
	}
	return 0;
}
