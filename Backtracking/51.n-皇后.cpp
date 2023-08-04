/*
 * @lc app=leetcode.cn id=51 lang=cpp
 *
 * [51] N 皇后
 */

// @lc code=start
#include <vector>
#include <string>
using namespace std;


/**Gain:
 * N皇后问题的难点在于剪枝操作的实现，如何将前面已经布置的皇后遍历出来，这里有两种方法
 * 1. 直接遍历当前行上的列，左右对角线，看看是否已经有皇后占位了
 * 2. 考虑到左对角线(dale)的格子横竖索引值之差，右对角线(hill)的格子横竖索引值之和，都是与列数有关定值
 *      可以利用这个数量关系，对左斜，右斜，纵向各存一个数组来记录皇后的摆放情况，
 *      然后根据当前皇后格的索引推算出上面的格子有没有皇后（推荐）
*/
class Solution {
    static const char QUEEN = 'Q';
    static const char EMPTY = '.';
    vector<int> colu;
    vector<int> hill;
    vector<int> dale;

    bool isValid(int col, int row, const vector<string>& chessBoard){
        // for(int i = 0; i<row; i++){
        //     if(chessBoard[i][col]==QUEEN){
        //         return false;
        //     }
        // }
        // for(int i=row-1,j=col-1; i>=0&&j>=0; i--,j--){
        //     if(chessBoard[i][j]==QUEEN){
        //         return false;
        //     }
        // }
        // int n = chessBoard.size();
        // for(int i=row-1,j=col+1; i>=0&&j<n; i--,j++){
        //     if(chessBoard[i][j]==QUEEN){
        //         return false;
        //     }
        // }
        int n = chessBoard.size();
        return colu[col]==0&&dale[row-col+n]==0&&hill[row+col]==0;
    }

    void backtracking(int row, vector<string>& chessBoard, vector<vector<string>>& results){
        int n = chessBoard.size();
        if(row == n){
            results.push_back(chessBoard);
            return;
        }
        for(int col = 0; col<n; col++) {
            if(!isValid(col, row, chessBoard)){
                continue;
            }
            chessBoard[row][col] = QUEEN;
            colu[col] = dale[row-col+n] = hill[row+col] = 1;
            backtracking(row+1, chessBoard, results);
            colu[col] = dale[row-col+n] = hill[row+col] = 0;
            chessBoard[row][col] = EMPTY;
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        colu.resize(n,0);
        dale.resize(2*n,0);
        hill.resize(2*n,0);
        vector<vector<string>> results;
        vector<string> chessBoard;
        for(int i=0; i<n; i++){
            chessBoard.push_back(string(n, EMPTY));
        }
        backtracking(0, chessBoard, results);
        return results;
    } 
};
// @lc code=end

int main(){
    Solution().solveNQueens(4);
}
