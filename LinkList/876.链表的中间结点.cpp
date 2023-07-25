/*
 * @lc app=leetcode.cn id=876 lang=cpp
 *
 * [876] 链表的中间结点
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
 * 1. 快慢指针，快指针走2步，慢指针走一步，环状结构或者中分链表常用
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* p1= head, *p2= head;

        // for (int i1=0, i2=0; p1; ) {
        //     p1 = p1->next;
        //     i1++;
        //     if(i1/2-i2>0){
        //         p2 = p2->next;
        //     }
        //     i2 = i1/2;
        // }

        while(p2 && p2->next){
            p1 = p1->next;
            p2 = p2->next->next;
        }

        return p1;
    }
};
// @lc code=end

