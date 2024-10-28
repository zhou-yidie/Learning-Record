#include <iostream>
#include <vector>

int solution(std::vector<int> numbers) {
    int n = numbers.size() ;
    int ans = 0 ;
    std::vector<std::pair<int,int>> tmp;
    for (auto vl : numbers) {
        int ji = 0 ,ou = 0 ;
        while (vl) {
            if ( (vl%10) & 1 ) ji++ ;
            else ou++;
            vl /= 10;
        }
        tmp.push_back({ji,ou}) ;
    }
    int num = 1 ;
    for (int i = 0 ; i < n ; i++ ) {
        num *= tmp[i].second ;
    }
    ans += num ;
    num = 1 ;
    if (n >= 2) {
        for (int i = 0 ; i < n ; i++ ) {
            for (int j = i+1 ; j < n ; j ++ ) {
                num = 1 ;
                for (int k = 0 ; k < n ; k++ ) {
                    if ( k == i || k == j) num *= tmp[k].first ;
                    else num *= tmp[k].second ;
                }
                ans += num ;
            }
        }
    }

    if (n >= 4) {
        for (int i = 0 ; i < n ; i++ ) {
            for (int j = i+1 ; j < n ; j ++ ) {
                for (int i2 = j+1; i2< n ;i2++) {
                    for (int j2 = i2+1 ; j2 < n ; j2++) {
                        num = 1 ;
                        for (int k = 0 ; k < n ; k++ ) {
                            if ( k == i || k == j || k == i2 || k == j2) num *= tmp[k].first ;
                            else num *= tmp[k].second ;
                        }
                        ans += num ;
                    }
                }
                
            }
        }
    }
    
    return ans;
}

int main() {
    // You can add more test cases here
    std::cout << (solution({123, 456, 789}) == 14) << std::endl;
    std::cout << (solution({123456789}) == 4) << std::endl;
    std::cout << (solution({14329, 7568}) == 10) << std::endl;
    return 0;
}
