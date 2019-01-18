#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int square[25][25];
const int dir[4][2] = {
	{ 0, -1 },
	{ 1,0 },
	{ 0, 1 },
	{ -1 ,0 },
};
int row, column;
int minstep;
int di,dj; 


void DFS(const int& r, const int& c, int step)
{
	if (step >= 10 || step > minstep) return;
	for (int i = 0; i < 4; i++)
	{
		int rr = r, cc = c;
		while (rr >= 0 && cc >= 0 && rr < row&&cc < column)
		{
			switch (square[rr][cc])
			{
			case 0://�ո� ����������
			{
				rr += dir[i][0];
				cc += dir[i][1];
				break;
			}
			case 3://�����յ���
			{
				if (step + 1 < minstep)//���step���ϵ�ǰ�����֮ǰ��С�Ĳ�����С�����丳ֵ����С����
					minstep = step + 1;
				rr = -1;//????
				break;
			}
			case 1://����ʯͷ��
			{
				if (!(rr - dir[i][1] == r&&cc - dir[i][0] == c))//?????
				{
					square[rr][cc] = 0;//ʯͷ��ո� �ٵ���DFS����
					DFS(rr - dir[i][1], cc - dir[i][0], step + 1);//�򵽲��˷�ʯͷ�ĵط���ֻ������ԭ���ķ�������һ��
					square[rr][cc]=1; 
				}
				rr=-1;
				break;
			}
			default: {
				break;
			}
			}
		}
	}
}

int main()
{
	while (scanf("%d%d", &column, &row) != EOF)
	{
		if (column == 0 && row == 0)
			break;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				scanf("%d", &square[i][j]);
				if (square[i][j] == 2)
				{
					di = i;
					dj = j;//where the stone begins
				}
			}
		}
		square[di][dj] = 0;//��ʱ�ѽ��õ�����Ϊ�� 
		minstep=11;
		DFS(di, dj, 0);
	
		if (minstep > 10) minstep = -1;
		cout << minstep << endl;
	}
	return 0;
}
