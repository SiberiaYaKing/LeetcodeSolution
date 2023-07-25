/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 */

// @lc code=start
#include <string>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        if(s.size()<=1) {return s;}
        string res;
        for(int i=0; i<s.size()-1; i++){
            string res1 = palindrome(s,i,i);
            string res2 = palindrome(s,i,i+1);
            res = res1.size()>res.size()? res1: res;
            res = res2.size()>res.size()? res2: res;
        }
        return res;
    }
    string palindrome(const string &s, int left, int right){
        while(left>=0 && right<s.size()){
            if(s[left]==s[right]){
                left--;                                                                                                                                                                                                                                                                                                                                       
                right++;
            } else {
                break;
            }
        }
        return s.substr(left+1,right-left-1);
    }
};
// @lc code=end

