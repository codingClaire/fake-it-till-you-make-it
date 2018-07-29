#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;

map<string, int> dp;
int dir[4] = { 1,-1,4,-4 };

void BFS()
{
	queue<string> q;//�ַ�������
	q.push("01234567");
	dp["01234567"] = 0;//��ά�Ļ�Ϊһά dirҲֻ��һ��һά����
	while (!q.empty())
	{
		string now = q.front();
		q.pop();//��· �ȸ���now Ȼ���ٽ�������Ԫ������ ע����Ԫ�ؾ���һ���ַ��� ������ƴͼ��һ��״̬ 
		int zeroposition;//���0��λ��
		for (int j = 0; j < 8; j++)
		{
			if (now[j] == '0')//������һ�� 0 
			{
				zeroposition = j;
				break;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			int newp = zeroposition + dir[i];
			if (newp >= 0 && newp < 8 &&
				!(zeroposition == 3 && i == 0) && //���Ͻǲ��������� if(!(a)) ���aΪ�پͼ���
				!(zeroposition == 4 && i == 1))//���½ǲ���������
			{
				string next = now; 
				swap(next[zeroposition], next[newp]);//�¾�λ�ý��� 0�Ӿ�λ���ƶ�������λ��
				if (dp.find(next) == dp.end())//dp.end() map��β�� û��ʵ��Ԫ�� map�����һ��Ԫ����dp.end()-1
					//��find��������λ���ݳ���λ�ã������ص�һ���������������ݳ���ʱ����������������λ�õĵ����������map��û��Ҫ���ҵ����ݣ������صĵ���������end�������صĵ�����
				//��������������map��û�н�������ַ��� ��ô��ִ�����¶�̬�滮
				{
					dp[next] = dp[now] + 1;//��̬�滮
					//��̬�滮��˼·�ܺ� ��Ϊÿһ��״̬�ı����ʵ�ʹ���������״̬�ָ�����ʵ״̬�Ĳ��� ���� 
					q.push(next);
				}
			}
		}
	}
}

int main()
{
	BFS();
	string puzzle;
	while (getline(cin, puzzle))//Ĭ�ϻس�ֹͣ���� ,��Ctrl+Z�����EOF�س������˳�ѭ��
		//istream& getline(istream &is, string &str, char delim);�������ַ����� ������ϵͳĬ��Ϊ'\n'�����س�ֹͣ���� 
	{
		puzzle.erase(remove(puzzle.begin(), puzzle.end(), ' '), puzzle.end());
		//erase() ɾ�� remove() ɾ��
		//�������ǽ�������ַ���puzzle�еĿո�ɾ�� ������ɾ�� �����ͷſռ� ע�����
		cout << dp[puzzle] << endl;
	}
	return 0;
}

