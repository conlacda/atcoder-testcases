g++ -std=gnu++17 -Wall -O2 -o val_square val_square.cpp

for i in $( ls ../in )
do
	echo $i
	./val_square < ../in/$i
done

rm val_square