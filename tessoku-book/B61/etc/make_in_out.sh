g++-12 make_input.cpp -omake_input.out -O2 -std=c++1z;
./make_input.out;
rm make_input.out;

g++-12 in_to_out.cpp -oin_to_out.out -O2 -std=c++1z;
for i in `ls ../in`; do
  ./in_to_out.out < ../in/$i > ../out/$i;
done;
rm in_to_out.out;

cd ../task;
python md2atcoder.py ja.md > ja.html
cd ../etc;
cat ../task/ja.html | pbcopy