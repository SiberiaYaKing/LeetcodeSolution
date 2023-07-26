/*
 * @lc app=leetcode.cn id=124 lang=cpp
 *
 * [124] 二叉树中的最大路径和
 */

// @lc code=start
#include <iostream>
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
    int maxSum = INT_MIN;
public:
    int traverse(TreeNode* root){
        int leftSum=0, rightSum=0;
        if(root->left){ //提前过滤掉不应该继续递归的解，可以减少递归栈的长度
            leftSum = traverse(root->left);
        }
        if(root->right){
            rightSum = traverse(root->right);
        }
        int newSum = root->val;
        newSum += (leftSum>0? leftSum:0);
        newSum += (rightSum>0? rightSum:0);
        maxSum = max(maxSum, newSum);
        int maxChildSum = max(leftSum,rightSum);
        return root->val+ (maxChildSum>0? maxChildSum:0);
    }
    int maxPathSum(TreeNode* root) {
        traverse(root);
        return maxSum;
    }
};
// @lc code=end

