#include<iostream>
#include<cmath>
#include<string.h>
using namespace std;
int num[1010];
int ans[1010];
int prime[10100];
int n,m,k;
bool solve(int cnt)
{
    if(cnt==m-n+2)
        return true;
    int sum=0;
    for(int i=n;i<=m;i++)
    {
        if(num[i]==0)
        {
            sum=i;
            int j;
            int len=cnt-k;
            if(len<0)
                len=0;
            for(j=cnt-1;j>len;j--)
            {
                sum+=ans[j];
                if(prime[sum]!=1)
                    break;
            }
            if(j==len)
            {
                ans[cnt]=i;
                num[i]=1;
                if(solve(cnt+1))
                    return true;
                num[i]=0;
            }
        }
    }
    return false;
}
void init()
{
    memset(prime,0,sizeof(prime));
    for(int i=2;i<10010;i++)
    {
        int len=sqrt(i);
        for(int j=2;j<=len;j++)
            if(i%j==0)
            {
                prime[i]=1;
                break;
            }
    }
}
int main(){
    init();
    while(cin>>n>>m>>k)
    {
        if(n==0)
            break;
        memset(num,0,sizeof(num));
        memset(ans,0,sizeof(ans));
        num[n]=1;
        ans[1]=n;
        if(solve(2))
        {
            int i=1;
            for(;i<m-n+1;i++)
                cout<<ans[i]<<",";
            cout<<ans[i]<<endl;
        }
        else
        {
            cout<<"Your nightmare never ends."<<endl;
        }
    }
    return 0;
}
