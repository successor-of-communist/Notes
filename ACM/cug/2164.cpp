#include<iostream>
#include<queue>
#include<cmath>
#include<string.h>
using namespace std;
long long C[50][50];
void init()
{
    C[0][0]=C[1][0]=C[1][1]=1;
    for(int i=2;i<50;i++)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)
        {
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
}
int gcd(int a,int b)
{
    if(b==0)
        return a;
    else return gcd(b,a%b);
}
int tmp[3];
long long cal(int len)
{
    long long ans=1;
    int sum=0;
    for(int i=0;i<3;i++)
    {
        if(tmp[i]%len)
            return 0;
        tmp[i]/=len;
        sum+=tmp[i];
    }
    for(int i=0;i<2;i++)
    {
        ans*=C[sum][tmp[i]];
        sum-=tmp[i];
    }
    return ans;
}
int main()
{
    init();
    int t;
    cin>>t;
    while(t--)
    {
        int x,y,z;
        long long ans=0;
        cin>>x>>y>>z;
        int n=x+y+z;
        for(int i=1;i<=n;i++)
        {
            tmp[0]=x;
            tmp[1]=y;
            tmp[2]=z;
            ans+=cal(n/gcd(i,n));
        }
        if(n&1)
        {
            for(int i=0;i<3;i++)
            {
                tmp[0]=x;
                tmp[1]=y;
                tmp[2]=z;
                tmp[i]--;
                ans+=cal(2)*n;
            }
        }
        else
        {
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                {
                    tmp[0]=x;
                    tmp[1]=y;
                    tmp[2]=z;
                    tmp[i]--;
                    tmp[j]--;
                    if(tmp[i]<0||tmp[j]<0)
                        continue;
                    ans+=cal(2)*n/2;
                }
            }
            tmp[0]=x;
            tmp[1]=y;
            tmp[2]=z;
            ans+=cal(2)*n/2;
        }
        ans=ans/(2*n);
        cout<<ans<<endl;
    }
}
