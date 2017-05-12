#!/bin/sh
python patcher.py < test1.c > t1.cpp
g++ -g -fpermissive patch.cpp t1.cpp -o t1 && gdb -ex run ./t1