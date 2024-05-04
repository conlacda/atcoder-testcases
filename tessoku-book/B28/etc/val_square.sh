g++ -std=gnu++17 -Wall -O2 -g val_square.cpp

for i in $( ls ../in )
do
	echo $i
	sed 's/\r//g' ../in/$i > tmp_.txt
	./a.out < tmp_.txt
	cp tmp_.txt ../in/$i
	rm tmp_.txt
done
