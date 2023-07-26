/*
 * @lc app=leetcode.cn id=509 lang=cpp
 *
 * [509] 斐波那契数
 */

// @lc code=start
class Solution {
public:
    int fib(int n) {
        int prev = 0, curr = 1;
        if(n==0) { return prev; }
        if(n==1) { return curr; }
        for(int i = 2; i<=n; i++){
            int lastPrev = prev;
            int lastCurr = curr;
            prev = lastCurr;
            curr = lastCurr + lastPrev;
        }
        return curr;
    }
};
// @lc code=end

