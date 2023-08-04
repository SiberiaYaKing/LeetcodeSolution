/*
 * @lc app=leetcode.cn id=146 lang=cpp
 *
 * [146] LRU 缓存
 */

// @lc code=start
#include <unordered_map>
using namespace std;

class Node{
public:
    Node* prev = nullptr;
    Node* next = nullptr;
    int value;
    int key;
    Node(int _k, int _v):key(_k),value(_v){}
};

class DoubleLinkList{
    Node* head = nullptr;
    Node* last = nullptr;
public:
    int size;
    //注意链表头节点的应用，可以解决很多不必要的边界麻烦
    DoubleLinkList():size(0){
        head = new Node(0,0);
        last = new Node(0,0);
        head->next = last;
        last->prev = head;
    }
    ~DoubleLinkList(){
        Node* node = head;
        while(node){
            Node* temp = node;
            node = node->next;
            delete temp;
        }
        head = last = nullptr;
    }

    void PushNode(Node* node){
        if(!node) {return;}
        node->next = last;
        node->prev = last->prev;
        last->prev->next = node;
        last->prev = node;
        size ++;
    }

    void RemoveNode(Node* node){
        if(!node) {return;}
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = node->next = nullptr;
        size--;
    }

    Node* PopNode(){  
        if(!size) {return nullptr;}
        Node* node = head->next;
        RemoveNode(node);
        return node;
    }

    Node* PushNewNode(int k, int v){
        Node* node = new Node(k, v);
        PushNode(node);
        return node;
    }
};

class LRUCache {
    //linkedHashMap
    unordered_map<int,Node*> dict;
    DoubleLinkList list;
    int _capacity;

private:
    Node* GetNode(int key){
        if(dict.count(key)){
            return nullptr; 
        }
        Node* node = dict[key];
        list.RemoveNode(node);
        list.PushNode(node);
        return node;
    }
public:
    LRUCache(int capacity):_capacity(capacity) {}
    ~LRUCache() {dict.clear();}
    
    int get(int key) {
        Node* node = GetNode(key);
        if(!node) {return -1;}
        return node->value;
    }
    
    void put(int key, int value) {
        Node* node = GetNode(key);
        if(node){
            node->value = value;
            return;
        }
        if(_capacity>list.size){
            node = list.PushNewNode(key, value);
        } else {
            node = list.PopNode();
            dict.erase(node->key);
            node->key = key;
            node->value = value; 
            list.PushNode(node);
        }
        dict[key] = node;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

// int main(){
//     LRUCache cache(2);
//     cache.put(1,1);
//     cache.put(2,2);
//     cache.get(1);
//     cache.put(3,3);
//     cache.get(2);
//     cache.put(4,4);
//     cache.get(1);
//     cache.get(3);
//     cache.get(4);
// }