
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

char a[105][105];
int dir[4][2] =
{
	{ 1,0 },
	{ -1,0 },
	{ 0,1 },
	{ 0,-1 }
};
int row, column, num;

bool In_Boundary(int r, int c)
{
	if (r < row&&r >= 0 && c < column&&c >= 0)
		return true;
	return false;
} 

/*�����������*/
void Depth_First_Search(int r, int c,char ch)
{
	a[r][c] = '?';//��������ֱ�Ӹ�ֵΪ?

	int rr, cc;
	for (int i = 0; i < 4; i++)
	{//�����ĸ�����
		int rr = r + dir[i][0];
		int cc = c + dir[i][1];
		if (In_Boundary(rr, cc) && a[rr][cc] == ch)//�ڷ�Χ�������ַ�
			Depth_First_Search(rr, cc,ch);//�ݹ�
	}
}


int main()
{
	int di, dj;
	while (scanf("%d%d", &row, &column) != EOF)
	{
		getchar();
		if (column == 0 && row == 0)
			break;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
				scanf("%c", &a[i][j]);
			getchar();
		}
		num = 0;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				if (a[i][j] != '?')
				{
					di = i;
					dj = j;
					Depth_First_Search(di, dj,a[i][j]);
					num++;
					/*for (int i = 0; i < row; i++)
					{
							for (int j = 0; j < column; j++)
								printf("%c", a[i][j]);
						printf("\n");
				   }
					printf("%d",num);*/
				}
			}
		}
		printf("%d\n", num);
	}
	return 0;
}
