/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] 合并两个有序链表
 */

// @lc code=start

//Definition for singly-linked list.
//提交前需要先注释掉结构体定义
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* Gain:
 * 1. 注意虚拟头节点的应用，可以省掉边界情况判空的麻烦，需要增删链表节点的时候优先考虑 
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* p1 = list1 , *p2 = list2;
        ListNode* dummy = new ListNode(-1), *p = dummy;

        while (p1 && p2){
            if (p1->val > p2->val){
                p->next = p2;
                p2 = p2->next;  
            } else {
                p->next = p1;
                p1 = p1->next;
            }
            p = p->next;
        }

        p->next = p2? p2 : p->next;
        p->next = p1? p1 : p->next;

        ListNode *res = dummy->next;
        delete dummy;
        dummy = nullptr;
        
        return res;
    }
};
// @lc code=end

