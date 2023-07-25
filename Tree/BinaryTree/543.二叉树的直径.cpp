/*
 * @lc app=leetcode.cn id=543 lang=cpp
 *
 * [543] 二叉树的直径
 */

// @lc code=start
#include <iostream>
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
    int maxVal = 0;
    int maxDepth(TreeNode* node){
        if(!node){
            return 0;
        }
        int leftDepth = maxDepth(node->left);
        int rightDepth = maxDepth(node->right);
        maxVal = max(maxVal, leftDepth+rightDepth);
        return max(leftDepth,rightDepth)+1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        maxDepth(root);
        return maxVal;
    }
};
// @lc code=end

