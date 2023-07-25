/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第 N 个结点
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

/* Gain：
 * 1. 注意虚拟头节点的应用，可以省掉边界情况判空的麻烦，需要增删链表节点的时候优先考虑
 * 2. 让快指针先走n步，慢指针再跟着快指针走len-n步, 慢指针可以定位到第n个节点，
 *    由于是删除操作，需要定位到倒数n+1，以便获取被删除节点的前一个结点，然后才能进行删除操作
 * 3. 删除节点前需要缓存被删节点的后继，以便删除节点后链表可以再接上，也防止释放节点内存出现空指针的崩溃
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(-1), *fast = dummy, *slow = dummy;
        dummy->next = head; 

        for(int i=0; fast; i++){
            fast = fast->next;
            if(i >= n+1){ //需要定位倒数n+1个节点，才能进行删除操作
                slow = slow->next;
            }
        }
        
        ListNode* restList = slow->next->next;
        delete slow->next;
        slow->next = restList;

        ListNode* res = dummy->next;
        delete dummy;
        dummy = nullptr;
        return res;
    }
};
// @lc code=end

