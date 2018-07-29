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
	queue<string> q;//字符串队列
	q.push("01234567");
	dp["01234567"] = 0;//二维的化为一维 dir也只用一个一维数组
	while (!q.empty())
	{
		string now = q.front();
		q.pop();//套路 先更新now 然后再将队列首元素扔了 注意首元素就是一个字符串 代表了拼图的一个状态 
		int zeroposition;//存放0的位置
		for (int j = 0; j < 8; j++)
		{
			if (now[j] == '0')//锁定了一个 0 
			{
				zeroposition = j;
				break;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			int newp = zeroposition + dir[i];
			if (newp >= 0 && newp < 8 &&
				!(zeroposition == 3 && i == 0) && //右上角不能再往右 if(!(a)) 如果a为假就继续
				!(zeroposition == 4 && i == 1))//左下角不能再往左
			{
				string next = now; 
				swap(next[zeroposition], next[newp]);//新旧位置交换 0从旧位置移动到了新位置
				if (dp.find(next) == dp.end())//dp.end() map的尾部 没有实际元素 map的最后一个元素是dp.end()-1
					//用find函数来定位数据出现位置，它返回的一个迭代器，当数据出现时，它返回数据所在位置的迭代器，如果map中没有要查找的数据，它返回的迭代器等于end函数返回的迭代器
				//这里的条件是如果map里没有交换后的字符串 那么就执行以下动态规划
				{
					dp[next] = dp[now] + 1;//动态规划
					//动态规划的思路很好 因为每一个状态的标号其实就代表着这种状态恢复到其实状态的步数 机智 
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
	while (getline(cin, puzzle))//默认回车停止读入 ,按Ctrl+Z或键入EOF回车即可退出循环
		//istream& getline(istream &is, string &str, char delim);第三个字符参数 不设置系统默认为'\n'遇到回车停止输入 
	{
		puzzle.erase(remove(puzzle.begin(), puzzle.end(), ' '), puzzle.end());
		//erase() 删除 remove() 删除
		//这样用是将输入的字符串puzzle中的空格删除 真正的删除 并且释放空间 注意记忆
		cout << dp[puzzle] << endl;
	}
	return 0;
}

