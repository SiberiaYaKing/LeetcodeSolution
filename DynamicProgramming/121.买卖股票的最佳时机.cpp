/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start
#include <vector>
using namespace std;

//交易次数k=1, 交易次数的穷举可以化简
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size()+1, vector<int>(2,0));
        for(int i=0;i<=prices.size(); i++){
            if(i==0){
                dp[0][1] = INT_MIN;
                continue;
            }
            for(int s=0; s<=1; s++){
                if(s==0){
                    dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i-1]);
                } else {
                    dp[i][1] = max(dp[i-1][1], -prices[i-1]);
                }
            }
        }
        return dp[prices.size()][0];
    }
};
// @lc code=end

