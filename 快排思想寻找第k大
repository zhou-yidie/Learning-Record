class Solution {
public:
    int partition(vector<int>& a, int low, int high, int k){
        //随机快排划分
        swap(a[low], a[rand() % (high - low + 1) + low]);
        int v = a[low];
        int i = low + 1;
        int j = high;
        while(true){
            //小于标杆的在右
            while(j >= low + 1 && a[j] < v) 
                j--;
            //大于标杆的在左
            while(i <= high && a[i] > v) 
                i++;
            if(i > j) 
                break;
            swap(a[i], a[j]);
            i++;
            j--;
        }
        swap(a[low], a[j]);
        //从0开始，所以为第j+1大
        if(j + 1 == k)
            return a[j];
        //继续划分
        else if(j + 1 < k)
            return partition(a, j + 1, high, k);
        else
            return partition(a, low, j - 1, k);
    }
    int findKth(vector<int> a, int n, int K) {
        return partition(a, 0, n - 1, K);
    }
};
