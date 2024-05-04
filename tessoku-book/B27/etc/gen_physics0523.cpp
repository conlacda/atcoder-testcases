#include<bits/stdc++.h>
using namespace std;

long long get_rand(long long lim,mt19937_64 &eg){
  return (long long)(eg()%lim);
}

int main(){
  uint_fast64_t seed=649913017849956227;
  int test_num=36;
  mt19937_64 engine(seed);
  for(int cs=1;cs<=test_num;cs++){
    FILE *inp;
    char fn[64];
    sprintf(fn,"test_%02d.txt",cs);
    inp=fopen(fn,"w");

    long long a,b;
    if(cs==1){a=1;b=1;}
    else if(cs==2){a=999999999;b=1000000000;}
    else if(cs==3){a=1000000000;b=1000000000;}
    else if(cs<=9){
      vector<long long> v={367567200,551350800,698377680,735134400};
      int p,q;
      if(cs==4){p=1;q=2;}
      if(cs==5){p=1;q=3;}
      if(cs==6){p=1;q=4;}
      if(cs==7){p=2;q=3;}
      if(cs==8){p=2;q=4;}
      if(cs==9){p=3;q=4;}
      a=v[p-1];
      b=v[q-1];
      if(cs%2==0){swap(a,b);}
    }
    else if(cs<=18){
      if(cs%3==0){a=1+get_rand(100,engine);}
      if(cs%3==1){a=1+get_rand(10000,engine);}
      if(cs%3==2){a=1+get_rand(100000000,engine);}
      b=a*(1+get_rand((1000000000/a),engine));
      if(cs%2){swap(a,b);}
    }
    else{
      if(cs%3==0){
        a=1+get_rand(100,engine);
        b=1+get_rand(100,engine);
      }
      if(cs%3==1){
        a=1+get_rand(10000,engine);
        b=1+get_rand(10000,engine);
      }
      if(cs%3==2){
        a=1+get_rand(1000000000,engine);
        b=1+get_rand(1000000000,engine);
      }
    }

    fprintf(inp,"%lld %lld\n",a,b);

    fclose(inp);
  }
  return 0;
}
