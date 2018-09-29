#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
#define MAXN 200001
#define MOD 10000
#define sizer(num,i) num = i > MOD ? i / MOD : i
#define max(a,b) a > b ? a : b
int x[MAXN], y[MAXN];
int tx, ty;
int m, n;
struct Large {
  Large() {
    memset(num, 0, sizeof(int) * 8);
    len = 0;
    sign = false;
  }
  Large(int number):Large() {
    if (number < 0) {
      number *= -1;
      sign = true;
    }
    else if (number == 0) {
      sign = false;
      len == 1;
    }
    while (number > 0) {
      num[len++] = number % MOD;
      number /= MOD;
    }  
  }
  Large(const Large& copy) {
    memset(num, 0, sizeof(int) * 8);
    for (int i = 0; i < copy.len; ++i) {
      num[i] = copy.num[i];
    }
    len = copy.len;
    sign = copy.sign;
  }
  Large& operator = (const Large& right) {
    for (int i = 0; i < right.len; ++i) {
      num[i] = right.num[i];
    }
    len = right.len;
    sign = right.sign;
  }
  Large operator + (const Large& right){
    Large r;
    if (right.sign ^ sign) {
      int absc = absCmp(right);
      if (absc > 0) {
        r.sign = sign;
        r.len = len;
        for (int i = 0; i < r.len; ++i) {
          r.num[i] = num[i] - right.num[i];
        }
        arrange(r);
        return r;
      }
      else if (absc < 0) {
        r.sign = right.sign;
        r.len = right.len;
        for (int i = 0; i < r.len; ++i) {
          r.num[i] = right.num[i] - num[i];
        }
        arrange(r);
        return r;
      }
      else
        return ZERO;
    }
    else {
      r.sign = sign;
      r.len = max(len, right.len);
      for (int i = 0; i < r.len; ++i) {
        r.num[i] = num[i] + right.num[i];
      }
      arrange(r);
      return r;
    }
  }
  Large operator - (const Large& right) {
    Large r;
    if (sign ^ right.sign) {
      r.sign = sign;
      r.len = max(len, right.len);
      for (int i = 0; i < r.len; ++i) {
        r.num[i] = num[i] + right.num[i];
      }
      arrange(r);
      return r;
    }
    else {
      int absc = absCmp(right);
      if (absc > 0) {
        r.sign = sign;
        r.len = len;
        for (int i = 0; i < r.len; ++i) {
          r.num[i] = num[i] - right.num[i];
        }
        arrange(r);
        return r;
      }
      else if (absc < 0) {
        r.sign = !sign;
        r.len = right.len;
        for (int i = 0; i < r.len; ++i) {
          r.num[i] = right.num[i] - num[i];
        }
        arrange(r);
        return r;
      }
      else
        return ZERO;
    }
  }
  Large operator * (const Large& right) {
    if ((len == 1 && num[0] == 0) || (right.len == 1 && right.num[0] == 0))
      return ZERO;
    else {
      Large r;
      r.sign = right.sign ^ sign;
      for (int i = 0; i < len; ++i) {
        for (int j = 0; j < right.len; ++j) {
          r.num[i + j] += num[i] * right.num[j];
        }
        r.len = max(r.len, len + right.len);
        arrange(r);
      }
      return r;
    }
  }
  int absCmp(const Large& other) {
    if (other.sign ^ sign)
      return sign ? -1 : 1;
    else {
      if (len != other.len) {
        if (sign)
          return len < other.len ? 1 : -1;
        else
          return len > other.len ? 1 : -1;
      }
      else {
        for (int i = len - 1; i >= 0; --i) {
          if (num[i] > other.num[i])
            return 1;
          else if (num[i] < other.num[i])
            return -1;
        }
        return 0;
      }
    }
  }
  static void arrange(Large& obj) {
    for (int i = 0; i < obj.len; ++i) {
      if (obj.num[i] >= MOD) {
        if (i == obj.len - 1) {
          obj.len++;
        }
        obj.num[i + 1] += obj.num[i] / MOD;
        obj.num[i] = obj.num[i] % MOD;
      }
      else if (obj.num[i] < 0 && i < obj.len - 1) {
        obj.num[i] *= -1;
        obj.num[i + 1] -= obj.num[i] / MOD + 1;
        obj.num[i] = (obj.num[i] / MOD + 1) * MOD - obj.num[i];
      }
    }
    while (obj.num[obj.len - 1] == 0 && obj.len > 1) obj.len--;
    if (obj.num[obj.len - 1] < 0) {
      obj.num[obj.len - 1] *= -1;
      obj.sign = true;
    }
  }
  const static Large ZERO;
  int num[8];
  int len;
  bool sign;
};
const Large Large::ZERO(0);
//此处对三角形有向面积计算公式和Toleft算法的意义参考了 https://blog.csdn.net/qust_waiwai/article/details/81065857
int ToLeft(int line){
  unsigned long long xy = 0, txy = 0;
  xy =(unsigned long long) (x[line]) * (unsigned long long )y[line] ;
  txy = (unsigned long long) tx * (unsigned long long)y[line] + (unsigned long long) ty * (unsigned long long)x[line];

  //Large r = (xi * yi) - (txi * yi) - (tyi * xi);
  if (xy > txy)
    return 1;
  else if (xy < txy)
    return -1;
  else
    return 0;
  //return r.absCmp(Large::ZERO);
}
void Merge(int* arr,int lo,int mid,int hi){
  int *p = arr + lo;
  int lb = mid - lo;
  int *tmpl = new int[lb];
  for (int i = 0; i < lb; ++i)
    tmpl[i] = p[i];
  int lc = hi - mid;
  int *tmpr = arr + mid;
  for (int i = 0, j = 0, k = 0; j < lb;)
    p[i++] = (lc <= k || tmpl[j] <= tmpr[k]) ? tmpl[j++] : tmpr[k++];
  delete[] tmpl;
}
void MergeSort(int* arr,int lo,int hi){
  if(hi - lo < 2)
    return;
  int mid = (lo + hi) >> 1;
  MergeSort(arr,lo, mid);
  MergeSort(arr,mid , hi);
  Merge(arr,lo, mid, hi);
}

int Binsearch(int lo,int hi){
  
  int l = -1;
  while(lo < hi){
    int mid = (lo + hi) >> 1;
    
    int left = ToLeft(mid);

    if (left < 0){
      l = mid;
      lo = mid + 1;
    }
    else if (left > 0){
      hi = mid;
    }
    else
      return mid + 1;
  }
  return l + 1;
  /*
  lo = 0; hi = n - 1;
  while (lo <= hi) {
    int mid = (lo + hi) >> 1;

    int left = ToLeft(mid);

    if (left > 0) {
      hi = mid - 1;
    }
    else{
      lo = mid + 1;
    }
  }
  return hi + 1;
  */
}

int main(){
#ifndef _OJ_
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif // _OJ_
  
  scanf("%d", &n);
  for (int i = 0; i < n; ++i){
    scanf("%d", &x[i]);
  }
  for (int j = 0; j < n; ++j){
    scanf("%d", &y[j]);
  }
  MergeSort(&x[0], 0, n);
  MergeSort(&y[0], 0, n);
  scanf("%d", &m);
  for (int i = 0; i < m; ++i){
    scanf("%d %d", &tx, &ty);
    int result = Binsearch(0, n);
    printf("%d\n",result);
  }
#ifndef _OJ_
  fclose(stdin);
  fclose(stdout);
#endif //_OJ_
  return 0;
}