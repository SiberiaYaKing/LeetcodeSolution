/*
 * @lc app=leetcode.cn id=59 lang=cpp
 *
 * [59] 螺旋矩阵 II
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n,vector<int>(n,0));
        for(int s=0,e=n-1,m=1; s<(n+1)/2; s++,e--){
            if(s==e) {res[s][s] = m;}
            for(int i=s; i<e; i++) {res[s][i] = m++;}
            for(int i=s; i<e; i++) {res[i][e] = m++;}
            for(int i=e; i>s; i--) {res[e][i] = m++;}
            for(int i=e; i>s; i--) {res[i][s] = m++;}
        }
        return res;
    }
};
// @lc code=end

