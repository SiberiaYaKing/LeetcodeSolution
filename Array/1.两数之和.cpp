/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

/* Gain:
 * 最佳题解是用集合存储数据，看看每个数减出来的差是否找得到，
 * 但其实还有左右向中心靠拢的双指针解法，前提是数列需要排序
 */
// @lc code=start
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int left=0,right = nums.size()-1;
        int num1=0,num2=0;
        vector<int> tempNums = nums;
        sort(tempNums.begin(),tempNums.end());
        while(left!=right) {
            num1 = tempNums[left];
            num2 = tempNums[right];
            if(num1+num2>target){
                right--;
            } else if(num1+num2<target){
                left++;
            } else if(num1+num2==target){
                break;
            }
        }
        
        //需要在原数组中找到对应的索引
        left = find(nums.begin(),nums.end(),num1)-nums.begin();
        right = nums.rend()-find(nums.rbegin(),nums.rend(),num2)-1;
        return {left, right};
    }
};
// @lc code=end