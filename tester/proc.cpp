#include"int2048.h"
int main()
{
  using namespace sjtu;
  int2048 a("123456789");
  a.print(); puts("");
  a.LeftMoveBy(17);
  a.print(); puts("");
  a.RightMoveBy(17);
  a.print(); puts("");
  return 0;
}