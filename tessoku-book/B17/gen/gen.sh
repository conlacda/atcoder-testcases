if ! [ -d etc ]; then
    echo "directory 'etc' doe's not exists."
    exit 1
fi
if ! [ -d gen ]; then
    echo "directory 'gen' doe's not exists."
    exit 1
fi
if ! [ -d in ]; then
    echo "directory 'in' doe's not exists."
    exit 1
fi
if ! [ -d out ]; then
    echo "directory 'out' doe's not exists."
    exit 1
fi
rm in/*
rm out/*
cp gen/raw/* in
if ! g++ -std=c++17 -Wall -Wextra -O2 -o gen/gen gen/gen_tatyam.cpp; then
    echo "compile failed."
    exit 1
fi
echo "generating input."
cd in
../gen/gen
cd ..
rm gen/gen
echo "generating output."
for i in in/*; do
    pypy3 sol/ac_tatyam.py < $i > ${i/in/out}
done
echo "validating."
gen/val.sh
