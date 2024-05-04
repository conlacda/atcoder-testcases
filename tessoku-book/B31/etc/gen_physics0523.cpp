#include<bits/stdc++.h>
using namespace std;

long long get_rand(long long lim,mt19937_64 &eg){
  return (long long)(eg()%lim);
}

int main(){
  uint_fast64_t seed=976358247190134231;
  int test_num=33;
  mt19937_64 engine(seed);
  for(int cs=1;cs<=test_num;cs++){
    FILE *inp;
    char fn[64];
    sprintf(fn,"test_%02d.txt",cs);
    inp=fopen(fn,"w");
    long long n;
    if(cs==1){n=1;}
    else if(cs==2){n=2;}
    else if(cs==3){n=1000000000000;}
    else if(cs<=18){
      long long md=(cs-3);
      n=15*get_rand(1000000000000/15,engine)+md;
    }
    else{
      n=1+get_rand(1000000000000,engine);
    }
    fprintf(inp,"%lld\n",n);
    fclose(inp);
  }
  return 0;
}
