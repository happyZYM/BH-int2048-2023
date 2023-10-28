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
  size_t buf_length = 0;
  const static int kMod = 100000000, kNum = 8, kDefaultLength = 10;
  const static int kMemAdditionScalar = 2, kMemDeleteScalar = 4;
  int *val = nullptr;
  signed char flag = +1;
  int num_length = 0;

 public:
  int2048();
  int2048(long long);
  int2048(const std::string &);
  int2048(const int2048 &);
  int2048 (int2048 &&) noexcept;
  ~int2048();

  void read(const std::string &);
  void print();

  void ClaimMem(size_t);

  inline friend int UnsignedCmp(const int2048 &A,const int2048 &B);
  inline friend void UnsignedAdd(int2048 &,const int2048 *pB);
  inline friend void UnsignedMinus(int2048 &,const int2048 *pB);
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

  int2048 &operator*=(const int2048 &);
  friend int2048 operator*(int2048, const int2048 &);

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