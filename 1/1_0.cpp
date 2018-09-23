#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Large{
  Large(){
    num = new int[5000];
    memset(num, 0, sizeof(int) * 5000);
    len = 0;
    s = 0;
  }
  Large(int l){
    num = new int[l];
    memset(num, 0, sizeof(int) * l);
    len = 0;
    s = 0;
  }
  ~Large(){
    delete[] num;
  }
  Large(Large& copy):Large(copy.len){
    len = copy.len;
    for (int i = 0; i < len; ++i){
      num[i] = copy.num[i];
    }
  }
  int operator [] (unsigned int i){
    return num[i];
  }
  void Clear(){
    len = 0;
    s = 0;
  }
  int* num; //每一位
  int len; //位数
  int s; //储存的位置
};
int Max(int a,int b){
  if(a > b)
    return a;
  else
    return b;
}
void jinwei(Large& obj){
  for (int i = 0; i < obj.len; ++i){
    if(obj.num[i] >= 10){
      if(i + 1 >= obj.len){
        obj.len += 1;
      }
      obj.num[i + 1] += obj.num[i] / 10;
      obj.num[i] = obj.num[i] % 10;
    }
  }
}
// Large Mult(int astart,int aend,int bstart,int bend){
  
// }
int main(){

#ifndef _OJ_
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  Large a,b;
  
  for (int i = 0; i < n; ++i){
    a.Clear();
    b.Clear();

    //input
    char *ina, *inb;
    ina = new char[5000];
    inb = new char[5000];
    scanf("%s %s\n", ina,inb);
    
    int la = strlen(ina);
    int lb = strlen(inb);
    
    for (int j = 0; j < la; ++j){
      a.num[a.len++] = ina[j] - '0';
    }

    for (int k = 0; k < lb; ++k){
      b.num[b.len++] = inb[k] - '0';
    }

    
    //multiply
    if ((a.len == 1 && a.num[0] == 0) || (b.len == 1 && b.num[0] == 0)){
      printf("0\n");
      continue;
    }

    else{
      Large c(a.len + b.len + 1);
      for (int k = 0; k < b.len; k++){
        for (int q = 0; q < a.len; q++){
          c.num[k + q] += b[b.len - k - 1] * a[a.len - q - 1];
        }
        c.len = Max(a.len + k, c.len);
        jinwei(c);
      }
        
      //output
      for (int k = c.len - 1; k >= 0; k--){
        printf("%d", c.num[k]);
      }
      printf("\n");
    }
  }
      
#ifndef _OJ_
  fclose(stdin);
  fclose(stdout);
#endif
  
  return 0;
}