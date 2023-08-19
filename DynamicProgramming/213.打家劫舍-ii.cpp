/*
 * @lc app=leetcode.cn id=213 lang=cpp
 *
 * [213] 打家劫舍 II
 */

// @lc code=start
#include <vector>
using namespace std;
/**Gain:
 * 在打家劫舍问题1的基础上，将问题分解成：
 *  偷第一家不偷最后一家 or 不偷第一家偷最后一家
 * 然后比较这两者的最大值
*/
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n<2) {return nums[0];}
        return max(robRange(nums,0,n-1), robRange(nums,1,n));
    }

    int robRange(vector<int>& nums, int begin, int end) {
        vector<int> dp(nums.size(),0);
        for(int i=begin; i<end; i++){
            if(i==begin){
                dp[i] = nums[i];
                continue;
            }
            if(i==begin+1){
                dp[i] = max(dp[i-1],nums[i]);
                continue;
            }
            dp[i]= max(dp[i-1],dp[i-2]+nums[i]);
        }
        return dp[end-1];
    }
};
// @lc code=end

