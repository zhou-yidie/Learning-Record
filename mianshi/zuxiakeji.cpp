/**
 * @brief
 * 在时间轴上均匀的测量车辆的实时加速度（踩油门为+，刹车为-）
 * 找到一个时间段，累计加速度最小（负值比正值小），假设结果唯一
 * @return std::pair<int, int> 返回accelerations中开始和结束的index
 */

 #include <bits/stdc++.h>
 using namespace  std;
 
 std::pair<int, int> min_acc_window(const std::vector<double>& a) {
     int n = a.size(),end_id = -1,st_id = -1;
     double ans = 1e9+7;
     std::vector<double> f(n+1); // 以i为结束节点可以达到的最小值
     for (int i = 0; i < n ; i++) {
         if ( i == 0 ) {
             f[i] = a[i];
         } else {
             f[i] = min(f[i-1] + a[i] , a[i]);
         }
         if (f[i] < ans) {
             ans = f[i];
             end_id = i;
         }
     }
     for (int i = end_id; i >=0 ;i--) {
         ans -= a[i];
         if (ans == 0) {
             st_id = i ;
             break;
         }
     }
     return {st_id,end_id};
 }
 
 int main() {
     vector<double> test = {-9 , 6 , 23 , -80 ,2, -1 };
     auto v = min_acc_window(test);
     cout << v.first << " " << v.second << '\n';
 }
 