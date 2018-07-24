#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=1e5+5;
char str[maxn];
struct node{
    int l,r,add;
}ar[maxn];
bool cmp(node a,node b){
    if(a.r>=a.l)
        return b.l>b.r||b.l>a.l;
    else
        return b.l>b.r&&a.r>b.r;
}
bool cmp1(node a,node b){
    if(a.l>=a.r&&b.l<b.r)
        return false;
    if(a.l<a.r&&b.l>=b.r)
        return true;
    if(a.l>=a.r&&b.l>=b.r)
        return a.r>b.r;
    return a.l<b.l;
}
int main()
{
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%s",str);
            int len=strlen(str);
            ar[i].l=ar[i].r=ar[i].add=0;
            for(int j=0;j<len;j++)
            {
                if(str[j]=='('){
                    ar[i].r++;
                }
                else{
                    if(ar[i].r>0){
                        ar[i].add++;
                        ar[i].r--;
                    }
                    else
                        ar[i].l++;
                }
            }
        }
        sort(ar,ar+n,cmp);
        int now=0;
        int ans=0;
        for(int i=0;i<n;i++){
            if(ar[i].l>now)
                ar[i].l=now;
            ans+=ar[i].l+ar[i].add;
            now-=ar[i].l;
            now+=ar[i].r;
        }
        printf("%d\n",ans*2);
    }
    return 0;
}

