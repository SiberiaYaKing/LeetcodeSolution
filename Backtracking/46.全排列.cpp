/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] 全排列
 */

// @lc code=start
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> results;
        int upper = nums.size();
        for(int choice=0; choice<upper; choice++){
            backtracking(choice, upper, nums, results);
        }
        return results;
    }

    void backtracking(int choice, int upper, vector<int>& nums, vector<vector<int>>& results){
        upper--;
        if(upper==0){
            results.push_back(nums);
            return;
        }
        if(choice!=upper){
            swap(nums[upper],nums[choice]);
        }
        for(int choice=0 ; choice<upper; choice++){
            backtracking(choice, upper, nums, results); 
        }
        if(choice!=upper){
            swap(nums[choice],nums[upper]);
        }
    }
};
// @lc code=end

