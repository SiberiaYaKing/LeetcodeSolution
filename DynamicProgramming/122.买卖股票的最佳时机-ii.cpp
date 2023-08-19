/*
 * @lc app=leetcode.cn id=122 lang=cpp
 *
 * [122] 买卖股票的最佳时机 II
 */

// @lc code=start
#include <vector>
using namespace std;

//交易次数k为正无穷，近似k-1==k
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size()+1, vector<int>(2,0));
        for(int i=0; i<=prices.size(); i++){
            if(i==0){
                dp[0][1] = INT_MIN;
                continue;
            }
            for(int s=0;s<=1;s++){
                if(s == 0){
                    dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i-1]);
                } else {
                    dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i-1]);
                }
            }
        }
        return dp[prices.size()][0];
    }
};
// @lc code=end

