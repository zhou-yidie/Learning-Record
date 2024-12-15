#include <bits/stdc++.h>
using namespace std;
char a[10000];
char b[10000];
int main(){
    string c,d;
    getline(cin,c);
    getline(cin,d);
    // cout << " c = " << c << '\n';
    // cout << "d = " << d << '\n';
    int aid = 0 ,bid = 0 ;
    for(int i=0;i<c.size();i++){
        if(c[i]==' '){
            continue;
        }else if('A'<=c[i] && c[i] <='Z'){
            c[i]=c[i]+32;
            a[++aid]=c[i];
        }else{
            a[++aid]=c[i];
        }
    }
    int n=0;
    for(int i=0;i<d.size();i++){
        if(d[i]==' '){
            continue;
        }else if('A'<=d[i] && d[i] <='Z'){
            d[i]=d[i]+32;
            b[++bid]=d[i];
            n++;
        }else{
            b[++bid]=d[i];
            n++;
        }
    }
    int flag=1;
    if (aid != bid ) {
      flag = 0 ;
      //cout << "111\n";
    }
    for(int i=1;i<=aid;i++){
        if(a[i]!=b[i]){
            //cout << " i = " << i << " a " << a[i] << " b = " << b[i] << '\n';
            flag=0;
            break;
        }
    }
    // for(int i=0;i<n;i++){
    //     cout<<a[i]<<" ";
    // }
    // cout<<endl<<"1";
    // for(int i=0;i<n;i++){
    //     cout<<b[i]<<" ";
    // }
    // cout<<endl<<"2";
    if(flag==1){
        cout<<"YES";
    }else{
        cout<<"NO";
    }
    return 0;
}