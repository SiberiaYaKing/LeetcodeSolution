/*
 * @lc app=leetcode.cn id=590 lang=cpp
 *
 * [590] N 叉树的后序遍历
 */

// @lc code=start
#include <vector>
#include <stack>
using namespace std;
//Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
    struct Item{
        Node* node;
        int childIdx = 0;
        Node* getNextChild(){
            if(childIdx<node->children.size()){
                return node->children[childIdx++];
            }
            childIdx = 0;
            return nullptr;
        }
    };
public:
    vector<int> postorder(Node* root) {
        vector<int> res;
        stack<Item> stack;
        Node* node = root;
        while(node || !stack.empty()){
            while(node){
                stack.push({node,0});
                //注意C++的默认拷贝，这里必须访问栈顶
                node = stack.top().getNextChild();
            }
            if(!stack.empty()){
                //注意C++的默认拷贝，这里必须用引用
                Item& top = stack.top(); 
                Node* nextNode = top.getNextChild();
                if(!nextNode) {
                    stack.pop();
                    res.push_back(top.node->val);
                } else {
                    node = nextNode;
                }
            }
        }
        return res;
    }
};
// @lc code=end

