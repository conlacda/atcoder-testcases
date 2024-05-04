#include<bits/stdc++.h>
using namespace std;

long long get_rand(long long lim,mt19937_64 &eg){
  return (long long)(eg()%lim);
}

int main(){
  uint_fast64_t seed=915047188963222075;
  int test_num=8;
  mt19937_64 engine(seed);
  for(int cs=1;cs<=test_num;cs++){
    FILE *inp;
    char fn[64];
    sprintf(fn,"test_%02d.txt",cs);
    inp=fopen(fn,"w");
    int a=1+get_rand(100,engine);
    int b=1+get_rand(1000000000,engine);
    if(cs==1){a=1;b=1;}
    if(cs>=5){b=1000000000;}
    if(cs==8){a=100;}
    fprintf(inp,"%d %d\n",a,b);
    fclose(inp);
  }
  return 0;
}
