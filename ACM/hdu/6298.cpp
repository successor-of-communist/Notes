#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int MAXN = 1e5 + 5;
int main() {
    ll t,n;
    scanf("%lld",&t);
    ll ans;
    while(t--)
    {
        scanf("%lld",&n);
        if(n%3==0)
            ans=(n/3)*(n/3)*(n/3);
        else if(n%4==0)
            ans=(n/2)*(n/4)*(n/4);
        else ans=-1;
        printf("%lld\n",ans);
    }
    return 0;
}
