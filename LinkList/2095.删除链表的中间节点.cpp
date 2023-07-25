/*
 * @lc app=leetcode.cn id=2095 lang=cpp
 *
 * [2095] 删除链表的中间节点
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
 *  删除节点前需要缓存被删节点的后继，以便删除节点后链表可以再接上
*/

class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        if(!head->next) {return nullptr;}
        
        ListNode* fast=head, *slow=head;
        ListNode* preNode=slow;
        while(fast && fast->next){
            preNode = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* restList = slow->next;
        delete slow;
        preNode->next = restList;

        return head;
    }
};
// @lc code=end

