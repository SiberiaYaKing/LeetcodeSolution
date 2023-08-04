/*
 * @lc app=leetcode.cn id=460 lang=cpp
 *
 * [460] LFU 缓存
 */

//@lc code=start
#include <unordered_map>
#include <list>
using namespace std;

template<class T>
class LinkedHashSet{
    list<T> m_list;
    unordered_map<T, typename list<T>::iterator> dict;
public:
    ~LinkedHashSet(){
        m_list.clear();
        dict.clear();
    }

    void Insert(T key){
        if(dict.count(key)) {return;}
        m_list.push_back(key);
        dict[key] = --m_list.end();
    }

    bool Remove(T key){
        if(!dict.count(key)) {return false;}
        m_list.erase(dict[key]);
        dict.erase(key);
        return true;
    }

    T Pop() {
        T key = m_list.front();
        if(Remove(key)){
            return key;
        }
        throw;
    }

    bool IsEmpty(){
        return m_list.empty()||dict.empty();
    }

    bool HasKey(T key){
        return dict.count(key);
    }

};

/**算法就像搭乐高，模块化构筑，对于复杂算法流程实现的技巧
 * 1. 不要企图上来就实现算法的所有细节，应该自顶向下，逐步求精，先写清楚主函数逻辑，然后再一步步实现细节
 * 2. 搞清楚映射关系，如果更新了key对应的freq，那么就需要同步修改KF表和FK表，这样才不会出问题
 * 3. 画图、画图、画图，把逻辑比较复杂的部分用流程图画出来，然后根据图来写代码，可以极大减少出错的概率
*/
class LFUCache {

    unordered_map<int, int> keyToVal;
    unordered_map<int, int> keyToFreq;
    unordered_map<int, LinkedHashSet<int>> freqToKeys;
    int minFreq;
    int capacity;

private: 
    void increaseFreq(int key){
        if(!keyToFreq.count(key) || !keyToVal.count(key)){
            return;
        }
        int oldFreq = keyToFreq[key];
        int newFreq = ++keyToFreq[key];
        if(freqToKeys.count(oldFreq)) {
            //注意!!!!!，C++存在默认拷贝，如果需要操作原容器对象，应该考虑使用引用或者指针
            LinkedHashSet<int>& oldFreqKeys =freqToKeys[oldFreq];
            if(oldFreqKeys.HasKey(key)){
                oldFreqKeys.Remove(key);
            }
            if(oldFreqKeys.IsEmpty()){
                freqToKeys.erase(oldFreq);
                if(oldFreq == minFreq){
                    minFreq = oldFreq+1;
                }
            }
        }
        if(!freqToKeys.count(newFreq)){
            freqToKeys[newFreq] = LinkedHashSet<int>();
        }
        freqToKeys[newFreq].Insert(key);
    }

    void removeMinFreqKey(){
        if(!freqToKeys.count(minFreq)) {return;}
        //注意!!!!!，C++存在默认拷贝，如果需要操作原容器对象，应该考虑使用引用或者指针
        LinkedHashSet<int>& minFreqKeys = freqToKeys[minFreq];
        int removedKey = -1;
        if(!minFreqKeys.IsEmpty()){
            removedKey = minFreqKeys.Pop();
        }
        if(removedKey == -1){
            freqToKeys.erase(minFreq);
        } else{
            keyToVal.erase(removedKey);
            keyToFreq.erase(removedKey);
        }
    }

public:
    LFUCache(int _capacity):capacity(_capacity),minFreq(0) {}
    ~LFUCache() {
        keyToVal.clear();
        keyToFreq.clear();
        freqToKeys.clear();
    }
    
    int get(int key) {
        if(!keyToVal.count(key)){
            return -1;
        }
        increaseFreq(key);
        return keyToVal[key];
    }
    
    void put(int key, int value) {
        if(get(key)!=-1){
            keyToVal[key] = value;
            return;
        }
        if(keyToVal.size()>=capacity){
            removeMinFreqKey();
        }
        keyToVal[key] = value;
        keyToFreq[key] = 1;
        if(!freqToKeys.count(1)){
            freqToKeys.insert({1, LinkedHashSet<int>()});
        }
        freqToKeys[1].Insert(key);
        minFreq = 1;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end