#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std;
const int maxn=1e7;
typedef long long ll;
ll a[maxn],que[maxn];
int main(){
    ll n,m,k,q,p,r,mod;
    int t;
    scanf("%d",&t);
    while(t--){
        ll ansa=0,ansb=0;
        int he=0,ta=0;
        scanf("%lld%lld%lld%lld%lld%lld%lld",&n,&m,&k,&p,&q,&r,&mod);
        for(int i=1;i<=k;i++)
            scanf("%lld",&a[i]);
        for(int i=k+1;i<=n;i++)
            a[i]=((p*a[i-1])%mod+(q*i)%mod+r)%mod;
        for(int i=n;i>=n-m+1;i--){
            while(he<ta&&a[que[ta-1]]<=a[i])ta--;
            que[ta++]=i;
        }
        ansa+=a[que[he]]^(n-m+1);
        ansb+=(ta-he)^(n-m+1);
        for(int i=n-m;i>0;i--){
            while(he<ta&&que[he]>i+m-1)he++;
            while(he<ta&&a[que[ta-1]]<=a[i])ta--;
            que[ta++]=i;
            ansa+=a[que[he]]^i;
            ansb+=(ta-he)^i;
        }
        printf("%lld %lld\n",ansa,ansb);
    }
    return 0;
}
