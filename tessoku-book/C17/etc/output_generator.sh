g++ -std=gnu++17 -Wall -O2 -o model_solution ../sol/ac_square.cpp

for i in "../in/"*; do
	name=$(basename "$i")
	inpath="../in/$name"
	outpath="../out/$name"
	./model_solution < "$inpath" > "$outpath"
done

rm model_solution