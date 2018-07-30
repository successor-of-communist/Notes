#include<iostream>
#include<stdio.h>
#include<bitset>
using namespace std;
const int maxn=805;
bitset<maxn> a1[maxn],a2[maxn],b1[maxn],b2[maxn];
int ans[maxn][maxn];
int main(){
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=0;i<maxn;i++)
        {
            a1[i].reset();
            a2[i].reset();
            b1[i].reset();
            b2[i].reset();
        }
        int tmp;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                scanf("%d",&tmp);
                tmp%=3;
                if(tmp==1)
                    a1[i].set(j);
                else if(tmp==2)
                    a2[i].set(j);
            }
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                scanf("%d",&tmp);
                tmp%=3;
                if(tmp==1)
                    b1[j].set(i);
                else if(tmp==2)
                    b2[j].set(i);
            }
        }
        bitset<maxn>bit;
        int ans=0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                ans=0;
                bit=a1[i]&b1[j];
                ans+=bit.count();
                bit=a1[i]&b2[j];
                ans+=bit.count()*2;
                bit=a2[i]&b1[j];
                ans+=bit.count()*2;
                bit=a2[i]&b2[j];
                ans+=bit.count();
                ans%=3;
                printf("%d%c",ans,j==n-1?'\n':' ');
            }
        }
    }
    return 0;
}
