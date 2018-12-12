#include<iostream>
using namespace std;
int main()
{
	int tol = 0;
	for (int s = 3; s <= 10; s++)
	{
		char first = 'a' + tol % 26;
		char endding = first+2*(s-1);
		for (int i = 0; i < s; i++)
		{
			if (first+i>'z') first=(first-'z')%26+'a'-1;
			printf("%c", first+i);
			for (int j = 1; j < s - i-1; j++)
				printf(" ");
			if(i<s-1) 
			{
				char mid=first+i + 2*(s - i - 1);
				if (mid>'z') mid=(mid-'z')%26+'a'-1;
				printf("%c", mid);
				//printf(" ");
			}
			for (int j = s - i; j < s - 1; j++)
				printf(" ");	
			if(i>0)
			{
				if(endding>='z') 
				endding=(endding-'z')%26+'a'-1;
				printf("%c",endding+i);
			}
			printf("\n");
		}
		tol += 3 * s - 2;
	}
	
return 0;		
}
