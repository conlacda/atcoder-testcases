import subprocess
from os import listdir

subprocess.call(['g++', 'etc/validator.cpp', '-std=gnu++17', '-o', 'etc/validator'])
for filename in listdir('./in'):
    print(filename)
    subprocess.call(['etc/validator'], stdin=open('in/' + filename))
