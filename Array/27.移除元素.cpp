/*
 * @lc app=leetcode.cn id=27 lang=cpp
 *
 * [27] 移除元素
 */

// @lc code=start
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if(!nums.size()) {return 0;}
        
        int slow=0;
        for(int fast=0; fast<nums.size(); ++fast){
            if(nums[fast] != val) {
                nums[slow++] = nums[fast];
            }
        }

        //移除冗余的元素
        nums = vector<int>(nums.begin(),nums.begin()+slow);
        return nums.size();
    }
};
// @lc code=end

