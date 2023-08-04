/*
 * @lc app=leetcode.cn id=37 lang=cpp
 *
 * [37] 解数独
 */

// @lc code=start
#include <vector>
using namespace std;

class Solution {
    static const char ZERO = '0';
    static const char EMPTY = '.';
    bool isValid(const vector<vector<char>>& board,int row,int col, char num){
        int size = board.size();
        for(int i=0; i<size; i++){
            if(board[i][col] == num) {return false;}
            if(board[row][i] == num) {return false;}
            if(board[row/3*3+i/3][col/3*3+i%3]==num){
                return false;
            }
        }
        return true;
    }
    
    bool backtracking(vector<vector<char>>& board, int row, int col){
        int size = board.size();
        if(col == size){
            row = row+1;
            if(row == size) {return true;}
            return backtracking(board,row,0);
        }
        if(board[row][col]!=EMPTY){
            return backtracking(board,row,col+1);
        }
        for(int num = 1; num<=size; num++){
            char chNum = num+ZERO;
            if(!isValid(board,row,col,chNum)) {continue;}
            board[row][col] = chNum;
            if(backtracking(board,row,col+1)) {return true;}
            board[row][col] = EMPTY;
        }
        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board,0,0);
    }
};
// @lc code=end

