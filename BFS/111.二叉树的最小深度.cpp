/*
 * @lc app=leetcode.cn id=111 lang=cpp
 *
 * [111] 二叉树的最小深度
 */

// @lc code=start

//Definition for a binary tree node.
#include <queue>
using namespace std;
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
    int minDepth(TreeNode* root) {
        int depth = 0;
        if(!root) {return 0;}
        queue<TreeNode*> queue;
        queue.push(root);
        while(!queue.empty()){
            int queueSize = queue.size();
            depth++;
            for(int i=0;i<queueSize; i++){
                TreeNode* top = queue.front();
                if(top->left){
                    queue.push(top->left);
                }
                if(top->right){
                    queue.push(top->right);
                }
                if(!top->right&&!top->left){
                    return depth;
                }
                queue.pop();
            }
        }
        return depth;
    }
};
// @lc code=end

