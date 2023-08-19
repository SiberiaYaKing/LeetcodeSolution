/*
 * @lc app=leetcode.cn id=309 lang=cpp
 *
 * [309] 最佳买卖股票时机含冷冻期
 */

// @lc code=start
#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>>dp(prices.size()+1, vector<int>(3,0));
        for(int i=0; i<=prices.size(); i++){
            for(int s=0; s<=3; s++){
                if(i==0){
                    dp[0][1]=INT_MIN;
                    continue;
                }
                switch (s)
                {
                case 0:
                    dp[i][0] = max(dp[i-1][0],dp[i-1][1]+prices[i-1]);
                    break;
                case 1:
                    dp[i][1] = max(dp[i-1][1],dp[i-1][2]-prices[i-1]);
                    break;
                case 2:
                    dp[i][2] = dp[i-1][0];
                default:
                    break;
                }
            }
        }
        return dp[prices.size()][0];
    }
};
// @lc code=end

