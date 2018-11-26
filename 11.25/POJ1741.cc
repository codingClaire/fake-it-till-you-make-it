// POJ1741 Tree
// 陈锋
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <climits>
#include <iostream>
#include <sstream>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <vector>

using namespace std;
#define _for(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define _zero(D) memset((D), 0, sizeof(D))
#define _init(D, v) memset((D), (v), sizeof(D))
#define _ri1(x) scanf("%d", &(x))
#define _ri2(x, y) scanf("%d%d", &(x), &(y))
#define _ri3(x, y, z) scanf("%d%d%d", &(x), &(y), &(z))
#define _ri4(a, b, c, d) scanf("%d%d%d%d", &(a), &(b), &(c), &(d))
typedef long long LL;

const int MAXN = 1e4 + 4;
vector<pair<int, int> >G[MAXN];
int VIS[MAXN], SZ[MAXN], MaxSub[MAXN], Dep[MAXN], N, K; // 子树u的 访问标记，体积，最大子树体积，所有点深度


void find_heart(int u, int fa, int tree_size, int& heart) { // 给定子树大小，找到子树重心
  int &szu = SZ[u], &msu = MaxSub[u];
  szu = 1, msu = 0; // MaxSub[u]表示去以u为root的最大子树体积
  _for(i, 0, G[u].size()) {
    int v = G[u][i].first;
    if (v == fa || VIS[v]) continue;
    find_heart(v, u, tree_size, heart);
    msu = max(SZ[v], msu), szu += SZ[v]; //用子树v的节点数更新maxson[u]
  }
  msu = max(msu, tree_size - SZ[u]);
  if (msu < MaxSub[heart]) heart = u;
}

void get_all_deps(int u, int fa, vector<int>& deps) { // 计算子树u下所有节点的depth
  deps.push_back(Dep[u]);
  SZ[u] = 1;
  _for(i, 0, G[u].size()) {
    int v = G[u][i].first, w = G[u][i].second;
    if (v == fa || VIS[v]) continue;
    Dep[v] = Dep[u] + w;
    get_all_deps(v, u, deps);
    SZ[u] += SZ[v];
  }
}

int count_pairs(int u, int fa, int u_height) { // 子树u下所有符合条件的点对个数
  vector<int> D; // 子树u所有节点深度
  Dep[u] = u_height;
  get_all_deps(u, fa, D);
  sort(D.begin(), D.end()); // 对deps排序后
  int cnt = 0, l = 0, r = D.size() - 1;
  while (l < r) { // 用双指针扫一遍得到合法点对数
    if (D[l] + D[r] <= K) cnt += (r - l), l++;
    else r--;
  }
  return cnt;
}

int solve(int u, int fa) { // 子树u求解
  VIS[u] = 1; // 子树内遍历走到u就停
  int ans = count_pairs(u, fa, 0); // 计算当前根下所有合法点对的个数
  _for(i, 0, G[u].size()) {
    int v = G[u][i].first, w = G[u][i].second;
    if (v == fa || VIS[v]) continue;
    ans -= count_pairs(v, u, w); // 去除同一子树内部的合法点对
    int heart = 0;
    find_heart(v, u, SZ[v], heart); // 找到子树v的重心
    ans += solve(heart, u); // 递归求解
  }
  return ans;
}

int main() {
  while (_ri2(N, K) && (N || K)) {
    _rep(i, 1, N) G[i].clear();
    int u, v, w, heart = 0;
    MaxSub[0] = N + 1;
    _zero(VIS);
    _for(i, 1, N) {
      _ri3(u, v, w);
      G[u].push_back(make_pair(v, w)), G[v].push_back(make_pair(u, w));
    }
    find_heart(1, -1, N, heart); // 找到整颗树的重心
    int ans = solve(heart, -1); // 递归求解
    printf("%d\n", ans);
  }
  return 0;
}