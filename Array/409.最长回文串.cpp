/*
 * @lc app=leetcode.cn id=409 lang=cpp
 *
 * [409] 最长回文串
 */

// @lc code=start
#include <unordered_map>
#include <string>
using namespace std;

/* Gain:
 * 这是利用回文串的数学性质和哈希表解决问题，哈希表用来计数，注意回文串的中心可能是偶数个重复字符
 */
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char ,int> charCounter;
        for(char c : s){
            if(charCounter.find(c)==charCounter.end()){
                charCounter[c] = 1;
            } else {
                charCounter[c]++;
            }
        }
        int res = 0;
        int one = 0;
        for(auto item : charCounter){
            int even = item.second/2 *2;
            res += even;
            if(item.second-even){
                one = 1;
            }
        }
        return res+one;
    }
};
// @lc code=end

