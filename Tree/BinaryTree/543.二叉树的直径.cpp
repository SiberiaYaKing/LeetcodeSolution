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
        int leftDepth = 0, rightDepth = 0;
        if(node->left){ //提前过滤掉不应该继续递归的解，可以减少递归栈的长度
            leftDepth = maxDepth(node->left);
        }
        if(node->right){
            rightDepth = maxDepth(node->right);
        }
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

