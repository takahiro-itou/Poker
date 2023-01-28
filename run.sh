#!/bin/bash

echo "---------- フロップ ----------"  1>&2
time ./Calc5.exe

echo "----------  ターン  ----------"  1>&2
time ./Calc6.exe

echo "----------  リバー  ----------"  1>&2
time ./Calc7.exe
