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
const int N=(1<<20)+5;
const int Mod=1e9+7;
inline int ad(int x,int y){
	x+=y;
	if (x>=Mod) x-=Mod;
	if (x<0) x+=Mod;
	return x;
}
int n,m,d,ans,pw;
int a[N],g[N],dp[10][N];
int main(){
	freopen("4347.in","r",stdin);
	freopen("4347.out","w",stdout);
	n=read(),d=read();
	for (int i=1;i<=n;++i){
		int x=read();
		++a[x],m=max(m,x);	
	}
	pw=dp[0][0]=1;
	for (int i=1;i<=m;++i){
		while (pw<=i) pw<<=1;
		while (a[i]--){
			for (int j=0;j<pw;++j) g[j]=ad(dp[0][j^i],dp[d-1][j]);
			for (int j=d-1;j>=1;--j){
				for (int k=0;k<pw;++k){
					if (k>(i^k)) continue;
					int x=dp[j][k];
					dp[j][k]=ad(dp[j-1][k],dp[j][i^k]);
					dp[j][k^i]=ad(x,dp[j-1][i^k]);
				}
			}
			for (int j=0;j<pw;++j) dp[0][j]=g[j];
		}
	}
	ans=ad(dp[0][0],Mod-(n%d==0));
	printf("%d\n",ans);
	return 0;
}
