/*
 * @lc app=leetcode.cn id=86 lang=cpp
 *
 * [86] 分隔链表
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
 * 1. 注意虚拟头节点的应用，可以省掉边界情况判空的麻烦，需要增删链表节点的时候优先考虑
 * 2. 注意断开链表节点的操作，需要缓存被断开节点的下个节点，以便能继续遍历下个节点
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* dummy1 = new ListNode(-1), *p1 = dummy1;
        ListNode* dummy2 = new ListNode(-1), *p2 = dummy2;
        ListNode* p = head;

        while (p) {
            if (p->val < x) {
                p1->next = p;
                p1 = p1->next;
            } else {
                p2->next = p;
                p2 = p2->next;
            }
            //断开已经分隔的节点
            ListNode* nextNode = p->next;
            p->next = nullptr;
            p = nextNode;
        }

        p1->next = dummy2->next;
        delete dummy2;
        dummy2 = nullptr;

        ListNode* res = dummy1->next;
        delete dummy1;
        dummy1 = nullptr;
        return res;
    }
};
// @lc code=end

