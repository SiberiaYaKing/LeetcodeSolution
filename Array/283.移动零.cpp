/*
 * @lc app=leetcode.cn id=283 lang=cpp
 *
 * [283] 移动零
 */

// @lc code=start
#include <vector>
using namespace std;


/* Gain:
 * 滑动窗口双指针，注意窗口收缩的时机和幅度
 */
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        if(!nums.size()) {return;}

        for(int fast=0, slow=0; fast<nums.size(); ++fast){
            if(nums[fast] != 0 && nums[slow] == 0) {
                nums[slow] = nums[fast];
                nums[fast] = 0;
            }
            if(nums[slow]!=0){
                ++slow;
            }
        }
        return;
    }
};
// @lc code=end

