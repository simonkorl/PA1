#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;
#define MAX 100
#define MID 100 + 1
int n, m, k;
int v[2 * MAX + 3];
string fn, fm;
int x, y;
int main(){
#ifndef _OJ_
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif // _OJ_
  
  scanf("%d %d %d", &n, &m, &k);
  fn.resize(n);
  fm.resize(m);
  scanf("%s\n%s\n", &fn[0], &fm[0]);
  //此处算法部分为实现文献中的伪代码
  for (int d = 0; d <= k; ++d){
    for (int i = MID - d; i <= MID + d; i += 2){
      if(i == MID - d || (i != MID + d && v[i - 1] < v[i + 1]))
        x = v[i + 1];
      else
        x = v[i - 1] + 1;
      y = x - i + MID;
      while(x < n && y < m && fn[x] == fm[y])
        x += 1, y += 1;
      v[i] = x;
      if(x >= n && y >= m){
        printf("%d", d);
        #ifndef _OJ_
        fclose(stdin);
        fclose(stdout);
        #endif //_OJ_
        return 0;
      }
    }
  }
  printf("-1");
#ifndef _OJ_
  fclose(stdin);
  fclose(stdout);
#endif //_OJ_
  return 0;
}