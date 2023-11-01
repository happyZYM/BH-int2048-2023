#pragma once
#ifndef SJTU_BIGINTEGER
#define SJTU_BIGINTEGER

#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

namespace sjtu {
class int2048 {
  /**
   * If the interger is negative, flag = -1, otherwise flag = 1.
   * num_length is the length of the integer, (num_length+kNum-1)/kNum is the
   * length of val with data. Note that position in val without data is 0.
   */
  const static int kStoreBase = 100000000, kNum = 8, kDefaultLength = 10;
  const static int kMemAdditionScalar = 2, kMemDeleteScalar = 4;
  /**
   * the follow data used by NTT is generated by this code:
#!/usr/bin/python3
from sympy import isprime,primitive_root
found=False
for i in range(0,20):
        for j in range(2**i,(2**(i+1))):
                V=j*(2**(57-i))+1
                if isprime(V):
                        found=True
                        print(j,57-i)
                        print("number=",V)
                        print("root=",primitive_root(V))
                        exit(0)
  * it out puts:
95 55
number= 180143985094819841
root= 6
  */
  const static __int128_t kNTTMod = 180143985094819841ll;
  const static __int128_t kNTTRoot = 6;
  const static int kNTTBlockNum = 4;
  const static int kNTTBlcokBase = 10000;

  size_t buf_length = 0;
  int *val = nullptr;
  signed char flag = +1;
  int num_length = 0;

  __int128_t QuickPow(__int128_t v, long long q);
  void NTTTransform(__int128_t *, int, bool);
  friend int2048 GetInv(const int2048 &,int);

 public:
  int2048();
  int2048(long long);
  int2048(const std::string &);
  int2048(const int2048 &);
  int2048(int2048 &&) noexcept;
  ~int2048();

  void UnsignedMultiplyByInt(int);
  void LeftMoveBy(int);
  void RightMoveBy(int);

  void read(const std::string &);
  void print();
  void print_debug();

  void ClaimMem(size_t);

  inline friend int UnsignedCmp(const int2048 &, const int2048 &);
  inline friend void UnsignedAdd(int2048 &, const int2048 *);
  inline friend void UnsignedMinus(int2048 &, const int2048 *);
  int2048 &add(const int2048 &);
  friend int2048 add(int2048, const int2048 &);

  int2048 &minus(const int2048 &);
  friend int2048 minus(int2048, const int2048 &);

  int2048 operator+() const;
  int2048 operator-() const;

  int2048 &operator=(const int2048 &);
  int2048 &operator=(int2048 &&) noexcept;

  int2048 &operator+=(const int2048 &);
  friend int2048 operator+(int2048, const int2048 &);

  int2048 &operator-=(const int2048 &);
  friend int2048 operator-(int2048, const int2048 &);

  inline friend void UnsignedMultiply(int2048 &, const int2048 *);
  int2048 &Multiply(const int2048 &);
  friend int2048 Multiply(int2048, const int2048 &);

  int2048 &operator*=(const int2048 &);
  friend int2048 operator*(int2048, const int2048 &);

  inline friend void UnsignedDivide(int2048 &, const int2048 *);
  int2048 &Divide(const int2048 &);
  friend int2048 Divide(int2048, const int2048 &);

  int2048 &operator/=(const int2048 &);
  friend int2048 operator/(int2048, const int2048 &);

  int2048 &operator%=(const int2048 &);
  friend int2048 operator%(int2048, const int2048 &);

  friend std::istream &operator>>(std::istream &, int2048 &);
  friend std::ostream &operator<<(std::ostream &, const int2048 &);

  friend bool operator==(const int2048 &, const int2048 &);
  friend bool operator!=(const int2048 &, const int2048 &);
  friend bool operator<(const int2048 &, const int2048 &);
  friend bool operator>(const int2048 &, const int2048 &);
  friend bool operator<=(const int2048 &, const int2048 &);
  friend bool operator>=(const int2048 &, const int2048 &);
};
}  // namespace sjtu

#endif