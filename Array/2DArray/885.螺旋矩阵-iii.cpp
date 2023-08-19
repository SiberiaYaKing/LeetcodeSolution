/*
 * @lc app=leetcode.cn id=885 lang=cpp
 *
 * [885] 螺旋矩阵 III
 */

// @lc code=start
#include <vector>
using namespace std;

class Solution {
    bool isValid(const vector<int>& point,int rows, int cols){
        if(point[0]>=rows || point[0]<0) {return false;}
        if(point[1]>=cols || point[1]<0) {return false;}
        return true;        
    }
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        int size = rows*cols;
        vector<vector<int>> res;
        vector<int> point = {rStart, cStart};
        for(int s=0,e=0;res.size()<size;e+=2){
            if(s==e && isValid(point,rows,cols)) {
                res.push_back(point);
                point[1]++;
                continue;
            }
            for(int i=s; i<e; i++) {
                if(isValid(point,rows,cols)){res.push_back(point);}
                point[0]++;
            }
            point[0]--, point[1]--;
            for(int i=e; i>s; i--) {
                if(isValid(point,rows,cols)){res.push_back(point);}
                point[1]--;
            }
            point[0]--, point[1]++;
            for(int i=e; i>s; i--) {
                if(isValid(point,rows,cols)){res.push_back(point);}
                point[0]--;
            }
            point[0]++, point[1]++;
            for(int i=s; i<e; i++) {
                if(isValid(point,rows,cols)){res.push_back(point);}
                point[1]++;
            }
        }
        return res;
    }
};
// @lc code=end
int main(){
    Solution().spiralMatrixIII(5,6,1,4);
}
