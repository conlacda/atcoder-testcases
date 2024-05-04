#include<bits/stdc++.h>
using namespace std;

long long get_rand(long long lim,mt19937_64 &eg){
  return (long long)(eg()%lim);
}

int main(){
  uint_fast64_t seed=976358247190134491;
  int test_num=4;
  mt19937_64 engine(seed);
  for(int cs=1;cs<=test_num;cs++){
    FILE *inp;
    char fn[64];

    int n;
    if(cs==1){n=2;}
    if(cs==2){n=100;}
    if(cs==3){n=10000;}
    if(cs==4){n=1000000;}
    sprintf(fn,"%d.txt",n);

    inp=fopen(fn,"w");
    fprintf(inp,"%d\n",n);
    fclose(inp);
  }
  return 0;
}
