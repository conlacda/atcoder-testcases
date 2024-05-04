#include<bits/stdc++.h>
using namespace std;

long long get_rand(long long lim,mt19937_64 &eg){
  return (long long)(eg()%lim);
}

int mex(vector<int> a){
  int n=a.size();
  vector<int> bk(n+1,0);
  for(auto &nx : a){
    if(nx<=n){bk[nx]++;}
  }

  for(int i=0;;i++){
    if(bk[i]==0){return i;}
  }
}

int main(){
  uint_fast64_t seed=976358247190134234;
  int test_num=40;
  mt19937_64 engine(seed);
  for(int cs=1;cs<=test_num;cs++){
    FILE *inp;
    char fn[64];
    sprintf(fn,"test_%02d.txt",cs);
    inp=fopen(fn,"w");

    long long n,x=2,y=3;

    n=1+get_rand(100000,engine);
    if(cs<=4){n=1;}
    else if(cs>=29){n=100000;}
    vector<int> g={0,0,1,1,2};
    vector<long long> a(n);
    while(1){
      for(int i=0;i<n;i++){
        if(cs%5==0){a[i]=1+get_rand(5,engine);}
        if(cs%5==1){a[i]=(1000000000000000000-4)+get_rand(5,engine);}
        a[i]=1+get_rand(1000000000000000000,engine);
      }
      int gg=0;
      for(auto &nx : a){gg^=g[nx%5];}

      if(cs%2!=0 && gg!=0){break;}
      if(cs%2==0 && gg==0){break;}
    }

    fprintf(inp,"%lld %lld %lld\n",n,x,y);
    for(int i=0;i<n;i++){
      if(i){fprintf(inp," ");}
      fprintf(inp,"%lld",a[i]);
    }fprintf(inp,"\n");
    fclose(inp);
  }
  return 0;
}
