/*
 * @lc app=leetcode.cn id=6 lang=cpp
 *
 * [6] N 字形变换
 */

// @lc code=start
#include <string>
using namespace std;

class Solution {
public:
    string convert(string s, int n) {
        if(n<2) {return s;}
        string res;
        int zHead = 2*n-2;
        for(int row=0; row<n; row++){
            int z=0, i1 = row, i2=zHead-row;
            while (i1<s.size()){
                if(i1!=i2){
                    res.push_back(s[i1]);
                }
                if(row!=0&&i2<s.size()){
                    res.push_back(s[i2]);
                }
                z++;
                i1 = zHead*z+row; 
                i2 = zHead*(z+1)-row;
            }  
        }
        return res;
    }
};
// @lc code=end

