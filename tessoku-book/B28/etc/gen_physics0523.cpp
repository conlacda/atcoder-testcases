#include<bits/stdc++.h>
using namespace std;

long long get_rand(long long lim,mt19937_64 &eg){
  return (long long)(eg()%lim);
}

int main(){
  uint_fast64_t seed=915047188963222074;
  int test_num=8;
  mt19937_64 engine(seed);
  for(int cs=1;cs<=test_num;cs++){
    FILE *inp;
    char fn[64];
    sprintf(fn,"test_%02d.txt",cs);
    inp=fopen(fn,"w");
    int n=3+get_rand(10000000-2,engine);
    if(cs==1){n=3;}
    else if(cs==8){n=10000000;}
    fprintf(inp,"%d\n",n);
    fclose(inp);
  }
  return 0;
}
