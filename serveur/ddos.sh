#!/usr/bin/env bash
d=0
n=100

for ((i=$d;$i<$n;i++))
do
   $(./clients localhost $i) &
   echo $i
done;
