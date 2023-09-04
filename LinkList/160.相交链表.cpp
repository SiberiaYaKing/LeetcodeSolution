/*
 * @lc app=leetcode.cn id=160 lang=cpp
 *
 * [160] 相交链表
 */

// @lc code=start

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/* Gain:
 * 1. 让相交链表首尾相连，问题就转化成求环形链表环起点的问题，不过链表需要还原回去
 * 2. 还有一种解法，利用相交链表的性质，相交列表分头循环遍历，可以找到相交的节点
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        //成环
        ListNode* lastNode = headA;
        while (lastNode->next){
            lastNode = lastNode->next;
        }
        lastNode->next = headB;

        ListNode* p1=headA, *p2=headA;
        bool isCycle = false;
        
        while(p2 && p2->next){
            p1 = p1->next;
            p2 = p2->next->next;
            if(p1 == p2){
                isCycle = true;
                break;
            }
        }
        if(!isCycle) {
            lastNode->next = nullptr;
            return nullptr;
        }
        
        p2 = headA;
        while(p2!=p1){
            p1 = p1->next;
            p2 = p2->next;
        }

        //将环断开
        lastNode->next = nullptr;
        return p2;

        // //利用相交链表性质，分头循环遍历，可以找到相交的节点
        // ListNode* p1 = headA, *p2 = headB;
        // while (p1!=p2) {
        //     p1 = p1->next;
        //     p2 = p2->next;
        //     if(p1==p2) {break;}
        //     if(!p1) {p1 = headB;}
        //     if(!p2) {p2 = headA;}
        // }
        // return p2;
    }
};
// @lc code=end

