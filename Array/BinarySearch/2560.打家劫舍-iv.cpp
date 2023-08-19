/*
 * @lc app=leetcode.cn id=2560 lang=cpp
 *
 * [2560] 打家劫舍 IV
 */

// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;

//看到「最大化最小值」或者「最小化最大值」就要想到二分答案，这是一个固定的套路。
//满足单调性优先考虑二分法
//这里dp数组的定义是最终偷的次数，必须要达到k
// 「最小化最大值」就是找到左边界
// 「最大化最小值」就是找到右边界
// 本题是左边界问题
class Solution {
public:
    int minCapability(vector<int>& nums, int k) {
        int left =  *min_element(nums.begin(),nums.end());
        int right = *max_element(nums.begin(),nums.end());
        while(left<=right){
            int mid = left+(right-left)/2;
            vector<int> dp(nums.size(),0);
            for(int i=0; i<nums.size();i++){
                if(mid<nums[i]) { //价值较小 不偷
                    if(i<1) {
                        dp[i] = 0;
                        continue;
                    }
                    dp[i] = dp[i-1];
                }else if(mid>=nums[i]){ //价值较大 偷
                    if(i<2) {
                        dp[i] = 1;
                        continue;
                    }
                    dp[i] = max(dp[i-1],dp[i-2]+1);
                }
            }  
            if(dp.back()>=k){
                right = mid-1;
            } else {
                left = mid+1;
            }
        }
        return left;
    }
};
// @lc code=end

