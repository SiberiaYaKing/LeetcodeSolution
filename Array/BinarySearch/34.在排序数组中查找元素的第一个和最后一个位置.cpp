/*
 * @lc app=leetcode.cn id=34 lang=cpp
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */

// @lc code=start
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int leftBound=-1, rightBound=-1;

        // rightBound
        int left=0, right=nums.size()-1;
        while(left<=right){
            int mid = left+(right-left)/2;
            if(nums[mid]<=target){
                left = mid+1;
            }else if(nums[mid]>target){
                right = mid-1;
            }
        }
        if(right>=0 && nums[right]==target){
            rightBound = right;
        }
        
        //leftBound
        left=0, right=nums.size()-1;
        while(left<=right){
            int mid = left+(right-left)/2;
            if(nums[mid]>=target){
                right = mid-1;
            }else if(nums[mid]<target){
                left = mid+1;
            }
        }
        if(left<nums.size()&&nums[left]==target){
            leftBound = left;
        }

        return {leftBound, rightBound};
    }
};
// @lc code=end

