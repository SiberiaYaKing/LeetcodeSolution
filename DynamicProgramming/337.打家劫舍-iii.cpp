/*
 * @lc app=leetcode.cn id=337 lang=cpp
 *
 * [337] 打家劫舍 III
 */

// @lc code=start
#include <functional>
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
    int rob(TreeNode* root) {
        function<vector<int>(TreeNode*)> dp =[&](TreeNode* node)->vector<int>{
            if(!node) {return {0,0};}
            vector<int> dp_l = dp(node->left);
            vector<int> dp_r = dp(node->right);
            int rob = node->val + dp_l[0] + dp_r[0];
            int no_rob = max(dp_l[0],dp_l[1])+max(dp_r[0],dp_r[1]);
            return {no_rob, rob};
        };
        vector<int> res = dp(root);
        return max(res[0],res[1]);
    }
};
// @lc code=end

