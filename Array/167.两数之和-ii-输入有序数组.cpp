/*
 * @lc app=leetcode.cn id=167 lang=cpp
 *
 * [167] 两数之和 II - 输入有序数组
 */

// @lc code=start
#include <vector>
using namespace std;

/* Gain:
 * 常规的左右向中心移动的双指针解法
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left=0,right = numbers.size()-1;
        while(left!=right) {
            if(numbers[right]+numbers[left]>target){
                right--;
            } else if(numbers[right]+numbers[left]<target){
                left++;
            } else if(numbers[right]+numbers[left]==target){
                break;
            }
        }
        return {left+1, right+1};
    }
};
// @lc code=end

