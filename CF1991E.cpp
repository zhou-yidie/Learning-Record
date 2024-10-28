#include<bits/stdc++.h>
using namespace  std ;
typedef long long LL ;
typedef pair<int,int> pii ;
const int N = 1e4+10 ;
const int mod = 1e9+7;

LL n , x , m ;

vector<int> e[N] ;
int vis[N] ;
bool fg ;


bool bfs(int x) {
    queue<int> q ; q.push(1);
    fill(vis+1,vis+n+1,-1);
    vis[1] = 0 ;
    while (!q.empty()) {
        auto f = q.front() ; q.pop() ;
        for (auto i : e[f]) {
            if (vis[i] != -1 && vis[i] == vis[f]) return 1;
            if (vis[i] != -1) continue;
            vis[i] = vis[f] ^ 1 ;
            q.push(i);
        }
    }
    return 0;
}

void AC(){
    cin >> n >> m ;
    for (int i =  0 ; i <= n + 5 ; i++ ) {
        e[i].clear();
    }
    for (int i = 1 ; i <= m ;i ++ ) {
        int u , v ; cin >> u >> v ;
        e[u].push_back(v) ; e[v].push_back(u);    
    }
    if (bfs(1)) {
        cout << "Alice" << endl;
        for (int i = 1 , a , b ; i <= n ; i++ ) {
            cout << "1 2" << endl;
            cin >> a >> b ;
        }
    } else {
        cout << "Bob" << endl;
        vector<int> v[2] ;
        for (int i = 1 ; i <= n ; i++ ) {
            v[ vis[i] ].push_back(i);
        }
        for (int i = 1 , a , b ; i <= n ; i++ ) {
            cin >> a >> b ;
            if (a > b) swap(a,b) ;
            if (a == 1) {
                if (!v[0].empty()) {
                    cout << v[0].back() << " " << a << endl;
                    v[0].pop_back();
                } else {
                    cout << v[1].back() << " " << b << endl;
                    v[1].pop_back();
                }
            } else {
                if (!v[1].empty()) {
                    cout << v[1].back() << " " << b << endl;
                    v[1].pop_back();
                } else {
                    cout<<v[0].back()<<" "<<a<<endl;
					v[0].pop_back();
                }
            }
        }
    }
}



int main(){
//    ios::sync_with_stdio(0);
//    cin.tie(0);cout.tie(0);
    int tt = 1 ;
    cin >> tt ;
    while( tt-- ) {
        AC();
    }
}

//  1  2  3 4 5 6 7 ....n
