/*
 * @lc app=leetcode.cn id=752 lang=cpp
 *
 * [752] 打开转盘锁
 */

// @lc code=start
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;
class Solution {
    static const char ZERO = '0';
    static const char NINE = '9';
    inline static const string BEGIN = "0000";

    string plusOne(string s,int i){
        s[i] = s[i]+1;
        if(s[i]>NINE){
            s[i] = ZERO;
        }
        return s;
    }
    string miusOne(string s,int i){
        s[i] = s[i]-1;
        if(s[i]<ZERO){
            s[i] = NINE;
        }
        return s;
    }
public:
    int openLock(vector<string>& deadends, string target) {
        queue<string> queue;
        unordered_set<string> visited(deadends.begin(),deadends.end());
        if(visited.count(BEGIN)) {return -1;}
        queue.push(BEGIN);
        visited.insert(BEGIN);
        int count = 0;
        while(!queue.empty()){
            int queueSize = queue.size();
            for(int i=0; i<queueSize; i++){
                string front = queue.front();
                queue.pop();
                if(front==target) {return count;}
                for(int j=0;j<front.size();j++){
                    string up = plusOne(front,j);
                    string down = miusOne(front,j);
                    if(!visited.count(up)){
                        queue.push(up);
                        visited.insert(up);
                    }
                    if(!visited.count(down)){
                        queue.push(down);
                        visited.insert(down);
                    }
                }
            }
            count++;
        }
        return -1;
    }
    // //已知目标点的情况下可以双向BFS
    // int openLock(vector<string>& deadends, string target) {
    //     unordered_set<string> visited(deadends.begin(),deadends.end());
    //     if(visited.count(BEGIN)) {return -1;}
    //     int count = 0;
    //     unordered_set<string> q1,q2;
    //     q1.insert(BEGIN);
    //     q2.insert(target);
    //     while(!q1.empty()&&!q2.empty()){
    //         unordered_set<string> temp;
    //         for(auto cur: q1){
    //             if(q2.count(cur)) {return count;}
    //             visited.insert(cur);
    //             for(int j=0;j<cur.size();j++){
    //                 string up = plusOne(cur,j);
    //                 string down = miusOne(cur,j);
    //                 if(!visited.count(up)){
    //                     temp.insert(up);
    //                 }
    //                 if(!visited.count(down)){
    //                     temp.insert(down);
    //                 }
    //             }
    //         }
    //         count++;
    //         q1 = q2;
    //         q2 = temp;
    //     }
    //     return -1;
    // }
};
// @lc code=end

