/*
 * @lc app=leetcode.cn id=26 lang=cpp
 *
 * [26] 删除有序数组中的重复项
 */

// @lc code=start
#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size()==0) {return 0;}

        int slow=0;
        for(int fast=0; fast<nums.size(); ++fast){
            if(nums[slow] != nums[fast]){
                nums[++slow] = nums[fast];
            }
        }

        //移除冗余的元素
        nums = vector<int>(nums.begin(),nums.begin()+slow+1);
        return nums.size();
    }
};
// @lc code=end

