#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{   
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0; 
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100]; 
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
typedef long long ll;
const int N=1e5+5;
const int M=1e4+5;
int n,m,q,Mod;
int vis[M],p[M];
int gcd(int x,int y){
	if (!y) return x;
	return gcd(y,x%y);
}
inline int lcm(int x,int y){
	return (x*y)/gcd(x,y);
}
namespace seg{
	#define ls (x<<1)
	#define rs (ls|1)
	#define mid ((l+r)>>1)
	bool lp[N<<2];
	int now[N<<2],tag[N<<2];
	ll sum[N<<2][60];
	inline void chk(int x){
		if (p[sum[x][0]]){
			for (int i=1;i<m;++i)
				sum[x][i]=sum[x][i-1]*sum[x][i-1]%Mod;
			now[x]=0,lp[x]=1;
		}else now[x]=lp[x]=0;
	}
	inline void Add(int x,int k){
		tag[x]=(tag[x]+k)%m;
		now[x]=(now[x]+k)%m;
	}
	inline void pushup(int x){
		lp[x]=lp[ls]&lp[rs],now[x]=0;
		if (!lp[x]) sum[x][0]=sum[ls][now[ls]]+sum[rs][now[rs]];
		else{
			int lx=now[ls],rx=now[rs];
			for (int i=0;i<m;++i){
				sum[x][i]=sum[ls][lx]+sum[rs][rx];
				lx=(lx+1)%m,rx=(rx+1)%m;
			}
		}
	}
	inline void pushdown(int x){
		if (tag[x]){
			Add(ls,tag[x]);
			Add(rs,tag[x]);
			tag[x]=0;
		}
	}
	void build(int x,int l,int r){
		if (l==r){
			sum[x][0]=read();
			tag[x]=0,chk(x);
			return;
		}
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(x);
	}
	void update(int x,int l,int r,int L,int R){
		if (L<=l && r<=R && lp[x]){
			Add(x,1);
			return;
		}
		if (l==r){
			sum[x][0]=sum[x][0]*sum[x][0]%Mod;
			chk(x);
			return;
		}
		pushdown(x);
		if (L<=mid) update(ls,l,mid,L,R);
		if (R>mid) update(rs,mid+1,r,L,R);
		pushup(x);
	}
	ll query(int x,int l,int r,int L,int R){
		if (L<=l && r<=R) return sum[x][now[x]];
		ll res=0;
		pushdown(x);
		if (L<=mid) res+=query(ls,l,mid,L,R);
		if (R>mid) res+=query(rs,mid+1,r,L,R);
		return res;
	}
}
using namespace seg;
inline void get_loop(int x){
	for (int i=1,y=x;;++i,y=y*y%Mod){
		if (vis[y]){
			p[y]=i-vis[y];
			break;
		}else vis[y]=i;
	}
	for (int y=x;vis[y];y=y*y%Mod) vis[y]=0;
}
int main(){
	freopen("4105.in","r",stdin);
	freopen("4105.out","w",stdout);
	n=read(),q=read(),Mod=read(),m=1;
	for (int i=0;i<Mod;++i) get_loop(i);
	for (int i=0;i<Mod;++i)
		if (p[i]) m=lcm(p[i],m);
	build(1,1,n);
	while (q--){
		int opt=read(),l=read(),r=read();
		if (opt&1) update(1,1,n,l,r);
		else Print(query(1,1,n,l,r));
	}
	io::flush();
	return 0;
}
