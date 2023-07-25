/*
 * @lc app=leetcode.cn id=23 lang=cpp
 *
 * [23] 合并 K 个升序链表
 */

// @lc code=start

//Definition for singly-linked list.
#include <vector>
#include <queue>
#include <functional>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


/* Gain:
 * 1. 注意虚拟头节点的应用，可以省掉边界情况判空的麻烦，需要增删链表节点的时候优先考虑 
 * 2. 多个元素取最值的情况，优先考虑用堆结构，上来就是LogN
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) {return nullptr;}
        ListNode* dummy = new ListNode(-1);
        //最小堆
        priority_queue<ListNode*, vector<ListNode*>, function<bool(ListNode*, ListNode*)>> pq
            ([] (ListNode* a, ListNode* b) {return a->val > b->val;});
        for(ListNode* head : lists){
            if(!head) {continue;}
            pq.push(head);
        }

        for (ListNode*p=dummy; !pq.empty(); p=p->next){
            ListNode* head = pq.top();
            pq.pop();
            if (head->next) {
                pq.push(head->next);
            }
            p->next = head;
        }  

        ListNode* res = dummy->next;
        delete dummy;
        dummy = nullptr;
        return res;
    }
};
// @lc code=end

