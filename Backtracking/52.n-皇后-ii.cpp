/*
 * @lc app=leetcode.cn id=52 lang=cpp
 *
 * [52] N 皇后 II
 */

// @lc code=start
#include <functional>
class Solution {
public:
    int totalNQueens(int n) {
        int count = 0;
        std::function<void(int,int,int,int,int)> backtracking = [&](int r,int n,int colu, int hill, int dale){
            if(r == n) {count++;}
            for(int c=0; c<n&&r<n; c++){
                if(1&colu>>c||1&hill>>(r+c)||1&dale>>(r-c+n)) {continue;}
                backtracking(r+1, n, colu|1<<c, hill|1<<(r+c), dale|1<<(r-c+n));
            }
        };
        backtracking(0,n,0,0,0);
        return count;
    }
};
// @lc code=end

#include <iostream>
using namespace std;
int main(){
    cout<<Solution().totalNQueens(16);
    //14772512
}
