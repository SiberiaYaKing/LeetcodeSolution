/*
 * @lc app=leetcode.cn id=104 lang=cpp
 *
 * [104] 二叉树的最大深度
 */

// @lc code=start
#include <iostream>
#include <vector>
#include <stack>
#include <set>
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
    int maxDepth(TreeNode* root) {
        int res = 0;
        int depth = 0;
        stack<TreeNode*> tempStack;
        TreeNode* tempNode = root;
        TreeNode* lastTopNode = nullptr;
        while(tempNode || !tempStack.empty()){
            while(tempNode){
                // 前序位: 入栈前清算
                depth++;
                // 到达叶子节点
                if(!tempNode->left && !tempNode->right){
                    res = max(depth,res);
                }
                tempStack.push(tempNode);
                tempNode = tempNode->left;
            }
            if(!tempStack.empty()){
                TreeNode* topNode = tempStack.top();
                if(!topNode->right || lastTopNode==topNode->right){
                    tempStack.pop();
                    // 后序位：所有子节点都出栈了再清算
                    depth--;
                } else {
                    tempNode = topNode->right;
                }
                if(!lastTopNode||lastTopNode!=topNode->right) {
                    //中序位：当上个栈顶节点不等于当前栈顶的右节点，相当于仅左子节点出栈，这时候清算是中序
                    cout<<topNode->val<<endl;
                }
                lastTopNode = topNode;
            }
        }
        return res;
    }
};
// @lc code=end

