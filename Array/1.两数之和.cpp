/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
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
            num1 = tempNums[left], num2 = tempNums[right];
            if(tempNums[right]+tempNums[left]>target){
                right--;
            } else if(tempNums[right]+tempNums[left]<target){
                left++;
            } else if(tempNums[right]+tempNums[left]==target){
                break;
            }
        }
        
        left = find(nums.begin(),nums.end(),num1)-nums.begin();
        right = nums.rend()-find(nums.rbegin(),nums.rend(),num2)-1;
        return {left, right};
    }
};
// @lc code=end

