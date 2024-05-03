#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

typedef unsigned __int128 Hash;

template<class T,Hash base>
class RollingHash{
public:
	vector<Hash> harr,p;
	RollingHash(){
		RollingHash(vector<T>{});
	}
	RollingHash(vector<T> src){
		p.resize(src.size()+1);
		harr.resize(src.size());
		for(int i = 0 ; i < src.size() ; i++){
			harr[i] = (i>0?harr[i-1]:0) * base + src[i];
		}
		p[0] = 1;
		for(int i = 1 ; i < p.size() ; i++){
			p[i] = p[i-1] * base;
		}
	}
	size_t size() const{
		return harr.size();
	}

	T operator[](int i) const{
		assert(i<size());
		return sub(i,i+1);
	}
	
	// [l,r)
	Hash sub(int l,int r) const{
		if( l >= r ) return 0;
		return harr[r-1] - (l?harr[l-1] * p[r-l]:0);
	}
	
	int lcp(int x,int y) const{
		int l = 0, r = min(harr.size()-x,harr.size()-y);
		while( l != r ){
			int m = (l+r+1)/2;
			if( sub(x,x+m) == sub(y,y+m) ) l = m;
			else r = m-1;
		}
		return l;
	}
	RollingHash<T,base> & operator += (const RollingHash<T,base> &b){
		assert(&(*this) != &b);
		if( size() == 0 ){
			*this = b;
			
		}else{
			Hash offset = harr[size()-1];
			for(int i = 0 ; i < b.size() ; i++){
				harr.push_back(offset*b.p[i+1] + b.harr[i]);
				p.push_back(p.back()*base);
			}
		}
		return *this;
	}
	void resize(int s){
		
		assert( s <= size() );
		p.resize(s+1);
		harr.resize(s);
	}
	int lcp(const RollingHash<T,base> &b){
		int l = 0, r = min(size(),b.size());
		while( l != r ){
			int m = (l+r+1)/2;
			if( sub(0,m) == b.sub(0,m) ) l = m;
			else r = m-1;
		}
		return l;
	}
	int compare(const RollingHash<T,base> &b) const{
		int len = lcp(b);
		if( len == min(size(),b.size()) ){
			return size() == b.size() ? 0 : (size() > b.size() ? +1 : -1);
		}
		if( (*this)[len] == b[len] ) return 0;
		else return (*this)[len] == b[len] ? -1 : 1;
	}
	
	bool operator < (const RollingHash<T,base> &b) const{
		return compare(b) == -1;
	}
	bool operator == (const RollingHash<T,base> &b) const{
		return compare(b) == 0;
	}
	bool operator > (const RollingHash<T,base> &b) const{
		return compare(b) == 1;
	}
};

void output(const RollingHash<char,8999> &rh){
	for(int i = 0 ; i < rh.size() ; i++)
		cout << rh[i];
	cout << endl;
}

int N,K;

vector<vector<char>> can;
RollingHash<char,8999> rh[5010];
int check(int x,int k){
	if( K == k ) return 1;
	if( k > K ) return 0;
	if( x > N ) return 0;
	if( can[x][k] != -1 ) return can[x][k];
	return can[x][k] = check(x+1,k+rh[x].size()) || check(x+1,k);
}
bool dp_fill[40010];
RollingHash<char,8999> dp_content;

int lcp(const RollingHash<char,8999> &X,int x,const RollingHash<char,8999> &Y,int y){
	int l = 0, r = min(X.size()-x,Y.size()-y);
	while( l != r ){
		int m = (l+r+1)/2;
		if( X.sub(x,x+m) == Y.sub(y,y+m) ) l = m;
		else r = m-1;
	}
	return l;
}


int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin >> N >> K;
	can = vector<vector<char>>(N+1,vector<char>(K+1,-1));
	
	for(int i = 0 ; i < N ; i++){
		string s;
		cin >> s;
		rh[i] = RollingHash<char,8999>(vector<char>(s.begin(),s.end()));
	}
	dp_fill[0] = true;
	for(int i = 0 ; i < N ; i++){
		for(int j = K ; j >= rh[i].size()  ; j--){
			if( !check(i+1,j) ) continue;
			if( !dp_fill[j - rh[i].size()] or j - rh[i].size() > dp_content.size()) continue;
			
			int l = lcp(dp_content,j-rh[i].size(),rh[i],0);
			int u = min(dp_content.size()-(j-rh[i].size()),rh[i].size());
			
			if( (l == u and j > dp_content.size()) or (l < u and dp_content[j-rh[i].size()+l] > rh[i][l]) ){
				for(int k = j - rh[i].size() + l+1 ; k <= dp_content.size() ; k++)
						dp_fill[k] = false;
				dp_content.resize(j - rh[i].size());
				dp_content += rh[i];
				dp_fill[j] = true;
			}else if( l == rh[i].size() ){
				dp_fill[j] = true;
			}
		}
		//cout << i << ": ";
		//for(int j = 0 ; j <= K ; j++) if( dp_fill[j] ) cout << j << " ";
		//cout << endl;
	}
	output(dp_content);
}
