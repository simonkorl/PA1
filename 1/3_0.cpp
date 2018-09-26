#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#ifndef _OJ_
#include <Windows.h>
#endif // !_OJ_

using namespace std;

#define MAXDIGIT 5000
#define Max(a,b) a > b ? a : b
const int MAXN = 1e4 + 8000;
struct Complex{
  Complex(){
    a = 0;
    b = 0;
  }
  Complex(double x,double y):a(x),b(y){}
  ~Complex() {}
  Complex operator + (const Complex& right) const {
    return Complex(a + right.a, b + right.b);
  }
  Complex operator - (const Complex& right) const{
    return Complex(a - right.a, b - right.b);
  }
  Complex operator * (const Complex& right) const{
    return Complex((a * right.a - b * right.b), (b * right.a + a * right.b));
  }
  void Clear() { a = 0; b = 0; }
  double a, b;
};

static const double Pi = acos(-1.0);
//快速傅里叶变换的实现参考了 https://www.cnblogs.com/zwfymqz/p/8244902.html?mType=Group#!comments 中的程序
//inverse == 1 从频域向时域转化, inverse == -1 时从时域向频域转化
void fft(Complex a[],int limit,int r[],int inverse){
  for (int i = 0; i < limit; i++)
    if (i < r[i])
      swap(a[i], a[r[i]]);

  for (int mid = 1; mid < limit; mid *= 2){
    Complex Wn(cos(Pi / mid), inverse * sin(Pi / mid));
    int R = mid << 1;
    for (int i = 0; i < limit; i += R){
      Complex Wk(1, 0);
      for (int k = 0; k < mid; ++k,Wk = Wk * Wn){
        Complex a1 = a[i + k], a2 = Wk * a[i + mid + k];
        a[i + k] = a1 + a2;
        a[i + mid + k] = a1 - a2;
      }
    }
  }
}
char ina[MAXDIGIT + 1], inb[MAXDIGIT + 1];
int r[MAXN + 1];
Complex A[MAXN], B[MAXN];
int main(){
#ifndef _OJ_
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  LARGE_INTEGER nFreq;//LARGE_INTEGER在64位系统中是LONGLONG，在32位系统中是高低两个32位的LONG，在windows.h中通过预编译宏作定义
  LARGE_INTEGER nBeginTime;//记录开始时的计数器的值
  LARGE_INTEGER nEndTime;//记录停止时的计数器的值
  double time;

  QueryPerformanceFrequency(&nFreq);//获取系统时钟频率
  QueryPerformanceCounter(&nBeginTime);//获取开始时刻计数值

  //To Do:
#endif
  int n = 0;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i){
    if (i != 0) {
      for (int i = 0; i < MAXN; ++i) {
        A[i].Clear();
        B[i].Clear();
      }
    }
    scanf("%s %s\n", ina, inb);
    int la = strlen(ina);
    int lb = strlen(inb);
    int limit = 1, l = 0;
    int lensum = la + lb;
    while (limit <= lensum)
      limit <<= 1, l++;
    
    for (int i = la - 1; i >= 0; --i){
      A[la - i - 1].a = ina[i] - '0';
    }
    for (int i = lb - 1; i >= 0; --i){
      B[lb - i - 1].a = inb[i] - '0';
    }
    if((la == 1 && A[0].a == 0) || (lb == 1 && B[0].a == 0)){
      printf("0\n");
      //delete[] ina;
      //delete[] inb;
      //delete[] A;
      //delete[] B;
      continue;
    }
    else{
      for (int i = 0; i < limit; i++)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));

      fft(A, limit, r, 1);
      fft(B, limit, r, 1);

      for (int i = 0; i <= limit; ++i){
        A[i] = A[i] * B[i];
      }
      fft(A, limit, r, -1);
      
      int len = lensum;
      for (int i = 0; i < len; ++i) {
        A[i].a = (int)(A[i].a / limit + 0.5);
      }
      while (A[len - 1].a == 0) len--;
      for (int i = 0; i < len - 1; ++i) {
        A[i + 1].a += int(A[i].a) / 10;
        A[i].a = int(A[i].a) % 10;
      }
      if (A[len - 1].a >= 10) {
        A[len].a += int(A[len - 1].a) / 10;
        A[len - 1].a = int(A[len - 1].a) % 10;
        len++;
      }
      for (int i = len - 1; i >= 0; --i){
          printf("%d", (int)(A[i].a));
      }
      printf("\n");
      //delete[] ina;
      //delete[] inb;
      //delete[] r;
      //delete[] A;
      //delete[] B;
    }
  }
#ifndef _OJ_  
  QueryPerformanceCounter(&nEndTime);//获取停止时刻计数值
  time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart * 1000;//（开始-停止）/频率即为秒数，精确到小数点后6位
  printf("time:%lf", time);
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}