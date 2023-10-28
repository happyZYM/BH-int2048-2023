/**
 * @file int2048.cpp --- 2048-bit integer class implementation
 *
 * @details This file contains the implementation of the 2048-bit integer class.
 *
 * Codesytle: This file is written in a sytle mainly based on Google C++ Style
 * Guide. As I use Clang-format to format my code, so the code style may be a
 * little bit strange sometimes, in that case I'll manually format the
 * code.What's sepecial is the comment:
 * 1. Multi-line comments are always before the code they comment on.
 * Usually the code they comment on is a complex procedure,like the definition
 * of a function,a class or a variable with complex operation. If a multi-line
 * comment is in one line, it will start with "/*" instead of "/**",otherwise it
 * will start with "/**" and in the format of Doxygen.
 * 2. Single-line comments are always after the code they comment on.
 * Usually they are in the same line with the code they comment on,but sometimes
 * they may come in the next lines. single-line comments shouldn't exceed 3
 * lines as they are intended to be short and easy to understand.
 * 3. Temporary disabled code will be marked with "//" in the front of each
 * 4. Some comments have special meanings,like "//TODO", "//FIXME", "//XXX","//
 * clang-format off" and "// clang-format on". They are not controlled by the
 * previous rules.
 */
#include "int2048.h"

#include <cstdio>
#include <cstring>
#include <utility>
namespace sjtu {
// 构造函数
int2048::int2048() {
  // 实现构造函数逻辑
  buf_length = kDefaultLength;
  val = new int[buf_length]();
  flag = 1;
  num_length = 1;
}

int2048::int2048(long long input_value) {
  // 实现构造函数逻辑
  buf_length = kDefaultLength;
  val = new int[buf_length]();
  if (input_value < 0) {
    flag = -1;
    input_value = -input_value;
  } else
    flag = 1;
  if (input_value == 0) {
    num_length = 1;
    return;
  }
  num_length = 0;
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  while (input_value > 0) {
    val[num_length / kNum] += (input_value % 10) * kPow10[num_length % kNum];
    input_value /= 10;
    num_length++;
  }
}

int2048::int2048(const std::string &input_value) {
  // 实现构造函数逻辑
  buf_length = (input_value.length() + kNum - 1) / kNum * kMemAdditionScalar;
  val = new int[buf_length]();
  flag = 1;
  num_length = 0;
  if (input_value[0] == '-') {
    flag = -1;
  }
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  int read_highest_pos = (flag > 0 ? 0 : 1);
  while (input_value[read_highest_pos] == '0' &&
         read_highest_pos + 1 < input_value.length())
    read_highest_pos++;
  for (int i = input_value.length() - 1; i >= read_highest_pos; i--) {
    val[num_length / kNum] +=
        (input_value[i] - '0') * kPow10[num_length % kNum];
    num_length++;
  }
  if (num_length == 1 && val[0] == 0) flag = 1;
}

int2048::int2048(const int2048 &input_value) {
  buf_length = input_value.buf_length;
  val = new int[buf_length]();
  memcpy(val, input_value.val, buf_length * sizeof(int));
  flag = input_value.flag;
  num_length = input_value.num_length;
}

int2048::int2048(int2048 &&input_value) noexcept {
  buf_length = input_value.buf_length;
  val = input_value.val;
  flag = input_value.flag;
  num_length = input_value.num_length;
  input_value.val = nullptr;
}

// 读入一个大整数
void int2048::read(const std::string &input_value) {
  delete[] val;
  buf_length = (input_value.length() + kNum - 1) / kNum * kMemAdditionScalar;
  val = new int[buf_length]();
  flag = 1;
  num_length = 0;
  if (input_value[0] == '-') {
    flag = -1;
  }
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  int read_highest_pos = (flag > 0 ? 0 : 1);
  while (input_value[read_highest_pos] == '0' &&
         read_highest_pos + 1 < input_value.length())
    read_highest_pos++;
  for (int i = input_value.length() - 1; i >= read_highest_pos; i--) {
    val[num_length / kNum] +=
        (input_value[i] - '0') * kPow10[num_length % kNum];
    num_length++;
  }
  if (num_length == 1 && val[0] == 0) flag = 1;
}

// 输出储存的大整数，无需换行
void int2048::print() {
  // 实现输出逻辑
  if (flag == -1) putchar('-');
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  for (int i = num_length - 1; i >= 0; i--)
    putchar('0' + val[i / kNum] / kPow10[i % kNum] % 10);
}

void int2048::ClaimMem(size_t number_length) {
  size_t new_number_blocks = (number_length + kNum - 1) / kNum;
  if (new_number_blocks > buf_length) {
    int *new_val = new int[new_number_blocks * kMemAdditionScalar]();
    memcpy(new_val, val, buf_length * sizeof(int));
    delete[] val;
    val = new_val;
    buf_length = new_number_blocks * kMemAdditionScalar;
  } else if (new_number_blocks * kMemDeleteScalar < buf_length) {
    int *new_val = new int[new_number_blocks * kMemAdditionScalar]();
    memcpy(new_val, val, new_number_blocks * sizeof(int));
    delete[] val;
    val = new_val;
    buf_length = new_number_blocks * kMemAdditionScalar;
  }
}

inline int UnsignedCmp(const int2048 &A, const int2048 &B) {
  if (A.num_length != B.num_length) return A.num_length < B.num_length ? -1 : 1;
  int number_of_blocks = (A.num_length + A.kNum - 1) / A.kNum;
  for (int i = number_of_blocks - 1; i >= 0; i--)
    if (A.val[i] != B.val[i]) return A.val[i] < B.val[i] ? -1 : 1;
  return 0;
}

inline void UnsignedAdd(int2048 &A, const int2048 *const pB) {
  if (&A == pB) throw "UnsignedAdd: A and B are the same object";
  A.ClaimMem(std::max(A.num_length, pB->num_length) + 2);
  for (int i = 0;
       i < (std::max(A.num_length, pB->num_length) + A.kNum - 1) / A.kNum;
       i++) {
    if (i < (pB->num_length + pB->kNum - 1) / pB->kNum) A.val[i] += pB->val[i];
    A.val[i + 1] += A.val[i] / A.kMod;
    A.val[i] %= A.kMod;
  }
  A.num_length = std::max(A.num_length, pB->num_length);
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  if (A.val[A.num_length / A.kNum] / kPow10[A.num_length % A.kNum] > 0)
    A.num_length++;
}

inline void UnsignedMinus(int2048 &A, const int2048 *const pB) {
  if (&A == pB) throw "UnsignedMinus: A and B are the same object";
  ;
}
// 加上一个大整数
int2048 &int2048::add(const int2048 &B) {
  // 实现加法逻辑
  const int2048 *pB = &B;
  if (this->flag == pB->flag) {
    if (this == &B) pB = new int2048(B);
    UnsignedAdd(*this, pB);
  } else if (this->flag == 1 && pB->flag == -1) {
    int cmp = UnsignedCmp(*this, *pB);
    if (cmp >= 0) {
      if (this == &B) pB = new int2048(B);
      UnsignedMinus(*this, pB);
      this->flag = 1;
    } else {
      int2048 new_B = std::move(*this);
      *this = B;
      UnsignedMinus(*this, &new_B);
      this->flag = -1;
    }
  } else if (this->flag == -1 && pB->flag == 1) {
    int cmp = UnsignedCmp(*this, *pB);
    if (cmp >= 0) {
      if (this == &B) pB = new int2048(B);
      UnsignedMinus(*this, pB);
      this->flag = -1;
    } else {
      int2048 new_B = std::move(*this);
      *this = B;
      UnsignedMinus(*this, &new_B);
      this->flag = 1;
    }
  }
  return *this;
}

// 返回两个大整数之和
int2048 add(int2048 A, const int2048 &B) {
  // 实现加法逻辑
  return A.add(B);
}

// 减去一个大整数
int2048 &int2048::minus(const int2048 &B) {
  // 实现减法逻辑
  const int2048 *pB = &B;
  if (this == &B) pB = new int2048(B);
  UnsignedMinus(*this, pB);
  return *this;
}

// 返回两个大整数之差
int2048 minus(int2048 A, const int2048 &B) {
  // 实现减法逻辑
  return A.minus(B);
}

// 运算符重载

int2048 int2048::operator+() const {
  // 实现一元加法逻辑
  return int2048(*this);
}

int2048 int2048::operator-() const {
  // 实现一元减法逻辑
  int2048 ret(*this);
  if (!(ret.num_length == 1 && ret.val[0] == 0)) ret.flag = -ret.flag;
  return ret;
}

int2048 &int2048::operator=(const int2048 &B) {
  // 实现赋值运算符逻辑
  // similar to int2048::int2048(const int2048 &input_value)
  if (this == &B) return *this;
  delete[] val;
  buf_length = B.buf_length;
  val = new int[buf_length]();
  memcpy(val, B.val, buf_length * sizeof(int));
  flag = B.flag;
  num_length = B.num_length;
  return *this;
}

int2048 &int2048::operator=(int2048 &&B) noexcept {
  // 实现移动赋值运算符逻辑
  if (this == &B) return *this;
  delete[] val;
  buf_length = B.buf_length;
  val = B.val;
  flag = B.flag;
  num_length = B.num_length;
  B.val = nullptr;
  return *this;
}

int2048 &int2048::operator+=(const int2048 &B) {
  // 实现复合加法逻辑
  return this->add(B);
}

int2048 operator+(int2048 A, const int2048 &B) {
  // 实现加法逻辑
  A.add(B);
  return A;
}

int2048 &int2048::operator-=(const int2048 &B) {
  // 实现复合减法逻辑
  return this->minus(B);
}

int2048 operator-(int2048 A, const int2048 &B) {
  // 实现减法逻辑
  A.minus(B);
  return A;
}

int2048 &int2048::operator*=(const int2048 &) {
  // 实现复合乘法逻辑
}

int2048 operator*(int2048, const int2048 &) {
  // 实现乘法逻辑
}

int2048 &int2048::operator/=(const int2048 &) {
  // 实现复合除法逻辑
}

int2048 operator/(int2048, const int2048 &) {
  // 实现除法逻辑
}

int2048 &int2048::operator%=(const int2048 &) {
  // 实现复合取模逻辑
}

int2048 operator%(int2048, const int2048 &) {
  // 实现取模逻辑
}

std::istream &operator>>(std::istream &stream, int2048 &V) {
  // 实现输入运算符逻辑
  std::string v_str;
  stream >> v_str;
  V.read(v_str);
}

std::ostream &operator<<(std::ostream &stream, const int2048 &v) {
  // 实现输出运算符逻辑
  if (v.flag == -1) stream << '-';
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  for (int i = v.num_length - 1; i >= 0; i--)
    stream << char('0' + v.val[i / v.kNum] / kPow10[i % v.kNum] % 10);
}

bool operator==(const int2048 &A, const int2048 &B) {
  // 实现等于运算符逻辑
  if (A.flag != B.flag) return false;
  return UnsignedCmp(A, B) == 0;
}

bool operator!=(const int2048 &A, const int2048 &B) {
  // 实现不等于运算符逻辑
  if (A.flag != B.flag) return true;
  return UnsignedCmp(A, B) != 0;
}

bool operator<(const int2048 &A, const int2048 &B) {
  // 实现小于运算符逻辑
  if (A.flag != B.flag) return A.flag < B.flag;
  int cmp = UnsignedCmp(A, B);
  if (A.flag == 1)
    return cmp < 0;
  else
    return cmp > 0;
}

bool operator>(const int2048 &A, const int2048 &B) {
  // 实现大于运算符逻辑
  if (A.flag != B.flag) return A.flag > B.flag;
  int cmp = UnsignedCmp(A, B);
  if (A.flag == 1)
    return cmp > 0;
  else
    return cmp < 0;
}

bool operator<=(const int2048 &A, const int2048 &B) {
  // 实现小于等于运算符逻辑
  if (A.flag != B.flag) return A.flag < B.flag;
  int cmp = UnsignedCmp(A, B);
  if (A.flag == 1)
    return cmp <= 0;
  else
    return cmp >= 0;
}

bool operator>=(const int2048 &A, const int2048 &B) {
  // 实现大于等于运算符逻辑
  if (A.flag != B.flag) return A.flag > B.flag;
  int cmp = UnsignedCmp(A, B);
  if (A.flag == 1)
    return cmp >= 0;
  else
    return cmp <= 0;
}
}  // namespace sjtu
