/*
 * @lc app=leetcode.cn id=322 lang=cpp
 *
 * [322] 零钱兑换
 */

// @lc code=start
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1,amount+1);
        dp[0] = 0;
        for(int n=1; n<dp.size(); n++) {
            for(int coin: coins){
                int newAmount = n-coin;
                if(newAmount<0) {continue;}
                dp[n] = min(dp[newAmount]+1,dp[n]);
            }
        }
        return dp[amount]==amount+1? -1: dp[amount];
    }
};
// @lc code=end

