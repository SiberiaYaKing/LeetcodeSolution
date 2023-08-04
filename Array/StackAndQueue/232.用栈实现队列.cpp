/*
 * @lc app=leetcode.cn id=232 lang=cpp
 *
 * [232] 用栈实现队列
 */

// @lc code=start
#include <stack>
using namespace std;

class MyQueue {
    stack<int> queuePush;
    stack<int> queuePop;
public:
    MyQueue() {}
    
    void push(int x) {
        while(!queuePop.empty()){
            queuePush.push(queuePop.top());
            queuePop.pop();
        }
        queuePush.push(x);
    }
    
    int pop() {
        int val = peek();
        queuePop.pop();
        return val;
    }
    
    int peek() {
        while(!queuePush.empty()){
            queuePop.push(queuePush.top());
            queuePush.pop();
        }
        return queuePop.top();
    }
    
    bool empty() {
        return queuePop.empty()&&queuePush.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * bool param_4 = obj.empty();
 */
// @lc code=end

