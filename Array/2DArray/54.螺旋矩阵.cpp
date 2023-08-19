/*
 * @lc app=leetcode.cn id=54 lang=cpp
 *
 * [54] 螺旋矩阵
 */

// @lc code=start
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.empty()) {return {};}
        vector<int> res;
        int col = matrix.size(), row = matrix.back().size();
        for(int n=0,h=col-1,w=row-1; n<(col+1)/2; n++,h--,w--){
            if(n>=h){
                for(int i=n; i<=w&&n==h; i++){
                    res.push_back(matrix[h][i]);
                }
                break;
            }
            if(n>=w){
                for(int i=n; i<=h&&n==w; i++){
                    res.push_back(matrix[i][w]);
                }
                break;
            }
            for(int i=n; i<w; i++){
                res.push_back(matrix[n][i]);
            }
            for(int i=n; i<h; i++){
                res.push_back(matrix[i][w]);
            }
            for(int i=w; i>n; i--){
                res.push_back(matrix[h][i]);
            }
            for(int i=h; i>n; i--){
                res.push_back(matrix[i][n]);
            }
        }
        return res;
    }
};
// @lc code=end

int main() {
    vector<vector<int>> input = {{1,11},{2,12},{3,13},{4,14},{5,15},{6,16},{7,17},{8,18},{9,19},{10,20}};
    Solution().spiralOrder(input);
}

