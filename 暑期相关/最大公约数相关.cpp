#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>

int gcd(int num1,int num2)
{
	for(int i=2;i<min(num1,num2);i++)
	{
		if(num1%i==-&&num2%i==0)
			ans=i;
	}
	return ans;
}
//��ʽ�� gcd(a,b)=gcd(b,a-b)  (a>=b)�� 
//��������� 
int  GCD(int num1,int num2)
{
	if(num2==0)
		return num1;
	if(num1<num2) 
		swap(num1,num2);//��֤��ߵ��������ұߵ��� 
	return GCD(num2,num1-num2);
	
}

//��ʽ�� gcd(a,b)=gcd(b,a-k*b) ����k=0,1,2,3,4...��a>=k*b
//gcd(a,b)=gcd(b,a%b)
int G_C_D(int num1,int num2)
{
	if(num2==0)
		return num1;
	return G_C_D(num2,num1%num2); 
 } 
 
 //֮ǰ���ϻ���
 //ŷ������㷨 
 int main()
{
	int m,i;
	cin>>m;
	for(i=0;i<m;i++)
	{
		long int a,n;
		cin>>a>>n;
		int k=n%a;
		while(n!=0&&k!=0)
		{
		  if(n>k) 
		  {
		  	n=n%k;
		  	x=n/k;
		  }
		  else k=k%n;
		}
	}
return 0;
 } 
 
 //��չŷ�����
 /*F: ŷ������㷨
��RSA������ϵ��, ŷ������㷨�Ǽ��ܻ�����������Ҫ��ɲ��֡����Ļ���������̾��ǽ� x*a=1(mod n) ���ַ��̡�������Ĺ����������ģ�������һ��������˵����
��a = 1001 ��n = 3837ʱ
����Ϊ x * 1001 = 1 (mod 3837)
�����̣�
3837 = 3 * 1001 + 834
1001 = 1 * 834 + 167
834 = 4 * 167 + 166
167 = 166 + 1
����
1 = 167 �C 166
= 167 - (834 - 4 * 167)
= 5 * 167 �C 834
= 5 *(1001 - 834) �C 834
= 5 * 1001 - 6 *834
= 5 * 1001 - 6 * (3837 -3 *1001)
= 23 * 1001 - 6 *3837
Ȼ��Ե�ʽ����ͬʱ����ģ3837��
23 * 1001 = 1 (mod 3837)
���� x = 23
���ڸ���a��n�����ܲ�������̵�ʱ���ڽ����������أ�
 
����
 
�����������������ݡ�ÿ��������ݶ�Ӧ�����һ�У�ÿ�а�����������a��n��1<a,n<2^31(��long���Դ���)
��a=n=0ʱ����������������ݲ���������Ҫ����������С�

���

��Ӧÿ���������ݣ������С����������Ľ�x��

��������
 
1001 3837
136468984 134548555
0 0
 
�������
 
23
112206854
 
��ʾ
 
1. ����������ǲ�������������
2. �������������*/

int extgcd(long a, long b,int &x, int &y)
{
    int d = a;
    if(b != 0)
	{
        d = extgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
    else x=1,y=0;
    return d;
}

int main()
{
	
	long int a,n;
	
	while(1)
	{
	    cin>>a>>n;
		if(a==0&&n==0)
		  break;
		 int x1,y1;  
         extgcd(a,n,x1,y1);
         if(x1<0)
     	 	 x1=x1+n;
		  cout<<x1<<endl;
	}
return 0;
}
 
   
 
