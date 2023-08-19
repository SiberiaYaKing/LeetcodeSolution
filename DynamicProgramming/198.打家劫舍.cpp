/*
 * @lc app=leetcode.cn id=198 lang=cpp
 *
 * [198] 打家劫舍
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> dp(nums.size(),0);
        for(int i=0; i<nums.size(); i++){
            if(i==0){
                dp[i] = nums[i];
                continue;
            }
            if(i==1){
                dp[i] = max(dp[i-1],nums[i]);
                continue;
            }
            dp[i]= max(dp[i-1],dp[i-2]+nums[i]);
        }
        return dp.back();
    }
};
// @lc code=end

