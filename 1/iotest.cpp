#include <cstdio>
#include <iostream>
using namespace std;
int main(){
  #ifndef _OJ_
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif
  int n;
  scanf("%d", &n);
  long long  a[10] = {0}, b[10]={0};
  for (int i = 0; i < n; ++i){
    scanf("%lld %lld",&a[i],&b[i]);
  }

  for (int i = 0; i < n; ++i){
    printf("%lld %lld\n",a[i],b[i]);
  }

  #ifndef _OJ_
    fclose(stdin);
    fclose(stdout);
  #endif
  return 0;
}