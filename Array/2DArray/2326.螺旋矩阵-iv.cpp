/*
 * @lc app=leetcode.cn id=2326 lang=cpp
 *
 * [2326] 螺旋矩阵 IV
 */

// @lc code=start
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        if(!head) {return {};}
        vector<vector<int>> res(m,vector<int>(n,-1));
        ListNode* temp = head;
        for(int s=0,h=m-1,w=n-1; s<(m+1)/2&&temp; s++,h--,w--){
            if(s>=h){
                for(int i=s; i<=w&&s==h&&temp; i++){
                    res[h][i] = temp->val;
                    temp = temp->next;
                }
                break;
            }
            if(s>=w){
                for(int i=s; i<=h&&s==w&&temp; i++){
                    res[i][w] = temp->val;
                    temp = temp->next;
                }
                break;
            }
            for(int i=s; i<w&&temp; i++){
                res[s][i] = temp->val;
                temp = temp->next;
            }
            for(int i=s; i<h&&temp; i++){
                res[i][w] = temp->val;
                temp = temp->next;
            }
            for(int i=w; i>s&&temp; i--){
                res[h][i] = temp->val;
                temp = temp->next;
            }
            for(int i=h; i>s&&temp; i--){
                res[i][s] = temp->val;
                temp = temp->next;
            }
        }
        return res;
    }
};
// @lc code=end

