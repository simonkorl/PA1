#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
struct Large{
  Large(){
    num = new int[5000];
    memset(num, 0, 5000 * sizeof(int));
    len = 0;
  }
  Large(int l){
    num = new int[l];
    memset(num, 0, l * sizeof(int));
    len = l;
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
  int* num; //每一位
  int len; //位数
};
// Large Mult(int astart,int aend,int bstart,int bend){

// }
int main(){

#ifndef _OJ_
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  Large a, b;

  for (int i = 0; i < n; ++i){
    a.len = 0;
    b.len = 0;
    //input
    char *in;
    in = new char[10002];
    scanf("%s", in);

    int length = strlen(in);
    int j = 0;
    for (; j < length; ++j){
      if(in[j] != ' '){
        a.num[j] = in[j] - '0';
        a.len++;
      }
      else 
        break;
    }
    for (j = j + 1; j < length; ++j){
      if(in[j] != '\n'){
        b.num[j] = in[j] - '0';
        b.len++;
      }
    }
    //multiply
    if ((a.len == 1 && a.num[0] == 0) || (b.len == 1 && b.num[0] == 0)){
      printf("0\n");
      delete in;
      continue;
    }

    else{
      Large c(a.len + b.len);
      for (int k = 0; k < b.len; k++){
        for (int q = 0; q < a.len; q++){
          c.num[k + q] = b[b.len - k - 1] * a[a.len - q - 1];
        }
      }
        //output

        printf("\n");
      delete in;
    }
  }
      
#ifndef _OJ_
  fclose(stdin);
  fclose(stdout);
#endif

  return 0;
}