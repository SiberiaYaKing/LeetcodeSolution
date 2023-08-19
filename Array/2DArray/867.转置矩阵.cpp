/*
 * @lc app=leetcode.cn id=867 lang=cpp
 *
 * [867] 转置矩阵
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        if(matrix.empty()) {return {};}
        vector<vector<int>> newMat(matrix.back().size(), vector<int>(matrix.size(),0));
        for(int i=0; i<matrix.size();i++){
            for(int j=0; j<matrix.back().size();j++){
                newMat[j][i] = matrix[i][j];
            }
        }
        return newMat;
    }
};
// @lc code=end

