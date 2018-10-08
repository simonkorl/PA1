#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;
#define MAXN 501001
#define MOD 10000
#define max(a,b) a > b ? a : b
#define UP 0
#define DOWN 1
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
  
  int *f[2];
  for (int i = 0; i < 2; ++i) {
    f[i] = new int[m];
  }
  //初始化
  if (fn[0] == fm[0]) 
    f[UP][0] = 1;
  else
    f[UP][0] = 0;

  for (int j = 1; j < m; ++j) {
    if (fn[0] == fm[j])
      f[UP][j] = 1;
    else 
      f[UP][j] = f[UP][j - 1];
  }
  //此处动态规划的减治思路来自课本
  for (int i = 1; i < n; ++i) {
    if (fn[i] == fm[0])
      f[DOWN][0] = 1;
    else
      f[DOWN][0] = f[UP][0];

    for (int j = 1; j < m; ++j) {
      if (fn[i] == fm[j]) {
        f[DOWN][j] = f[UP][j - 1] + 1;
      }
      else {
        f[DOWN][j] = max(f[UP][j], f[DOWN][j - 1]);
      }
    }

    swap(f[0],f[1]);
  }

  int r = m + n - 2 * f[UP][m - 1];
  if (r > k)
    printf("-1");
  else
    printf("%d", r);

  for (int i = 0; i < 2; ++i) {
    delete[] f[i];
  }
#ifndef _OJ_
  fclose(stdin);
  fclose(stdout);
#endif //_OJ_
  return 0;
}