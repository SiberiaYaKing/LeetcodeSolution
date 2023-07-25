/*
 * @lc app=leetcode.cn id=82 lang=cpp
 *
 * [82] 删除排序链表中的重复元素 II
 */

// @lc code=start

//Definition for singly-linked list.
#include <iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/**Gain:
 * 典型的滑动窗口类型题，前后指针需要根据是否满足条件而移动
*/
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head) {return nullptr;}
        ListNode* dummy = new ListNode(INT8_MIN);
        dummy->next = head;

        ListNode* right=dummy, *left=dummy; //滑动窗口节点
        ListNode* preNode = left; //记录被删节点的前继
        int count = 0; //记录重复数量
        while(right){
            //窗口扩大的时机
            if(right->val == left->val){
                ++count;
                right = right->next;
            }
            //窗口收缩的时机
            if(!right || right->val != left->val) {
                for(int i=count; i>0; i--){
                    ListNode* leftNext = left->next;
                    if(count>1) { //大于1的重复节点需要删掉
                        delete left;
                        preNode->next = leftNext;
                    } else { //否则移动前继节点，因为被删节点要切换到下一个
                        preNode = left;
                    }
                    left = leftNext;
                }
                count=0;
            }
        }

        ListNode* res = dummy->next;
        delete dummy;
        dummy = nullptr;

        return res;
    }
};
// @lc code=end

