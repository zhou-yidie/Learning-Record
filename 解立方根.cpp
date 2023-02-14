#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
#define double long double
const double eps = 1e-12;
int main()
{
    int T = 1;
    cin >> T;
    while (T--)
    {
        double n;
        cin >> n;
        double l = 0, r = 100000, res = 0;
        while (l <= r) //二分法查找答案
        {
            double mid = (l + r) / 2;
            if (fabs(mid * mid * mid - n) <= eps)//满足精度
            {
                res = mid;
                break;
            }
            if (mid * mid * mid > n) r = mid - 0.0001;
            else if (mid * mid * mid < n) l = mid + 0.0001, res = mid; 
        }
        cout << setprecision(3) << fixed << res << endl; 
    }
    return 0;
}
