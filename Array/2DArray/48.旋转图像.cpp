/*
 * @lc app=leetcode.cn id=48 lang=cpp
 *
 * [48] 旋转图像
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        for(int i=0; i<matrix.size();i++){
            for(int j=i;j<matrix.size();j++){
                swap(matrix[i][j],matrix[j][i]);
            }
        }
        for(int i=0; i<matrix.size();i++){
            for(int l = 0, r = matrix.size()-1; l<=r; r--,l++){
                swap(matrix[i][l],matrix[i][r]);
            }
        }
    }
};
// @lc code=end

