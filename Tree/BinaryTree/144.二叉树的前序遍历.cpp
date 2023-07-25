/*
 * @lc app=leetcode.cn id=144 lang=cpp
 *
 * [144] 二叉树的前序遍历
 */

// @lc code=start
#include <vector>
#include <stack>
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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stack;
        TreeNode* node = root;
        while(node || !stack.empty()){
            while(node){
                res.push_back(node->val);
                stack.push(node);
                node = node->left;
            }
            if(!stack.empty()){
                TreeNode* top = stack.top();
                stack.pop();
                node = top->right;
            }
        }
        return res;
    }
};
// @lc code=end

