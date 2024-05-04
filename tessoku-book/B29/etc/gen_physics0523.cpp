#include<bits/stdc++.h>
using namespace std;

long long get_rand(long long lim,mt19937_64 &eg){
  return (long long)(eg()%lim);
}

int main(){
  uint_fast64_t seed=649913017849956229;
  int test_num=33;
  mt19937_64 engine(seed);
  for(int cs=1;cs<=test_num;cs++){
    FILE *inp;
    char fn[64];
    sprintf(fn,"test_%02d.txt",cs);
    inp=fopen(fn,"w");

    long long a,b;
    a=1+get_rand(1000000000,engine);
    b=1+get_rand(1000000000000000000,engine);
    if(cs==1){a=1;b=1;}
    else if(cs==2){a=1000000000;b=1000000000000000000;}
    else if(cs==3){a=1;b=1000000000000000000;}
    else if(cs>=26){b=1000000000000000000;}
    fprintf(inp,"%lld %lld\n",a,b);
    fclose(inp);
  }
  return 0;
}
