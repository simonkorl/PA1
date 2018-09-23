#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#define MAXDIGIT 5000
#define MODNUM 10000
#define Max(a,b) a > b?a : b
#define Min(a,b) a < b?a : b
using namespace std;

struct Large{
  Large(){
    num = NULL;
    len = 0;
    sign = false;
  }
  Large(int l){
    if (l != 0) {
      num = new int[l];
      memset(num, 0, sizeof(int) * l);
      len = 0;
      sign = false;
    }
    else {
      num = new int[1];
      len = 1;
      num[0] = 0;
      sign = false;
    }  
  }
  Large(int l,int ll) {
    num = new int[l];
    memset(num, 0, sizeof(int) * l);
    len = ll;
    sign = false;
  }
  ~Large(){
    delete[] num;
  }
  Large(const Large& copy):Large(copy.len){
    /*
    if (num == NULL) {
      getSpace(copy.len);
    }
    */
    len = copy.len;
    for (int i = 0; i < len; ++i){
      num[i] = copy.num[i];
    }
    sign = copy.sign;
  }
  Large(long long lln) {
    num = new int[16];
    if (lln > 0)
      sign = false;
    else {
      sign = true;
      lln *= -1;
    }
    len = 0;
    while (lln > 0) {
      num[len++] = lln % 10000;
      lln /= 10000;
    }
  }
  Large& operator = (const Large& copy) {
    /*
    if (num == NULL) {
      getSpace(copy.len);
    }*/
    len = copy.len;
    for (int i = 0; i < len; ++i) {
      num[i] = copy.num[i];
    }
    sign = copy.sign;
    return *this;
  }
  const int operator [](int i) const{
    if (i >= len || i < 0)
      return 0;
    else
      return num[i];
  }

  int& operator [](int i){
    if (i >= len || i < 0) {
      cout << "operator[] overflow" << endl;
      return num[0];
    }
    else
      return num[i];
  }

  Large operator * (const Large& b) {
    if (len == 1 && num[0] == 0 || b.len == 1 && b.num[0] == 0)
      return Large(0);
    else if (len <= 2 && b.len <= 2)
    {
      long long la = toLongLong();
      long long lb = b.toLongLong();
      return Large(long long(la*lb));
    }
    else {
      Large *A, *B, *C, *D;

      int amid = len / 2;
      B = new Large(amid + 1, amid + 1);
      B->Copy(*this, 0, amid - 1);
      adjust(*B);

      A = new Large(amid + 1, amid + 1);
      A->Copy(*this, amid, len - 1);
      adjust(*A);

      int bmid = b.len / 2;
      D = new Large(bmid + 1, bmid + 1);
      D->Copy(b, 0, bmid - 1);
      adjust(*D);

      C = new Large(bmid + 1, bmid + 1);
      C->Copy(b, bmid, b.len - 1);
      adjust(*C);

      Large AC = *A * *C;
      Large BD = *B * *D;
      Large ZA = A->addZeroes(amid);
      Large ZC = C->addZeroes(bmid);
      Large com = (ZA - *B) * (*D - ZC);            
      delete A;
      delete B;
      delete C;
      delete D;

      Large r(AC.len + amid + bmid + 1);
      r = (AC + AC).addZeroes(amid + bmid) + com + BD + BD;
      adjust(r);
      return r;
    }
  }
  Large operator + (const Large& b) const{
    const Large * const a = this;
    Large r(Max(a->len, b.len) + 1, Max(a->len, b.len));
    if (len <= 2 && b.len <= 2)
    {
      long long la = toLongLong();
      long long lb = b.toLongLong();
      return Large(long long(la + lb));
    }
    else if (!(a->sign ^ b.sign)) {
      r.sign = a->sign;
      for (int i = 0; i < r.len; ++i) {
        r[i] = a->operator[](i) + b[i];
      }
      adjust(r);
      return r;
    }
    else {
      if (a->absLargerThan(b) > 0) {
        for (int i = 0; i < a->len; ++i) {
          r.num[i] = a->operator[](i) - b[i];
        }
        r.sign = a->sign;
        adjust(r);
        return r;
      }
      else if (a->absLargerThan(b) < 0) {
        for (int i = 0; i < b.len; ++i) {
          r.num[i] = b[i] - a->operator[](i);
        }
        r.sign = b.sign;
        adjust(r);
        return r;

      }
      else
        return ZERO;
    }
    
  }
  Large operator - (const Large& b) const{
    const Large* const a = this;
    Large r(Max(a->len, b.len) + 1, Max(a->len, b.len));
    if (len <= 2 && b.len <= 2)
    {
      long long la = toLongLong();
      long long lb = b.toLongLong();
      return Large(long long(la*lb));
    }
    else if (!(a->sign ^ b.sign)) {
      if (a->absLargerThan(b) > 0) {
        for (int i = 0; i < r.len; ++i) {
          r[i] = a->operator[](i) - b[i];
        }
        r.sign = a->sign;
        adjust(r);
        return r;
      }
      else if (a->absLargerThan(b) < 0) {
        for (int i = 0; i < r.len; ++i) {
          r[i] = b[i] - a->operator[](i);
        }
        r.sign = !a->sign;
        adjust(r);
        return r;
      }
      else
        return ZERO;
    }
    else {
      r.sign = a->sign;
      for (int i = 0; i < r.len; ++i) {
        r[i] = a->operator[](i) + b[i];
      }
      adjust(r);
      return r;
    }
    
  }

  static void adjust(Large& obj) {
    for (int i = 0; i < obj.len; ++i) {
      if (abs(obj.num[i]) >= 10000) {
        if (i == obj.len - 1) {
          obj.len += 1;
        }
        obj.num[i + 1] += obj.num[i] / 10000;
        obj.num[i] = abs(obj.num[i] % 10000);
      }
      else if (obj.num[i] < 0 && i != obj.len - 1){
        int tui = -(obj.num[i] / 10000) + 1;
        obj.num[i + 1] -= tui;
        obj.num[i] += tui * 10000;
      }
    }
    while (obj.num[obj.len - 1] == 0)obj.len--;
    if (obj.num[obj.len - 1] < 0) {
      obj.sign = true;
      obj.num[obj.len - 1] = -obj.num[obj.len - 1];
    }
  }
  void Clear(){
    len = 0;
  }
  long long toLongLong() const{
    long long a = 0;
    for (int i = len - 1; i >= 0; i--) {
      a += num[i];
      if (i > 0)
        a *= 10000;
    }
    if (sign)
      a *= -1;
    return a;
  }
  void Copy(const Large& copy, int start, int end) {
    if (end < start || start >= copy.len || end >= copy.len|| start < 0)
      return;
    else {
      len = end - start + 1;
      for (int i = 0; i < len; ++i) {
        num[i] = copy[start + i];
      }
    }
  }
  int absLargerThan(const Large& b) const{
    if (this->len > b.len)
      return 1;
    else if (this->len < b.len)
      return -1;
    else {
      for (int i = this->len - 1; i >= 0; --i) {
        if (this->num[i] > b.num[i])
          return 1;
        else if (this->num[i] < b.num[i])
          return -1;
        else
          continue;
      }
      return 0;
    }
  }
  Large addZeroes(int number) {
    if (number > 0) {
      Large r(number + len, number + len);
      for (int i = number; i < len + number; ++i) {
        r.num[i] = num[i - number];
      }
      return r;
    }
    else
      return ZERO;
  }
  int* num; //每一位
  int len; //位数
  bool sign; //符号，false 为正,true 为负
  static const Large ZERO;
private:
  void getSpace(int size) {
    if (num != NULL) {
      delete[] num;
    }
    num = new int[size];
    memset(num, 0, sizeof(int) * size);
  }

};
const Large Large::ZERO = Large(0);

int main(){

#ifndef _OJ_
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  Large a(1251),b(1251);
  
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
      c = a * b;
        
      //output
      //这种储存方法的问题在于不能显示一位中的零，需要补零
      for (int k = c.len - 1; k >= 0; k--){
          if (k == c.len - 1) 
            printf("%d", c.num[k]);
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
      printf("\n");
    }
  }
      
#ifndef _OJ_
  fclose(stdin);
  fclose(stdout);
#endif
  
  return 0;
}