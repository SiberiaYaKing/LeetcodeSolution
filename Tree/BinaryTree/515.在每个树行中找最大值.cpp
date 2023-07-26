/*
 * @lc app=leetcode.cn id=515 lang=cpp
 *
 * [515] 在每个树行中找最大值
 */

// @lc code=start
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()){
            int maxVal = INT_MIN;
            int len = queue.size(); //这个数量就是每层树的结点数
            for(int i=0;i<len;i++){
                TreeNode* node = queue.front();
                queue.pop();
                if(node){
                    queue.push(node->left);
                    queue.push(node->right);
                    maxVal = max(maxVal, node->val);
                }
            }
            if(!queue.empty()) {res.push_back(maxVal);}
        }
        return res;
    }
};
// @lc code=end

