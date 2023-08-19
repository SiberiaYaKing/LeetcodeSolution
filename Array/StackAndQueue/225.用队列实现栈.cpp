/*
 * @lc app=leetcode.cn id=225 lang=cpp
 *
 * [225] 用队列实现栈
 */

// @lc code=start
#include <queue>
using namespace std;

/**Gain:
 * 队列实现栈比较简单，出栈需要将队列头不断往后面塞，
 * 直到队尾推到头，弹出即可
*/

class MyStack {
    queue<int> stackSoul;
public:
    MyStack() {

    }
    
    void push(int x) {
        stackSoul.push(x);
    }
    
    int pop() {
        for(int size=stackSoul.size(); size>1; size--){
            int val = stackSoul.front();
            stackSoul.pop();
            stackSoul.push(val);
        }
        int val = stackSoul.front();
        stackSoul.pop();
        return val;
    }
    
    int top() {
        int val = pop();
        stackSoul.push(val);
        return val;
        //return stackSoul.back();
    }
    
    bool empty() {
        return stackSoul.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
// @lc code=end

