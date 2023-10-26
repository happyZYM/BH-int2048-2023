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
  buf_length = input_value.length() / kNum * kMemAdditionScalar;
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

// 读入一个大整数
void int2048::read(const std::string &input_value) {
  delete[] val;
  buf_length = input_value.length() / kNum * kMemAdditionScalar;
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

// 加上一个大整数
int2048 &int2048::add(const int2048 &) {
  // 实现加法逻辑
}

// 返回两个大整数之和
int2048 add(int2048, const int2048 &) {
  // 实现加法逻辑
}

// 减去一个大整数
int2048 &int2048::minus(const int2048 &) {
  // 实现减法逻辑
}

// 返回两个大整数之差
int2048 minus(int2048, const int2048 &) {
  // 实现减法逻辑
}

// 运算符重载

int2048 int2048::operator+() const {
  // 实现一元加法逻辑
}

int2048 int2048::operator-() const {
  // 实现一元减法逻辑
}

int2048 &int2048::operator=(const int2048 &) {
  // 实现赋值运算符逻辑
}

int2048 &int2048::operator+=(const int2048 &) {
  // 实现复合加法逻辑
}

int2048 operator+(int2048, const int2048 &) {
  // 实现加法逻辑
}

int2048 &int2048::operator-=(const int2048 &) {
  // 实现复合减法逻辑
}

int2048 operator-(int2048, const int2048 &) {
  // 实现减法逻辑
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

std::istream &operator>>(std::istream &, int2048 &) {
  // 实现输入运算符逻辑
}

std::ostream &operator<<(std::ostream &, const int2048 &) {
  // 实现输出运算符逻辑
}

bool operator==(const int2048 &, const int2048 &) {
  // 实现等于运算符逻辑
}

bool operator!=(const int2048 &, const int2048 &) {
  // 实现不等于运算符逻辑
}

bool operator<(const int2048 &, const int2048 &) {
  // 实现小于运算符逻辑
}

bool operator>(const int2048 &, const int2048 &) {
  // 实现大于运算符逻辑
}

bool operator<=(const int2048 &, const int2048 &) {
  // 实现小于等于运算符逻辑
}

bool operator>=(const int2048 &, const int2048 &) {
  // 实现大于等于运算符逻辑
}
}  // namespace sjtu
