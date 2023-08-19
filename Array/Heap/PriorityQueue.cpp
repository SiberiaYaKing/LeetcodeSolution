#include <iostream>
#include <vector>
#include <functional>
using namespace std;

/**
 * 用堆实现优先队列，核心模拟二叉树时，根节点索引与左右索引的数量关系
 * 上浮操作比较简单，下沉操作还需要比较左右节点的大小，选取极值来交换
*/
template<class T>
class PriorityQueue{
    using Compare = function<bool(T,T)>;
    vector<T> array;
    Compare compareFunc;
public:
    PriorityQueue(Compare func): array(vector<T>()), compareFunc(func){}
    PriorityQueue(int cap, Compare func): array(vector<T>(cap)),compareFunc(func){}
    inline bool IsEmpty() const {return array.empty();}
    inline int Size() const {return array.size();}
    inline const T& Top() const {return array.front();}
    T Pop();
    void Insert(T val);
private:
    inline int LeftIndex(int index) const {return index*2+1;}
    inline int RightIndex(int index) const {return index*2+2;}
    inline int ParentIndex(int index) const {return (index-1)>>1;}
    void Swim(int index);
    void Sink(int index);
};

template <class T>
T PriorityQueue<T>::Pop()
{
    swap<T>(array[0],array[Size()-1]);
    T res = array.back();
    array.pop_back();
    Sink(0);
    return res;
}

template <class T>
void PriorityQueue<T>::Insert(T val)
{
    array.push_back(val);
    Swim(Size()-1);
}

template <class T>
void PriorityQueue<T>::Swim(int index)
{
    int pIndex = ParentIndex(index);
    while(index>0&&compareFunc(array[pIndex],array[index])){
        swap<T>(array[pIndex],array[index]);
        index = pIndex;
        pIndex = ParentIndex(index);
    }
}

template <class T>
void PriorityQueue<T>::Sink(int index)
{
    int mIndex = LeftIndex(index);
    while(mIndex < Size()) {
        int rIndex = RightIndex(index);
        if(rIndex < Size() && compareFunc(array[mIndex],array[rIndex])){
            mIndex = rIndex;
        }
        if(compareFunc(array[mIndex],array[index])) {break;}
        swap<T>(array[index],array[mIndex]);
        index = mIndex;
        mIndex = LeftIndex(index);
    }
}

int main(){
    PriorityQueue<float> q([](float a, float b) {return a>b;});
    q.Insert(1);
    q.Insert(2);
    q.Insert(3);
    q.Insert(4);
    q.Insert(5);
    q.Insert(2.5);
    q.Insert(3.3);
    q.Insert(1.3);
    q.Insert(4.3);
    q.Insert(0.5);
    
    cout<<q.Pop()<<"  ";
    cout<<q.Size()<<endl;
    cout<<q.Pop()<<"  ";
    cout<<q.Size()<<endl;
    cout<<q.Pop()<<"  ";
    cout<<q.Size()<<endl;
    cout<<q.Pop()<<"  ";
    cout<<q.Size()<<endl;
    cout<<q.Pop()<<"  ";
    cout<<q.Size()<<endl;
    cout<<q.Pop()<<"  ";
    cout<<q.Size()<<endl;
    cout<<q.Pop()<<"  ";
    cout<<q.Size()<<endl;
    cout<<q.Pop()<<"  ";
    cout<<q.Size()<<endl;
    cout<<q.Pop()<<"  ";
    cout<<q.Size()<<endl;
    cout<<q.Pop()<<"  ";
    cout<<q.Size()<<endl;
}