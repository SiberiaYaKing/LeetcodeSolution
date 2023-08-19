/*
 * @lc app=leetcode.cn id=714 lang=cpp
 *
 * [714] 买卖股票的最佳时机含手续费
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        vector<vector<int>> dp(prices.size()+1, vector<int>(2,0));
        for(int i=0; i<=prices.size(); i++){
            if(i==0){
                dp[0][1] = INT_MIN+fee;
                continue;
            }
            for(int s=0;s<=1;s++){
                if(s == 0){
                    dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i-1]-fee);
                } else {
                    dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i-1]);
                }
            }
        }
        return dp[prices.size()][0];
    }
};
// @lc code=end

