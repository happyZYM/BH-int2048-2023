#!/usr/bin/python3
from os import system
from sys import exit
from random import randint
"""
this script is used to test * operator
"""

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

"""
def_python="a_0,a_1,a_2,a_3,a_4,a_5,a_6,a_7,a_8,a_9=0,0,0,0,0,0,0,0,0,0"


opt_cpp=[]
opt_python=[]

if True:
  for i in range(0,10):
    val=randint(-2**31,2**31-1)
    opt_cpp.append("a_"+str(i)+"="+str(val)+";")
    opt_python.append("a_"+str(i)+"="+str(val))
    opt_cpp.append("a_"+str(i)+".print(); puts(\"\");")
    opt_python.append("print(a_"+str(i)+")")

if True:
  for i in range(10):
    aid=randint(0,9)
    bid=randint(0,9)
    cid=randint(0,9)
    op='*'
    opt_cpp.append("a_"+str(aid)+"=a_"+str(bid)+op+"a_"+str(cid)+";")
    opt_python.append("a_"+str(aid)+"=a_"+str(bid)+op+"a_"+str(cid))
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
    op='*='
    opt_cpp.append("a_"+str(aid)+op+"a_"+str(bid)+";")
    opt_python.append("a_"+str(aid)+op+"a_"+str(bid))
    opt_cpp.append("a_"+str(aid)+".print(); puts(\"\");")
    opt_python.append("print(a_"+str(aid)+")")

sourc_cpp=open("/tmp/2.cpp","w")
print(code_cpp_pre,file=sourc_cpp)
print(def_cpp,file=sourc_cpp)
for opt in opt_cpp:
  print(opt,file=sourc_cpp)
print(code_cpp_suf,file=sourc_cpp)
sourc_cpp.close()
system("g++ /tmp/2.cpp -I /home/happyzym/CSWorkSpace/Proc/BigHomework/BH-int2048-2023/include/ -L /home/happyzym/CSWorkSpace/Proc/BigHomework/BH-int2048-2023/build/src/ -lint2048 -o /tmp/2")
system("/tmp/2 > /tmp/2_cpp.out")

sourc_python=open("/tmp/2.py","w")
print(code_python_pre,file=sourc_python)
print(def_python,file=sourc_python)
for opt in opt_python:
  print(opt,file=sourc_python)
sourc_python.close()
system("chmod +x /tmp/2.py")
system("/tmp/2.py > /tmp/2_python.out")

exit(system("diff -b -B -u /tmp/2_cpp.out /tmp/2_python.out > /tmp/2.diff")//256)