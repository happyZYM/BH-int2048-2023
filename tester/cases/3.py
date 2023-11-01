#!/usr/bin/python3
from os import system
from sys import exit
from random import randint
import sys
"""
this script is used to test * operator
"""

sys.set_int_max_str_digits(10000000)

code_cpp_pre="""
#include<iostream>
#include "/home/happyzym/CSWorkSpace/Proc/BigHomework/BH-int2048-2023/include/int2048.h"
using namespace std;
using namespace sjtu;
int main()
{
"""
code_cpp_suf="""
return 0;
}
"""
def_cpp="int2048 a_0(0),a_1(0),a_2(0),a_3(0),a_4(0),a_5(0),a_6(0),a_7(0),a_8(0),a_9(0);"


code_python_pre="""#!/usr/bin/python3
import sys
sys.set_int_max_str_digits(10000000)
"""
def_python="a_0,a_1,a_2,a_3,a_4,a_5,a_6,a_7,a_8,a_9=0,0,0,0,0,0,0,0,0,0"


opt_cpp=[]
opt_python=[]

if True:
  for i in range(0,10):
    val=randint(-10**18,10**18)
    if randint(0,1)==0:
      val=randint(-10**2,10**2)
    opt_cpp.append("a_"+str(i)+"=int2048(\""+str(val)+"\");")
    opt_python.append("a_"+str(i)+"="+str(val))
    opt_cpp.append("a_"+str(i)+".print(); puts(\"\");")
    opt_python.append("print(a_"+str(i)+")")

if True:
  for i in range(10):
    aid=randint(0,9)
    bid=randint(0,9)
    cid=randint(0,9)
    oplist=['+','-','*','/']
    op=oplist[randint(0,3)]
    bflag="+"
    if randint(0,1)==0:
      bflag="-"
    cflag="+"
    if randint(0,1)==0:
      cflag="-"
    opt_cpp.append("a_"+str(aid)+"=("+bflag+"a_"+str(bid)+")"+op+"("+cflag+"a_"+str(cid)+");")
    if op=='/':
      opt_python.append("try:")
      opt_python.append("  a_"+str(aid)+"=("+bflag+"a_"+str(bid)+")"+op+op+"("+cflag+"a_"+str(cid)+")")
      opt_python.append("except ZeroDivisionError:")
      opt_python.append("  a_"+str(aid)+"=0")
    else:
      opt_python.append("a_"+str(aid)+"=("+bflag+"a_"+str(bid)+")"+op+"("+cflag+"a_"+str(cid)+")")
    opt_cpp.append("a_"+str(aid)+".print(); puts(\"\");")
    opt_python.append("print(a_"+str(aid)+")")
    opt_cpp.append("a_"+str(bid)+".print(); puts(\"\");")
    opt_python.append("print(a_"+str(bid)+")")
    opt_cpp.append("a_"+str(cid)+".print(); puts(\"\");")
    opt_python.append("print(a_"+str(cid)+")")

if True:
  for i in range(10):
    aid=randint(0,9)
    bid=randint(0,9)
    oplist=['+','-','*','/']
    op=oplist[randint(0,3)]
    opt_cpp.append("a_"+str(aid)+op+"=a_"+str(bid)+";")
    if op=='/':
      opt_python.append("try:")
      opt_python.append("  a_"+str(aid)+op+op+"=a_"+str(bid))
      opt_python.append("except ZeroDivisionError:")
      opt_python.append("  a_"+str(aid)+"=0")
    else:
      opt_python.append("a_"+str(aid)+op+"=a_"+str(bid))
    opt_cpp.append("a_"+str(aid)+".print(); puts(\"\");")
    opt_python.append("print(a_"+str(aid)+")")

sourc_cpp=open("/tmp/3.cpp","w")
print(code_cpp_pre,file=sourc_cpp)
print(def_cpp,file=sourc_cpp)
for opt in opt_cpp:
  print(opt,file=sourc_cpp)
print(code_cpp_suf,file=sourc_cpp)
sourc_cpp.close()
system("g++ /tmp/3.cpp -I /home/happyzym/CSWorkSpace/Proc/BigHomework/BH-int2048-2023/include/ -L /home/happyzym/CSWorkSpace/Proc/BigHomework/BH-int2048-2023/build/src/ -lint2048 -g -fsanitize=address -o /tmp/3")
system("/tmp/3 > /tmp/3_cpp.out")

sourc_python=open("/tmp/3.py","w")
print(code_python_pre,file=sourc_python)
print(def_python,file=sourc_python)
for opt in opt_python:
  print(opt,file=sourc_python)
sourc_python.close()
system("chmod +x /tmp/3.py")
system("/tmp/3.py > /tmp/3_python.out")

exit(system("diff -b -B -u /tmp/3_cpp.out /tmp/3_python.out > /tmp/3.diff")//256)