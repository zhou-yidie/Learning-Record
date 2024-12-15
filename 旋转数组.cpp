// class Solution {
// public:
//     void rotate(vector<int>& nums, int k) {
//         int n = nums.size();
//         k = k % n;
//         int count = gcd(k, n);
//         for (int start = 0; start < count; ++start) {
//             int current = start;
//             int prev = nums[start];
//             do {
//                 int next = (current + k) % n;
//                 swap(nums[next], prev);
//                 current = next;
//             } while (start != current);
//         }
//     }
// };     // 这里还没弄懂


class Solution {
public:
    void reverse(vector<int>& nums, int start, int end) {
        while (start < end) {
            swap(nums[start], nums[end]);
            start += 1;
            end -= 1;
        }
    }

    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums, 0, nums.size() - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, nums.size() - 1);
    }
};

