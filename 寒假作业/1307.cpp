#include<iostream>
#include<string>
#include<cstring>
using namespace std;

int main()
{
 	string str1,str2; 
	int a[256],b[256],r[256];
	int carry;
  	memset(a,0,sizeof(a));
  	memset(b,0,sizeof(b));
  	memset(r,0,sizeof(r));
  	cin>>str1;
  	cin>>str2;
  	int len1=str1.length(),len2=str2.length();
  	int len=len1+len2;
  	for(int i=0;i<len1;i++)
    	a[len1-i]=str1[i]-'0';
  	for(int i=0;i<len2;i++)
    	b[len2-i]=str2[i]-'0';//存入数组

  	for(int i=1;i<=len2;i++)
  	{
    	carry=0;
    	for(int j=1;j<=len1;j++)
    	{
      		r[i+j-1]=a[j]*b[i]+carry+r[i+j-1];
      		carry=r[i+j-1]/10;
      		r[i+j-1]%=10;
    	}
   		 r[i+len1]=carry; //最后一个进位
  	
	  
	  /*for(int i=len;i>=1;i--)
   		 cout<<r[i];
  		cout<<endl;
	  */
	  }
  
  while((r[len]==0)&&(len>1))
    len--;//ɾȥǰ���� 
  for(int i=len;i>=1;i--)
    cout<<r[i];
  cout<<endl;
  return 0;
}
