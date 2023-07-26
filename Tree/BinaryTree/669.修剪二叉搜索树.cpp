/*
 * @lc app=leetcode.cn id=669 lang=cpp
 *
 * [669] 修剪二叉搜索树
 */

// @lc code=start

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
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if(!root) {return nullptr;}
        TreeNode* oldRoot = root;
        if(root->val<low){
            root = oldRoot->right;
            oldRoot->right = nullptr;
        } else if(root->val>high){
            root = oldRoot->left;
            oldRoot->left = nullptr;
        }
        if(!root) {return nullptr;}
        if(root!=oldRoot){
            root = trimBST(root,low,high);
        } else {
            if(root->right){  //提前过滤掉不应该继续递归的解，可以减少递归栈的长度
                root->right = trimBST(root->right, low, high);
            }
            if(root->left){
                root->left = trimBST(root->left, low, high);
            }
        }
        
        return root;
    }
};
// @lc code=end

