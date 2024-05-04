if ! [ -d etc ]; then
    echo "directory 'etc' doe's not exists."
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
if ! g++ -std=c++17 -Wall -Wextra -O2 -o val gen/val_tatyam.cpp; then
    echo "compile failed."
    exit 1
fi
for i in in/*; do
    echo $i
    if ! perl -pe "s/\r\n/\n/" $i | ./val; then
        echo "validation failed : $i"
        rm val
        exit 1
    fi
done
rm val
for i in in/*; do
    if ! [ -f ${i/in/out} ]; then
        echo "extra input file : $i"
        exit 1
    fi
done
for i in out/*; do
    if ! [ -f ${i/out/in} ]; then
        echo "extra input file : $i"
        exit 1
    fi
done
echo "validated successfully."