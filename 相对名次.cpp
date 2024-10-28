class Solution 
{
public:
    vector<string> findRelativeRanks(vector<int>& score) 
    {
        int n = score.size();
        string  three[3] = {"Gold Medal", "Silver Medal", "Bronze Medal"};
        vector<pair<int,int>> arr;

        for(int i = 0; i < n; i++)
        {
            arr.emplace_back(make_pair(-score[i],i));
        }
        sort(arr.begin(),arr.end());
        vector<string> answer(n);
        for(int i = 0; i < n; i++)
        {
            if(i >= 3)
            {
                answer[arr[i].second] = to_string(i+1);
            }
            else
            {
                answer[arr[i].second] = three[i];
            }
        }
        return answer;
    }
};


