class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        
        long total = 0;
        for(int x : nums)
            total += x;

        int rem = total % p;

        if(rem == 0)
            return 0;

        unordered_map<int,int> mp;
        mp[0] = -1;

        long prefix = 0;
        int ans = nums.size();

        for(int i = 0; i < nums.size(); i++) {
            
            prefix = (prefix + nums[i]) % p;

            int need = (prefix - rem + p) % p;

            if(mp.count(need))
                ans = min(ans, i - mp[need]);

            mp[prefix] = i;
        }

        if(ans == nums.size())
            return -1;

        return ans;
    }
};