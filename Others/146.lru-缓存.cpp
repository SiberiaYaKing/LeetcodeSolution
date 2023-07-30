/*
 * @lc app=leetcode.cn id=146 lang=cpp
 *
 * [146] LRU 缓存
 */

// @lc code=start
class Node{
public:
    Node* prev;
    Node* next;
    int value;
    int key;
    Node(int _k, int _v):key(_k),value(_v),prev(nullptr),next(nullptr){}
};

class DoubleLinkList{
    Node* last;
public:
    int size;
    DoubleLinkList():size(0){}
    void PushNode(Node* node){
        if(!node) {return;}
        node->prev = last;
        last = node;
        size ++;
    }

    void RemoveNode(Node* node){
        if(!node) {return;}
        node->prev->next = nullptr;
        
        size--;
    }
};

class LRUCache {
public:
    LRUCache(int capacity) {

    }
    
    int get(int key) {

    }
    
    void put(int key, int value) {

    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

