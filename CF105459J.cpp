#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 1e5+50 , mod = 1e9;
LL n , m , k  ,a[N]  ,you[N];
pair<LL, LL > b[N];
queue<LL> q[N];
priority_queue< pair<LL,LL > , vector< pair<LL,LL > >  , greater<pair<LL,LL > > > qu ;
void AC() {


    cin >> n >> m ;
    LL ans = 0 ;
    while (!qu.empty()) {
        qu.pop() ;
    }
    for (int i = 1; i <= n ; i++ ) {
        cin >> a[i]; you[i] = a[i] ;
        while (!q[i].empty()) {
            q[i].pop() ;
        }
    }
    for (int i = 1 ; i <= m ; i++ ) {
        cin >> b[i].first >> b[i].second ;
        q[ b[i].second ].push(b[i].first) ;
    }

    for (int i = 1 ; i <= n ; i++ ) {
        if (!q[i].empty()) {
            qu.push( { q[i].front() , i } ) ;
            q[i].pop();
        } else {
            qu.push( { mod + i ,  i } ) ;
        }
    }
    LL pos = 1 ;
    while (!qu.empty() && pos <= m) {
        auto id = qu.top().second , cur = qu.top().first ; qu.pop();
        LL cha = b[pos].first - ans ;
        //cout << "youid = " << you[id] << "  cha = " << cha << '\n';
        if (you[id] >= cha) {

            ans += cha ;
            you[id] -= cha ;

            LL pid = b[pos].second;
            LL nx ;
            if (!q[pid].empty()) {
                nx = q[pid].front() ; q[pid].pop() ;
            } else {
                nx = pid  + mod ;
            }
            you[pid] = a[pid] ;
            qu.push( { nx , pid } ) ;



            if (id == b[pos].second) {


                //cout << "YES\n";
                //LL nx ;
//                if (!q[id].empty()) {
//                    nx = q[id].front() ; q[id].pop() ;
//                } else {
//                    nx = id  +mod ;
//                }
//                you[id] = a[id] ;
//                qu.push({nx, id} ) ;


            } else {


                qu.push( { cur , id } ) ;


            }
            pos++ ;
        } else {
            ans += you[id] ;
            you[id] = 0;
        }
//        cout<<"you3  "<<you[3]<<endl;
//        cout<<"you1  "<<you[1]<<endl;

    }
    //cout << ans << '\n';
    while (!qu.empty()) {
        ans += you [ qu.top().second ] ;
        you [ qu.top().second ] = 0 ;qu.pop() ;
    }
    cout << ans << '\n';

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int T = 1 ;
    cin >> T ;
    while (T--) {
        AC();
    }
    return 0;
}

/*
3 1
3 3 3
8 1
 */