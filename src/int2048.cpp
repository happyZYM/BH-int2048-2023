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

#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <utility>

static_assert(sizeof(int) == 4, "sizeof(int) != 4");
static_assert(sizeof(long long) == 8, "sizeof(long long)!=8");
namespace sjtu {
// 构造函数
int2048::int2048() {
  // 实现构造函数逻辑
  buf_length = kDefaultLength;
  val = new int[buf_length]();
  flag = 1;
  num_length = 1;
}
int2048::~int2048() {
  // 实现析构函数逻辑
  if (val != nullptr) delete[] val;
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
  input_value.buf_length = kDefaultLength;
  input_value.flag = 1;
  input_value.num_length = 1;
  input_value.val = new int[input_value.buf_length]();
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
  char *buf = new char[num_length + 5];
  char *p = buf;
  if (flag == -1) *p++ = '-';
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  for (int i = num_length - 1; i >= 0; i--)
    *p++ = char('0' + val[i / int2048::kNum] / kPow10[i % int2048::kNum] % 10);
  *p++ = 0;
  std::cout << buf;
  delete[] buf;
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
  int number_of_blocks = (A.num_length + int2048::kNum - 1) / int2048::kNum;
  for (int i = number_of_blocks - 1; i >= 0; i--)
    if (A.val[i] != B.val[i]) return A.val[i] < B.val[i] ? -1 : 1;
  return 0;
}
inline void UnsignedMinus(int2048 &, const int2048 *, bool inverse = false);

inline void UnsignedAdd(int2048 &A, const int2048 *const pB,
                        bool inverse = false) {
  if (&A == pB) throw "UnsignedAdd: A and B are the same object";
  A.ClaimMem(std::max(A.num_length, pB->num_length) + 2);
  if (!inverse) {
    for (int i = 0;
         i < (std::max(A.num_length, pB->num_length) + int2048::kNum - 1) /
                 int2048::kNum;
         i++) {
      if (i < (pB->num_length + int2048::kNum - 1) / int2048::kNum)
        A.val[i] += pB->val[i];
      if (i + 1 < A.buf_length) A.val[i + 1] += A.val[i] / int2048::kMod;
      A.val[i] %= int2048::kMod;
    }
  } else {
    for (int i = (std::max(A.num_length, pB->num_length) + int2048::kNum - 1) /
                     int2048::kNum -
                 1;
         i >= 0; i--) {
      if (i < (pB->num_length + int2048::kNum - 1) / int2048::kNum)
        A.val[i] += pB->val[i];
      if (A.val[i] >= int2048::kMod && i - 1 >= 0) {
        A.val[i - 1] += A.val[i] / int2048::kMod;
        A.val[i] %= int2048::kMod;
      }
    }
  }
  A.num_length = std::max(A.num_length, pB->num_length);
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  if (A.val[A.num_length / int2048::kNum] /
          kPow10[A.num_length % int2048::kNum] >
      0)
    A.num_length++;
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
      if (this->num_length == 1 && this->val[0] == 0) this->flag = 1;
    } else {
      int2048 new_B = std::move(*this);
      *this = B;
      UnsignedMinus(*this, &new_B);
      this->flag = 1;
    }
  }
  if (pB != &B) delete pB;
  return *this;
}

// 返回两个大整数之和
int2048 add(int2048 A, const int2048 &B) {
  // 实现加法逻辑
  return std::move(A.add(B));
}

inline void UnsignedMinus(int2048 &A, const int2048 *const pB, bool inverse) {
  if (&A == pB) throw "UnsignedMinus: A and B are the same object";
  if (!inverse) {
    for (int i = 0; i < (pB->num_length + int2048::kNum - 1) / int2048::kNum;
         i++) {
      A.val[i] -= pB->val[i];
      if (A.val[i] < 0 && i + 1 < A.buf_length) {
        A.val[i] += int2048::kMod;
        A.val[i + 1]--;
      }
    }
  } else {
    int blocks_A = (A.num_length + int2048::kNum - 1) / int2048::kNum;
    int blocks_B = (pB->num_length + int2048::kNum - 1) / int2048::kNum;
    if (blocks_A < blocks_B) A.ClaimMem(blocks_A * int2048::kNum);
    blocks_A = (A.num_length + int2048::kNum - 1) / int2048::kNum;
    for (int i = (pB->num_length + int2048::kNum - 1) / int2048::kNum - 1;
         i >= 0; i--) {
      if (i < blocks_B && i < blocks_A) A.val[i] -= pB->val[i];
      if (i < blocks_A && A.val[i] < 0 && i - 1 >= 0) {
        A.val[i] += int2048::kMod;
        A.val[i - 1]--;
      }
    }
  }
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  int new_length = 0;
  for (int i = 0; i < A.num_length; i++)
    if (A.val[i / int2048::kNum] / kPow10[i % int2048::kNum] > 0)
      new_length = i + 1;
  A.num_length = new_length;
  if (A.num_length == 0) A.num_length = 1;
  A.ClaimMem(A.num_length);
}

// 减去一个大整数
int2048 &int2048::minus(const int2048 &B) {
  // 实现减法逻辑
  const int2048 *pB = &B;
  if (this->flag == B.flag) {
    int cmp = UnsignedCmp(*this, *pB);
    if (cmp >= 0) {
      if (this == &B) pB = new int2048(B);
      UnsignedMinus(*this, pB);
      if (this->num_length == 1 && this->val[0] == 0) this->flag = 1;
    } else {
      int2048 new_B = std::move(*this);
      *this = B;
      UnsignedMinus(*this, &new_B);
      this->flag = -this->flag;
      if (this->num_length == 1 && this->val[0] == 0) this->flag = 1;
    }
  } else {
    if (this == &B) pB = new int2048(B);
    UnsignedAdd(*this, pB);
  }
  if (pB != &B) delete pB;
  return *this;
}

// 返回两个大整数之差
int2048 minus(int2048 A, const int2048 &B) {
  // 实现减法逻辑
  return std::move(A.minus(B));
}

// 运算符重载

int2048 int2048::operator+() const {
  // 实现一元加法逻辑
  return std::move(int2048(*this));
}

int2048 int2048::operator-() const {
  // 实现一元减法逻辑
  int2048 ret(*this);
  if (!(ret.num_length == 1 && ret.val[0] == 0)) ret.flag = -ret.flag;
  return std::move(ret);
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
  B.buf_length = kDefaultLength;
  B.flag = 1;
  B.num_length = 1;
  B.val = new int[B.buf_length]();
  return *this;
}

int2048 &int2048::operator+=(const int2048 &B) {
  // 实现复合加法逻辑
  return this->add(B);
}

int2048 operator+(int2048 A, const int2048 &B) {
  // 实现加法逻辑
  A.add(B);
  return std::move(A);
}

int2048 &int2048::operator-=(const int2048 &B) {
  // 实现复合减法逻辑
  return this->minus(B);
}

int2048 operator-(int2048 A, const int2048 &B) {
  // 实现减法逻辑
  A.minus(B);
  return std::move(A);
}
__int128_t int2048::QuickPow(__int128_t v, long long q) {
  __int128_t ret = 1;
  v %= int2048::kNTTMod;
  while (q > 0) {
    if (q & 1) (ret *= v) %= int2048::kNTTMod;
    (v *= v) %= int2048::kNTTMod;
    q >>= 1;
  }
  return ret;
}
void int2048::NTTTransform(__int128_t *a, int NTT_blocks,
                           bool inverse = false) {
  for (int i = 1, j = 0; i < NTT_blocks; i++) {
    int bit = NTT_blocks >> 1;
    while (j >= bit) {
      j -= bit;
      bit >>= 1;
    }
    j += bit;
    if (i < j) std::swap(a[i], a[j]);
  }
  for (int len = 2; len <= NTT_blocks; len <<= 1) {
    __int128_t wlen = QuickPow(int2048::kNTTRoot, (int2048::kNTTMod - 1) / len);
    if (inverse) wlen = QuickPow(wlen, int2048::kNTTMod - 2);
    for (int i = 0; i < NTT_blocks; i += len) {
      __int128_t w = 1;
      for (int j = 0; j < len / 2; j++) {
        __int128_t u = a[i + j], v = a[i + j + len / 2] * w % int2048::kNTTMod;
        a[i + j] = (u + v) % int2048::kNTTMod;
        a[i + j + len / 2] = (u - v + int2048::kNTTMod) % int2048::kNTTMod;
        (w *= wlen) %= int2048::kNTTMod;
      }
    }
  }
  if (inverse) {
    __int128_t inv = QuickPow(NTT_blocks, int2048::kNTTMod - 2);
    for (int i = 0; i < NTT_blocks; i++) (a[i] *= inv) %= int2048::kNTTMod;
  }
}
inline void UnsignedMultiply(int2048 &A, const int2048 *pB,
                             bool inverse = false) {
  if (&A == pB) throw "UnsignedMultiply: A and B are the same object";
  int blocks_of_A = ((A.num_length + int2048::kNum - 1) / int2048::kNum);
  int blocks_of_B = ((pB->num_length + int2048::kNum - 1) / int2048::kNum);
  int max_blocks = blocks_of_A + blocks_of_B;
  int NTT_blocks = 1;
  while (NTT_blocks < (max_blocks << 1)) NTT_blocks <<= 1;
  __int128_t *pDA = new __int128_t[NTT_blocks]();
  __int128_t *pDB = new __int128_t[NTT_blocks]();
  __int128_t *pDC = new __int128_t[NTT_blocks]();
  for (int i = 0; i < blocks_of_A; i++) {
    pDA[i << 1] = A.val[i] % int2048::kNTTBlockBase;
    pDA[(i << 1) | 1] = A.val[i] / int2048::kNTTBlockBase;
  }
  for (int i = 0; i < blocks_of_B; i++) {
    pDB[i << 1] = pB->val[i] % int2048::kNTTBlockBase;
    pDB[(i << 1) | 1] = pB->val[i] / int2048::kNTTBlockBase;
  }
  A.NTTTransform(pDA, NTT_blocks);
  A.NTTTransform(pDB, NTT_blocks);
  for (int i = 0; i < NTT_blocks; i++)
    pDC[i] = (pDA[i] * pDB[i]) % int2048::kNTTMod;
  A.NTTTransform(pDC, NTT_blocks, true);
  if (!inverse) {
    for (int i = 0; i < NTT_blocks - 1; i++) {
      pDC[i + 1] += pDC[i] / int2048::kNTTBlockBase;
      pDC[i] %= int2048::kNTTBlockBase;
    }
    if (pDC[NTT_blocks - 1] >= int2048::kNTTBlockBase)
      throw "UnsignedMultiply: NTT result overflow";
  } else {
    for (int i = NTT_blocks - 1; i > 0; i--) {
      if (i - 1 >= 0) pDC[i - 1] += pDC[i] / int2048::kNTTBlockBase;
      pDC[i] %= int2048::kNTTBlockBase;
    }
    if (pDC[0] >= int2048::kNTTBlockBase)
      throw "UnsignedMultiply: NTT result overflow";
  }
  int flag_store = A.flag;
  A.ClaimMem(NTT_blocks * 4);
  memset(A.val, 0, A.buf_length * sizeof(int));
  for (int i = 0; i < NTT_blocks / 2; i++) {
    A.val[i] = pDC[(i << 1) | 1] * int2048::kNTTBlockBase + pDC[i << 1];
  }
  A.num_length = NTT_blocks * 4;
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  while (A.val[(A.num_length - 1) / int2048::kNum] /
             kPow10[(A.num_length - 1) % int2048::kNum] ==
         0) {
    A.num_length--;
    if (A.num_length == 0) {
      A.num_length = 1;
      break;
    }
  }
  delete[] pDA;
  delete[] pDB;
  delete[] pDC;
}

int2048 &int2048::Multiply(const int2048 &B) {
  // 实现复合乘法逻辑
  const int2048 *pB = &B;
  if (this == &B) pB = new int2048(B);
  if ((this->num_length == 1 && this->val[0] == 0) ||
      (pB->num_length == 1 && pB->val[0] == 0)) {
    *this = std::move(int2048(0));
    if (pB != &B) delete pB;
    return *this;
  }
  this->flag = this->flag * pB->flag;
  UnsignedMultiply(*this, pB);
  if (pB != &B) delete pB;
  return *this;
}

int2048 Multiply(int2048 A, const int2048 &B) {
  // 实现乘法逻辑
  return std::move(A.Multiply(B));
}

int2048 &int2048::operator*=(const int2048 &B) {
  // 实现复合乘法逻辑
  return this->Multiply(B);
}

int2048 operator*(int2048 A, const int2048 &B) {
  // 实现乘法逻辑
  A.Multiply(B);
  return std::move(A);
}

void int2048::RightMoveBy(int L) {
  if (L >= this->num_length) {
    this->num_length = 1;
    this->val[0] = 0;
    return;
  }
  int big_move = L / int2048::kNum;
  int small_move = L % int2048::kNum;
  for (int i = 0; i < this->buf_length - big_move; i++) {
    this->val[i] = this->val[i + big_move];
  }
  for (int i = this->buf_length - big_move; i < this->buf_length; i++) {
    this->val[i] = 0;
  }
  this->num_length -= big_move * int2048::kNum;
  if (small_move == 0) return;
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  for (int i = 0; i < this->buf_length; i++) {
    this->val[i] /= kPow10[small_move];
    if (i + 1 < this->buf_length) {
      this->val[i] += this->val[i + 1] % kPow10[small_move] *
                      kPow10[int2048::kNum - small_move];
    }
  }
  this->num_length -= small_move;
}

inline void UnsignedDivide(int2048 &A, const int2048 *pB) {
  int L1 = A.num_length, L2 = pB->num_length;
  if (&A == pB) throw "UnsignedDivide: A and B are the same object";
  if (2 * L1 - L2 - 1 < 0) {
    A = std::move(int2048(0));
    return;
  }
  if (UnsignedCmp(A, *pB) < 0) {
    A = std::move(int2048(0));
    return;
  }
  /**
   * Now pre-process has done. We can start the main algorithm:
   * 1. Convert B to scientific counting method and process the index.
   * 2. In the state of reversing, calculate 1/B' using Newton-Raphson method.
   * 3. Reverse the iterative results again and calculate the answer.
   *
   * Warning: in reversed mode, num_length has no exact meaning, just operate a
   * block as a whole
   */
  int2048 origin_A(A);
  int pow_A = (L1 + int2048::kNum - 1) / int2048::kNum - 1;
  int pow_B = (L2 + int2048::kNum - 1) / int2048::kNum - 1;
  // pow_B+1 is the number of blocks (with number) of B'
  int2048 inverse_B(*pB);
  for (int i = 0; (i << 1) < (pow_B + 1); i++)
    std::swap(inverse_B.val[i], inverse_B.val[pow_B - i]);
  int2048 x(int2048::kMod);
  assert(x.val[1] == 1);
  int *store[2];
  store[0] = new int[pow_A + 5]();
  store[1] = new int[pow_A + 5]();
  int tot = 0;
  for (int i = 0; i < pow_A + 1; i++) {
    store[0][i] = A.val[i];
    store[1][i] = -1;
  }
  while (true) {
    int2048 invsere_two(2), tmp_x(x);
    UnsignedMultiply(tmp_x, &inverse_B, true);
    UnsignedMinus(invsere_two, &tmp_x, true);
    UnsignedMultiply(x, &invsere_two, true);
    /**
     * now x is the next x, store[tot] stores last x, store[tot^1] stores the x
     * previous to store[x]
     */
    int blocks_of_x = (x.num_length + int2048::kNum - 1) / int2048::kNum;
    if (blocks_of_x > pow_A + 3) {
      x.ClaimMem((pow_A + 3) * int2048::kNum);
      blocks_of_x = pow_A + 3;
    }
    bool pre_same = true, pre_pre_same = true;
    for (int i = 0; i < pow_A + 3; i++) {
      if (store[tot][i] != (i < blocks_of_x ? x.val[i] : 0)) {
        pre_same = false;
        break;
      }
    }
    for (int i = 0; i < pow_A + 3; i++) {
      if (store[tot ^ 1][i] != (i < blocks_of_x ? x.val[i] : 0)) {
        pre_pre_same = false;
        break;
      }
    }
    if (pre_pre_same || pre_same) break;
    tot ^= 1;
    for (int i = 0; i < pow_A + 3; i++) {
      if (i < blocks_of_x)
        store[tot][i] = x.val[i];
      else
        store[tot][i] = 0;
    }
  }
  delete[] store[0];
  delete[] store[1];
  /**
   * Now reverse x back.
   */
  int blocks_of_x = (x.num_length + int2048::kNum - 1) / int2048::kNum;
  int pow_x = blocks_of_x - 1;
  for (int i = 0; i < blocks_of_x / 2; i++)
    std::swap(x.val[i], x.val[blocks_of_x - i - 1]);
  x.num_length = blocks_of_x * int2048::kNum;
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  /*Now get the accurate x.num_length for future computing*/
  while (x.num_length > 0 &&
         x.val[(x.num_length - 1) / int2048::kNum] /
                 kPow10[(x.num_length - 1) % int2048::kNum] ==
             0)
    x.num_length--;
  UnsignedMultiply(A, &x);
  A.RightMoveBy((pow_B + pow_x) * int2048::kNum);
  /*Now we begin to process error*/
  int2048 tmp(*pB), kOne(1);
  UnsignedMultiply(tmp, &A);
  while (UnsignedCmp(origin_A, tmp) < 0) {
    UnsignedMinus(A, &kOne);
    UnsignedMinus(tmp, pB);
  }
  UnsignedMinus(origin_A, &tmp);
  while (UnsignedCmp(origin_A, *pB) >= 0) {
    UnsignedAdd(A, &kOne);
    UnsignedMinus(origin_A, pB);
  }
}
int2048 &int2048::Divide(const int2048 &B) {
  if (this == &B) {
    *this = std::move(int2048(1));
    return *this;
  }
  if (B.num_length == 1 && B.val[0] == 0) {
    *this = std::move(int2048(0));
    return *this;
    // throw "Divide: divide by zero";
  }
  int2048 origin_A(*this);
  int flag_store = this->flag * B.flag;
  UnsignedDivide(*this, &B);
  this->flag = flag_store;
  if (this->flag == -1) {
    if (origin_A != (*this) * B) {
      *this -= 1;
    }
  }
  if (this->num_length == 1 && this->val[0] == 0) this->flag = 1;
  return *this;
}
int2048 Divide(int2048 A, const int2048 &B) {
  A.Divide(B);
  return std::move(A);
}

int2048 &int2048::operator/=(const int2048 &B) {
  // 实现复合除法逻辑
  return this->Divide(B);
}

int2048 operator/(int2048 A, const int2048 &B) {
  // 实现除法逻辑
  A.Divide(B);
  return std::move(A);
}

int2048 &int2048::operator%=(const int2048 &B) {
  // 实现复合取模逻辑
  int2048 C(*this);
  C.Divide(B);
  this->minus(C.Multiply(B));
  return *this;
}

int2048 operator%(int2048 A, const int2048 &B) {
  // 实现取模逻辑
  int2048 C(A);
  C.Divide(B);
  A.minus(C.Multiply(B));
  return std::move(A);
}

std::istream &operator>>(std::istream &stream, int2048 &V) {
  // 实现输入运算符逻辑
  std::string v_str;
  stream >> v_str;
  V.read(v_str);
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const int2048 &v) {
  // 实现输出运算符逻辑
  char *buf = new char[v.num_length + 5];
  char *p = buf;
  if (v.flag == -1) *p++ = '-';
  const static int kPow10[9] = {1,      10,      100,      1000,     10000,
                                100000, 1000000, 10000000, 100000000};
  for (int i = v.num_length - 1; i >= 0; i--)
    *p++ =
        char('0' + v.val[i / int2048::kNum] / kPow10[i % int2048::kNum] % 10);
  *p++ = 0;
  stream << buf;
  delete[] buf;
  return stream;
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