#!/bin/bash
g++ -std=gnu++17 val_e869120.cpp -O2
for i in $( ls ../in ); do
 echo $i
 # nkf -Lu ../in/$i > ./tmp_.txt
 sed 's/\r//g' ../in/$i > tmp_.txt
 ./a.exe < tmp_.txt
 cp tmp_.txt ../in/$i
 rm tmp_.txt
 #cat ../out/$i
done
