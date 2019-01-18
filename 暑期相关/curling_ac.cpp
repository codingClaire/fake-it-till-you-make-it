#include<iostream>
#include<cstdio>

using namespace std;


int column,row;
int square[25][25];
int dir[4][2]={{0,-1},{1,0},{0,1},{-1,0}};
int minstep;
int di,dj;

void DFS(const int& r,const int& c,int step)
{
	if(step>minstep||step>=10)
	{return;
		}	
	for(int i=0;i<4;i++)
	{
		int rr=r,cc=c;
		while(rr>=0&&rr<row&&cc>=0&&cc<column)
		{
			switch(square[rr][cc])
			{
				case 0:
					{
						rr+=dir[i][1];
						cc+=dir[i][0];
						break;
					}
				case 1:
					{
						if(!(rr-dir[i][1]==r&&cc-dir[i][0]==c))
						{
							square[rr][cc]=0;
							DFS(rr-dir[i][1],cc-dir[i][0],step+1);
							square[rr][cc]=1;
						}
						rr=-1;
						break;
					}
				
				case 3:
					{
						if(step+1<minstep)
						   minstep=step+1;
						rr=-1;
						break;
					}
				default:
					break;
			}
		}
	}
}




int main()
{
	while(scanf("%d%d",&column,&row)!=EOF)
	{
		if(column==0&&row==0)
			break;
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<column;j++)
			{
				scanf("%d",&square[i][j]);
				if(square[i][j]==2)//Æğµã 
				{
					di=i;
					dj=j;
				}
			}
		}
		square[di][dj]=0;
		minstep=11;
		DFS(di,dj,0);
		if(minstep>10)
			minstep=-1;
			
			cout<<minstep<<endl;
	}
	
	
	return 0;
	
}
