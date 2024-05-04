#include<bits/stdc++.h>
using namespace std;

long long get_rand(long long lim,mt19937_64 &eg){
  return (long long)(eg()%lim);
}

int main(){
  uint_fast64_t seed=915047188963222076;
  int test_num=9;
  mt19937_64 engine(seed);
  for(int cs=1;cs<=test_num;cs++){
    FILE *inp;
    char fn[64];
    sprintf(fn,"test_%02d.txt",cs);
    inp=fopen(fn,"w");
    int n=1+get_rand(100000,engine);
    int q=1+get_rand(100000,engine);
    if(cs==1){n=1;q=1;}
    if(cs>=6){n=100000;q=100000;}
    fprintf(inp,"%d %d\n",n,q);

    for(int i=0;i<n;i++){
      if(i){fprintf(inp," ");}
      int v=1+get_rand(10000,engine);
      if(cs==9){v=10000;}
      fprintf(inp,"%d",v);
    }fprintf(inp,"\n");

    for(int i=0;i<q;i++){
      int len=1+get_rand(n,engine);
      if(cs==8){len=90000+get_rand(10000,engine);}
      if(cs==9){len=100000;}
      int l=1+get_rand(n+1-len,engine);
      int r=l+len-1;
      fprintf(inp,"%d %d\n",l,r);
    }

    fclose(inp);
  }
  return 0;
}
