#include<bits/stdc++.h>
using namespace std;

long long get_rand(long long lim,mt19937_64 &eg){
  return (long long)(eg()%lim);
}

int main(){
  uint_fast64_t seed=976358247190134233;
  int test_num=40;
  mt19937_64 engine(seed);
  for(int cs=1;cs<=test_num;cs++){
    FILE *inp;
    char fn[64];
    sprintf(fn,"test_%02d.txt",cs);
    inp=fopen(fn,"w");

    int n=1+get_rand(100000,engine);
    if(cs>=21){n=100000;}
    if(cs<=4){n=1;}
    n*=2;

    vector<int> a(n);
    while(1){
      for(int i=0;i<n;i++){
        a[i]=get_rand(1000000000,engine);
        if((cs%5)==0 && get_rand(10,engine)==0){
          if(get_rand(2,engine)){a[i]=0;}
          else{a[i]=999999999;}
        }
      }

      if(cs%2==0){
        int g=0;
        for(int i=0;i<n;i++){g^=a[i];}
        if(g!=0){break;}
      }
      else{
        int g=0;
        for(int i=0;i<n-1;i++){g^=a[i];}
        if(0<=g && g<=999999999){
          a[n-1]=g;break;
        }
      }
    }

    n/=2;
    vector<int> p,q;
    if(cs%5==0){sort(a.begin(),a.end());}
    if(cs%5==1){
      sort(a.begin(),a.end());
      reverse(a.begin(),a.end());
    }

    for(int i=0;i<n;i++){p.push_back(a[i]+1);}
    for(int i=0;i<n;i++){q.push_back(a[n+i]+1);}
    shuffle(p.begin(),p.end(),engine);
    shuffle(q.begin(),q.end(),engine);

    int h=1,w=1;
    for(int i=0;i<n;i++){
      h=max(h,p[i]);
    }
    for(int i=0;i<n;i++){
      w=max(w,q[i]);
    }

    h=h+get_rand(1000000001-h,engine);
    w=w+get_rand(1000000001-w,engine);

    if(get_rand(3,engine)==0){
      h=1000000000;
      w=1000000000;
    }

    fprintf(inp,"%d %d %d\n",n,h,w);
    for(int i=0;i<n;i++){
      fprintf(inp,"%d %d\n",p[i],q[i]);
    }

    fclose(inp);
  }
  return 0;
}
