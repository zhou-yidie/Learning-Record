// ------------------------ 差解 ------------------
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset <int> qu;
        vector<int> ans ;
        for( int i = 0 ; i < nums.size(); i ++ ) {
            if( qu.size() < k - 1 ) {
                qu.insert( nums[i] ) ;
            }else {
                cout << " i = " << i << '\n';
                qu.insert( nums[ i ] ) ;
                ans.push_back(*qu.rbegin()) ;
                //cout << (*qu.rbegin()) << ' ' ;
                int num = qu.erase( nums[i-k+1] ) ;
                for( int j = 2 ; j <= num ; j ++ ) {
                    qu.insert( nums[i-k+1] ) ;
                }
            }
        }
        return ans ;
    }
};


// --------------------------------------------------------------
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        priority_queue <int> qu;
        vector<int> ans ;
        map<int , int > mp ;
        for( int i = 0 ; i < nums.size(); i ++ ) {
            if ( qu.size() < k - 1 ) {
                qu.push(nums[ i ]) ;
            } else {
                qu.push( nums[ i ] ) ;
                int val = qu.top();
                while( mp[ val ] != 0 ) {
                    qu.pop();
                    mp[ val ] -- ;
                    val = qu.top();
                    
                }
                ans.push_back( val ) ;
                mp[ nums[ i - k + 1] ] ++ ;
            }
        }
        return ans ;
    }
};

// ---------------------------------------------

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> q;
        for (int i = 0; i < k; ++i) {
            while (!q.empty() && nums[i] >= nums[q.back()]) {
                q.pop_back();
            }
            q.push_back(i);
        }

        vector<int> ans = {nums[q.front()]};
        for (int i = k; i < n; ++i) {
            while (!q.empty() && nums[i] >= nums[q.back()]) {
                q.pop_back();
            }
            q.push_back(i);
            while (q.front() <= i - k) {
                q.pop_front();
            }
            ans.push_back(nums[q.front()]);
        }
        return ans;
    }
};




