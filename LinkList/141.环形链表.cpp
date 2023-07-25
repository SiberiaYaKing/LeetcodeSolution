/*
 * @lc app=leetcode.cn id=141 lang=cpp
 *
 * [141] 环形链表
 */

// @lc code=start

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/* Gain:
 * 1. 快慢指针，快指针走2步，慢指针走一步，环状结构或者中分链表常用
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* p1 = head, *p2 = head;

        while(p2 && p2->next){
            p1 = p1->next;
            p2 = p2->next->next;
            if(p1 == p2){
                return true;
            }
        }

        return false;
    }
};
// @lc code=end

