#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;
#define MAXN 501001
#define MOD 10000
#define max(a,b) a > b ? a : b
int n, m, k;
string fn, fm;
int main(){
#ifndef _OJ_
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif // _OJ_
  scanf("%d %d %d", &n, &m, &k);
  fn.resize(n);
  fm.resize(m);
  scanf("%s\n%s\n", &fn[0], &fm[0]);
  int **f = new int*[n];
  //调试中出现了问题，在网上浏览了相关资料后进行了初始化操作
  for (int i = 0; i < n; ++i) {
    f[i] = new int[m];
    if (i == 0) {
      if (fn[i] == fm[0])
        f[i][0] = 1;
      else
        f[i][0] = 0;
    }
    else {
      if (fn[i] == fm[0])
        f[i][0] = 1;
      else
        f[i][0] = max(f[i - 1][0], 0);
    }  
  }
  for (int i = 0; i < m; ++i) {
    f[0][i] = max(f[0][0], 0);
  } 
  //此处动态规划的减治思路来自课本
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      if (fn[i] == fm[j]) {
        f[i][j] = f[i - 1][j - 1] + 1;
      }
      else {
        f[i][j] = max(f[i - 1][j], f[i][j - 1]);
      }
    }
  }
  int r = m + n - 2 * f[n - 1][m - 1];
  if (r <= k) {
    printf("%d", r);
  }
  else {
    printf("-1");
  }
  for (int i = 0; i < n; ++i) {
    delete[] f[i];
  }
  delete[] f;
#ifndef _OJ_
  fclose(stdin);
  fclose(stdout);
#endif //_OJ_
  return 0;
}