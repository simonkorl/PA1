#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#define MAXDIGIT 5000
#define MOVESPACE 10000
#define NUMOFPUSH 4
#define Max(a,b) a > b? a : b
using namespace std;

struct Large{
  Large(){
    num = new int [MAXDIGIT / NUMOFPUSH + 1];
    memset(num, 0, sizeof(int) * (MAXDIGIT / NUMOFPUSH + 1));
    len = 0;
  }
  Large(int l){
    num = new int[l];
    memset(num, 0, sizeof(int) * l);
    len = 0;
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

  void Clear(){
    len = 0;
  }

  int* num; //每一位
  int len; //位数
};
// int Max(long a,long b){
//   if(a > b)
//     return a;
//   else
//     return b;
// }
void jinwei(Large& obj){
  for (int i = 0; i < obj.len; ++i){
    if(obj.num[i] >= MOVESPACE){
      if(i + 1 >= obj.len){
        obj.len += 1;
      }
      obj.num[i + 1] += obj.num[i] / MOVESPACE;
      obj.num[i] = obj.num[i] % MOVESPACE;
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
    ina = new char[MAXDIGIT];
    inb = new char[MAXDIGIT];
    scanf("%s %s\n", ina,inb);
    
    int la = strlen(ina);
    int lb = strlen(inb);
    
    //这里按照讨论的思路进行大整数的压位处理
    //每四位储存进一个integer因为cpu计算一个四位数和计算一个一位数乘法时间差不多
    //这样可以减少乘法的数量
    string num;
    for (int j = la - 1; j >= 0; --j){
      num.insert(0, 1, ina[j]);
      if (num.length() >= 4 || j == 0) {
        a.num[a.len++] = atoi(num.c_str());
        num.clear();
      }
    }


    for (int j = lb - 1; j >= 0; --j) {
      num.insert(0, 1, inb[j]);
      if (num.length() >= 4 || j == 0) {
        b.num[b.len++] = atoi(num.c_str());
        num.clear();
      }
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
          c.num[k + q] += b.num[k] * a.num[k];
        }
        c.len = Max(a.len + k, c.len);
        jinwei(c);
      }
        
      //output
      //这种储存方法的问题在于不能显示一位中的零，需要补零
      bool flag = false;
      for (int k = c.len - 1; k >= 0; k--){
        if (!flag && c.num[k] != 0) {
          flag = true;
        }
        
        if (flag) {
          if (k == c.len - 1) {
            printf("%d", c.num[k]);
          }
          else {
            if (c.num[k] / 1 == 0) 
              printf("0000");
            else if (c.num[k] / 10 == 0) 
              printf("000%d", c.num[k]);
            else if (c.num[k] / 100 == 0) 
              printf("00%d", c.num[k]);
            else if (c.num[k] / 1000 == 0) 
              printf("0%d", c.num[k]);
            else
              printf("%d", c.num[k]);
          }          
        }
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