/*
 * @lc app=leetcode.cn id=83 lang=cpp
 *
 * [83] 删除排序链表中的重复元素
 */

// @lc code=start

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* Gain:
 * 1. 典型的快慢指针应用，但是C++需要自己做内存管理
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head) {return nullptr;}

        ListNode* fast=head, *slow=head;
        while(fast){
            if(fast->val > slow->val){
                slow = slow->next;
                slow->val = fast->val;
            }
            fast = fast->next;
        }

        //C++ 还要自己删掉冗余的节点内存...
        ListNode* p = slow->next;
        while(p){
            ListNode* nextP = p->next;
            delete p;
            p = nextP? nextP->next: nextP;
        }
        slow->next = nullptr;

        return head;
    }
};
// @lc code=end

