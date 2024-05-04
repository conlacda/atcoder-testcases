#include<bits/stdc++.h>
using namespace std;

long long get_rand(long long lim,mt19937_64 &eg){
  return (long long)(eg()%lim);
}

vector<int> solve(vector<int> a){
  vector<int> dp(100005,0);
  dp[0]=-1;
  for(int i=1;i<100005;i++){
    dp[i]=-1;
    for(auto &nx : a){
      if((i-nx)<0){continue;}
      if(dp[i-nx]==-1){dp[i]=1;}
    }
  }
  return dp;
}

int main(){
  uint_fast64_t seed=976358247190134232;
  int test_num=84;
  mt19937_64 engine(seed);
  for(int cs=1;cs<=test_num;cs++){
    FILE *inp;
    char fn[64];
    sprintf(fn,"test_%02d.txt",cs);
    inp=fopen(fn,"w");

    int n,k;
    if((cs/2)%7==0){k=1;}
    if((cs/2)%7==1){k=2+get_rand(3,engine);}
    if((cs/2)%7==2){k=5+get_rand(6,engine);}
    if((cs/2)%7==3){k=11+get_rand(15,engine);}
    if((cs/2)%7==4){k=26+get_rand(25,engine);}
    if((cs/2)%7==5){k=51+get_rand(50,engine);}
    if((cs/2)%7==6){k=100;}

    int lim;
    if((cs/2)%6==0){lim=500;}
    if((cs/2)%6==1){lim=1000;}
    if((cs/2)%6==2){lim=5000;}
    if((cs/2)%6==3){lim=10000;}
    if((cs/2)%6==4){lim=50000;}
    if((cs/2)%6==5){lim=100000;}

    vector<int> arr(lim);
    for(int i=0;i<lim;i++){arr[i]=i+1;}
    shuffle(arr.begin(),arr.end(),engine);

    vector<int> a;
    for(int i=0;i<k;i++){a.push_back(arr[i]);}

    vector<int> dp=solve(a);
    vector<int> w,l;
    for(int i=1;i<=100000;i++){
      if(dp[i]==1){w.push_back(i);}
      else{l.push_back(i);}
    }

    if(cs%2){swap(w,l);}
    if(w.empty()){swap(w,l);}

    if(cs%3==0){
      n=w.back();
    }
    else{
      if(get_rand(6,engine)==0){
        n=w[0];
      }
      else{
        n=w[get_rand(w.size(),engine)];
      }
    }

    fprintf(inp,"%d %d\n",n,k);
    for(int i=0;i<k;i++){
      if(i){fprintf(inp," ");}
      fprintf(inp,"%d",a[i]);
    }
    fprintf(inp,"\n");
    fclose(inp);
  }
  return 0;
}
