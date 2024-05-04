#include<bits/stdc++.h>
using namespace std;
using pi=pair<int,int>;

long long get_rand(long long lim,mt19937_64 &eg){
  return (long long)(eg()%lim);
}

vector<int> perm(int n,mt19937_64 &eg){
  vector<int> p;
  for(int i=0;i<n;i++){p.push_back(i+1);}
  shuffle(p.begin(),p.end(),eg);
  return p;
}

int main(){
  uint_fast64_t seed=915047188963222089;
  int test_num=28;
  mt19937_64 engine(seed);
  for(int cs=1;cs<=test_num;cs++){
    FILE *inp;
    char fn[64];
    sprintf(fn,"test_%02d.txt",cs);
    inp=fopen(fn,"w");
    int n,m;
    vector<pair<int,int>> vp;
    if(cs==1){n=1;}
    if(cs==2){n=100000;}
    if(cs==3){
      n=100000;
      for(int i=1;i<n;i++){vp.push_back({i-1,i});}
    }
    if(cs==4){
      n=100000;
      for(int i=0;i<50000;i++){
        vp.push_back({i,(i+1)%50000});
        vp.push_back({50000+i,50000+(i+1)%50000});
      }
    }
    if(cs==5){
      n=100000;
      for(int i=1;i<n;i++){vp.push_back({0,i});}
    }
    if(cs==6){
      n=100000;
      for(int i=1;i<(n-1);i++){vp.push_back({0,i});}
      vp.push_back({1,2});
    }
    if(cs==7){
      n=447;
      for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){vp.push_back({i,j});}
      }
    }
    if(cs==8){
      n=632;
      for(int i=0;i<316;i++){
        for(int j=i+1;j<316;j++){
          vp.push_back({i,j});
          vp.push_back({316+i,316+j});
        }
      }
    }
    if(cs>=9){
      n=10000;
      m=48000+get_rand(10000,engine);
      set<pair<int,int>> st;
      while(st.size()<m){
        int u=get_rand(n,engine);
        int v=get_rand(n,engine);
        if(u==v){continue;}
        if(u>v){swap(u,v);}
        st.insert({u,v});
      }
      for(auto &nx : st){
        vp.push_back(nx);
      }
    }

    shuffle(vp.begin(),vp.end(),engine);
    m=vp.size();
    fprintf(inp,"%d %d\n",n,m);
    vector<int> p=perm(n,engine);
    for(auto &nx : vp){
      int u=p[nx.first];
      int v=p[nx.second];
      fprintf(inp,"%d %d\n",min(u,v),max(u,v));
    }
    fclose(inp);
  }
  return 0;
}
