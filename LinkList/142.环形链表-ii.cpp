/*
 * @lc app=leetcode.cn id=142 lang=cpp
 *
 * [142] 环形链表 II
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
 * 2. 快慢指针相遇时，快指针始终比慢指针多走一圈，根据这个特性，
 *    慢指针放在头节点，两个指针同速前进就能在环起点遇到
 * 3. 如果需要断环，需要在快慢指针找到环起点前，记录下环终点的位置
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow=head, *fast=head;
        
        bool isCycle = false;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast){
                isCycle = true;
                break;
            }
        }
        if(!isCycle) {return nullptr;}
        
        //慢指针放在头节点
        slow = head;
        //breakNode是用来断环的
        ListNode* breakNode=fast;
        while(fast!=slow) {
            breakNode = fast;
            slow = slow->next;
            fast = fast->next;
        }
        //断环操作
        breakNode->next = nullptr;
        //这道题不能改链表，还原回去
        breakNode->next = slow;
        return fast;
    }
};
// @lc code=end

