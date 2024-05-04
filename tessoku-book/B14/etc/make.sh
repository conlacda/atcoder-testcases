echo "start"
g++ generator.cpp -std=c++14 -o generator
g++ solution.cpp -std=c++14 -o solution
./generator

mv *.txt ../in/
mv ../in/score.txt ./

while read file; do
  echo "$file"
  cat ../in/$file | ./solution > ../out/$file
done < <(ls -A -1 ../in)


rm generator
rm solution
