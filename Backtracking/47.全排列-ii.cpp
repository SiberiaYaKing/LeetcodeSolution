/*
 * @lc app=leetcode.cn id=47 lang=cpp
 *
 * [47] 全排列 II
 */

// @lc code=start
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
    void backtracking(int choice, int upper, vector<int>& nums, 
         unordered_map<int, int>& counter, vector<vector<int>>& results){
        upper--;
        nums.push_back(choice);
        if(upper==0){
            results.push_back(nums);
            nums.pop_back();
            return;
        }
        counter[choice]--;
        for(auto& item: counter){
            if(item.second == 0) {continue;}
            backtracking(item.first, upper, nums, counter, results);
        }
        counter[choice]++;
        nums.pop_back();
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> results;
        unordered_map<int, int> counter;
        for(int num: nums){
            if(!counter.count(num)){
                counter[num] = 0;
            }
            counter[num] += 1;
        }
        for(auto& item: counter){
            vector<int> newNums;
            backtracking(item.first, nums.size(), newNums, counter, results);
        }
        return results;
    }
};
// @lc code=end

