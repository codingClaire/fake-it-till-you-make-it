
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;

int num[15],leftball[15],rightball[15];
int flag;
void DFS(int now, int l, int r)//now��ǰ������� l left r right 
{
	if (now > 10)
	{
		flag = 1;
		return;
	}//������һ����Ҳ�ܷŽ�ȥ ��˵�������YES����� 
	else if (flag)
		return;
		
		if (num[now] >leftball[l - 1])
		{
			leftball[l] = num[now];//����leftball 
			DFS(now + 1, l+1, r);//�ݹ� 
		}
	  if (num[now] > rightball[r - 1])
	    {
		  rightball[r] = num[now];//����rightball ��ݹ����һ�αȽ� 
		  DFS(now + 1, l, r + 1);
		}
}


int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		
		for (int i = 1; i <=10; i++)
		{
			scanf("%d",&num[i]);
		}
		flag = 0;
		DFS(1, 1, 1);
		if (flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
