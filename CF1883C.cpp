#include <bits/stdc++.h>
using namespace std;
int a[200010],b[200010];
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t,n,k;
    cin>>t;
    for(int m=0;m<t;m++){
        cin>>n>>k;
        int cnt;
        int flag=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            b[i]=a[i]%k;
        }
        for(int i=1;i<=n;i++){
            if(b[i]==0){
                cnt=0;
                break;
            }
            if(k==4 && b[i]==3){
                cnt=1;
            }
            if(k==4 && b[i]==2 && flag==0){
                flag=2;
            }
            if(k==4 && b[i]==2 && flag==2){
                cnt=0;
                break;
            }
            if(k==4 && b[i]==1 && flag==2){
                cnt=1;
            }
            if(k==4 && b[i]==1 && flag==0){
                cnt++;
                if(cnt>2){
                    cnt=2;
                }
            }
            if(k==2 || k==3 || k==5){
                if(cnt==0){
                    cnt=k-b[i];
                }else{
                    cnt=min(cnt,k-b[i]);
                }
            }
        }
        cout<<cnt<<endl;
    }
    return 0;
}