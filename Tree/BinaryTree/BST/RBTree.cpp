#include <iostream>
#include <queue>
#include <string>
using namespace std;

template<class K, class V>
class RBTree{
    enum Color{
        Reimu = 0, //红色
        Marisa= 1, //黑色
    };

    template<class K, class V>
    class RBNode{
    public:
        RBNode<K,V>* parent;
        RBNode<K,V>* right;
        RBNode<K,V>* left;
        K key;
        V value;
        Color color;
        RBNode(RBNode<K,V>* _p, K _k, V _v, Color _c): 
            parent(_p),left(nullptr),right(nullptr),key(_k),value(_v),color(_c){}
        RBNode(K _k, V _v, Color _c): 
            parent(nullptr),left(nullptr),right(nullptr),key(_k),value(_v),color(_c){}
    };
    
public:
    RBNode<K, V>* root = nullptr;

private:
    RBNode<K, V>* LeftRotate(RBNode<K, V>* pivot);
    RBNode<K, V>* RightRotate(RBNode<K, V>* pivot);
    void AdjustAfterInsert(RBNode<K, V>* node);
    void AdjustAfterRemove(RBNode<K, V>* node);
    inline Color ColorOf(RBNode<K,V>* node) {
        return node? node->color: Color::Marisa;
    }
    //获取前驱节点
    RBNode<K,V>* Predecessor(RBNode<K,V>* node);
    //获取后继节点
    RBNode<K,V>* Successor(RBNode<K,V>* node);
    RBNode<K,V>* GetNode(K key);
    void DeleteNode(RBNode<K,V>* node);

public:
    void Insert(K newKey, V newValue);
    bool Remove(K key);
    V GetValue(K key);
    void Print(RBNode<K,V>* node);
};

/**删除策略：
 * 将待删除节点与后继节点交换，然后再删掉交换后的节点，此时删除操作只会改变其等价4阶B树的叶子节点
 * 删除节点分三种情况：
 * 1. 叶子节点直接删除，但是删了黑色的节点需要变换红黑树
 * 2. 删除的节点只有一个字节点，用这个子节点代替被删除的节点
 * 3. 删除的节点有两个子节点，需要找到该节点的前驱或后继节点来替代
*/
template <class K, class V>
void RBTree<K, V>::DeleteNode(RBTree<K, V>::RBNode<K,V>* node){
    if(!node) {return;}
    //情况3 寻找后继节点，交换节点值，然后将后继节点作为真正删掉的节点
    if(node->left && node->right){
        RBNode<K, V>* replacement = Successor(node);
        node->key = replacement->key;
        node->value = replacement->value;
        node = replacement;
    }
    
    RBNode<K,V>* child = node->left?node->left:node->right;
    //后继节点存在子节点，需要处理删除后的其子节点归属，也兼容情况2
    if(child){
        child->parent = node->parent;
        //删掉的节点是根节点，则子节点直接变为根节点
        if(!node->parent) {root = child;}
        //处理子节点的归属关系
        else if(node==node->parent->left){
            node->parent->left = child;
        }else {
            node->parent->right = child;
        }
        //被删节点与树脱钩
        node->left = node->right = node->parent = nullptr;
        if(ColorOf(child) == Color::Reimu){
            AdjustAfterRemove(child);
        }  
    }
    //替代节点无效的情况
    //被删节点是根节点
    else if(!node->parent){
        root = nullptr;
    }else { // 情况1 被删节点是叶子节点
        if(ColorOf(node) == Color::Marisa){
            AdjustAfterRemove(node);
        }
        if(node == node->parent->left){
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
        node->parent = nullptr;
    }
    delete node;
    node = nullptr;
}

template <class K, class V>
RBTree<K, V>::RBNode<K,V>* RBTree<K, V>::GetNode(K key){
    RBNode<K,V>* node = root;
    while(node){
        if(key<node->key){
            node = node->left;
        } else if(key>node->key){
            node = node->right;
        } else if(key==node->key){
            return node;
        }
    }
    return nullptr;
}

template <class K, class V>
bool RBTree<K, V>::Remove(K key){
    RBNode<K,V>* node = GetNode(key);
    if(!node) {return false;}
    DeleteNode(node);
    return true;;
}


template <class K, class V>
V RBTree<K, V>::GetValue(K key){
    RBNode<K,V>* node = GetNode(key);
    if(!node) {
        throw exception("Invalid Key!!!!")
    }
    return node->value;
}

template <class K, class V>
RBTree<K, V>::RBNode<K,V>* RBTree<K, V>::Predecessor(RBTree<K, V>::RBNode<K,V>* node){
    if(!node) {return nullptr;}
    RBNode<K,V>* temp = node->left;
    //没有左子树就往上找，直到节点值小于目标值，然而删除节点的时候不会调用到...
    if(!temp){
        temp = temp->parent;
        while(temp){
            if(temp->key<node->key){
                break;
            }
            temp = temp->parent;
        }
        return temp;
    }
    //有左子树就找左子树节点的最大值(沿左子树一直向右)
    RBNode<K,V>* lastTemp = nullptr;
    while(temp){
        lastTemp = temp;
        temp = temp->right;
    }
    return lastTemp;
}

template <class K, class V>
RBTree<K, V>::RBNode<K,V>* RBTree<K, V>::Successor(RBTree<K, V>::RBNode<K,V>* node){
    if(!node) {return nullptr;}
    RBNode<K,V>* temp = node->right;
    //没有右子树，直到节点值大于目标值，然而删除节点的时候不会调用到...
    if(!temp){
        temp = temp->parent;
        while(temp){
            if(temp->key>node->key){
                break;
            }
            temp = temp->parent;
        }
        return temp;
    }
    //有右子树就找右子树的最小值(沿右子树一直向左)
    RBNode<K,V>* lastTemp = nullptr;
    while(temp){
        lastTemp = temp;
        temp = temp->left;
    }
    return lastTemp;
}

template <class K, class V>
RBTree<K, V>::RBNode<K, V> *RBTree<K, V>::LeftRotate(RBTree<K, V>::RBNode<K, V> *pivot){
    if(!pivot&&!pivot->right) {return nullptr;}
    RBNode<K, V>* newPivot = pivot->right;
    // 变换原轴心的右支为新的轴心
    RBNode<K, V>* parent = pivot->parent;
    if(parent){
        if(parent->left == pivot){
            parent->left = newPivot;
        }
        else if(parent->right == pivot){
            parent->right = newPivot;
        }
    }
    newPivot->parent = parent;
    //新轴心的左支过继给原轴心作为其右支
    pivot->right = newPivot->left;
    if(newPivot->left){
        newPivot->left->parent = pivot;
    }
    //原轴心变成新轴心的左支
    newPivot->left = pivot;
    pivot->parent = newPivot;
    if(!newPivot->parent){
        root = newPivot;
    }
    return newPivot;
}

template<class K, class V>
RBTree<K,V>::RBNode<K, V>* RBTree<K,V>::RightRotate(RBTree<K,V>::RBNode<K, V>* pivot){
    if(!pivot&&!pivot->left) {return nullptr;}
    RBNode<K, V>* newPivot = pivot->left;  
    //变换原轴心的左支为新的轴心
    RBNode<K, V>* parent = pivot->parent;
    if(parent){
        if(parent->left == pivot){
            parent->left = newPivot;
        }
        else if(parent->right == pivot){
            parent->right = newPivot;
        }
    }
    newPivot->parent = parent;
    //新轴心的右支过继给原轴心作为其左支
    pivot->left = newPivot->right;
    if(newPivot->right){
        newPivot->right->parent = pivot;
    }
    //原轴心变成新轴心的右支
    newPivot->right = pivot;
    pivot->parent = newPivot;
    if(!newPivot->parent){
        root = newPivot;
    }
    return newPivot;
}

template<class K, class V>
void RBTree<K,V>::Insert(K newKey, V newValue){
    RBNode<K, V>* node = root;
    if(!node){ //根节点直接设为黑节点，返回掉
        root = new RBNode<K, V>(newKey, newValue, Color::Marisa);
        return;
    }
    //寻找插入位置
    RBNode<K, V>* lastNode = nullptr;
    while(node){
        lastNode = node;
        if(newKey<node->key){
            node = node->left;
        } else if(newKey>node->key){
            node = node->right;
        } else {
            node->value = newValue;
            return;
        }
    }
    //插入到寻找到的位置去
    node = new RBNode<K, V>(lastNode,newKey, newValue, Color::Reimu);
    if(newKey<lastNode->key){
        lastNode->left = node;
    } else if(newKey>lastNode->key){
        lastNode->right = node;
    }
    node->parent = lastNode;
    //重头戏来了，调整节点
    AdjustAfterInsert(node);
}

/** 红黑树的添加节点调整情况：
 * 1. 4阶b树：2阶节点添加一个key，比对节点的key找到插入位置，形成新的3阶节点 =>
 *      红黑树：新增红节点+黑父节点 ---- 不同调整树
 * 
 * 2. 4阶b树：3阶节点添加一个key，比对节点的key找到插入位置，形成新的4阶节点 =>
 *      红黑树：情况比较复杂，分6种可能性：
 *          新增红节点在左支+黑父节点 ---- 不用调整树
 *          新增红节点在右支+黑父节点 ---- 同上
 *          新增红节点在左支+红父节点(该节点在黑爷节点左支，且不存在红叔节点) ---- LL型，右旋黑爷节点，新根节点变黑，原根节点变红
 *          新增红节点在右支+红父节点(该节点在黑爷节点右支，且不存在红叔节点) ---- RR型，左旋黑爷节点，变色操作同上
 *          新增红节点在左支+红父节点(该节点在黑爷节点右支，且不存在红叔节点) ---- LR型，左旋红父节点，然后再按LL型操作
 *          新增红节点在右支+红父节点(该节点在黑爷节点左支，且不存在红叔节点) ---- RL型，右旋红父节点，然后再按RR型操作
 * 
 * 3. 4阶b树：4节点添加一个key，需要从中间分裂节点形成三个相连的2阶节点，然后将新key插入到子2阶节点中 =>
 *      红黑树：新增红节点+红父节点(存在红叔节点) ---- 红父节点与红叔节点变黑，黑爷节点变红，若是根节点，则再变成黑色
*/
template<class K, class V>
void RBTree<K,V>::AdjustAfterInsert(RBNode<K, V>* node){
    if(!node) { return; }
    while(node && node!=root){
        RBNode<K, V>* parent = node->parent;
        RBNode<K, V>* grandParent = parent->parent;
        //父节点是黑节点，不用调整树
        if(ColorOf(parent)==Color::Marisa){
            break;
        }
    
        //节点变色的情况，对应红黑树调整大类3
        if(ColorOf(grandParent->left)==Color::Reimu&&ColorOf(grandParent->right)==Color::Reimu){
            grandParent->color=Color::Reimu;
            grandParent->left->color = Color::Marisa;
            grandParent->right->color = Color::Marisa;
            node = grandParent;
            continue;
        }

        //需要旋转树的情况，对应红黑树调整大类2
        if(ColorOf(grandParent->left)==Color::Reimu&&ColorOf(grandParent->right)==Color::Marisa){
            if(ColorOf(parent->right)==Color::Reimu){
                parent = LeftRotate(parent);
            }
            RightRotate(grandParent);
        } else if(ColorOf(grandParent->right)==Color::Reimu&&ColorOf(grandParent->left)==Color::Marisa){
            if(ColorOf(parent->left)==Color::Reimu){
                parent = RightRotate(parent);
            }
            LeftRotate(grandParent); 
        }
        parent->color = Color::Marisa;
        grandParent->color = Color::Reimu;
    }
    if(node==root){
        node->color = Color::Marisa;
    }
}

/**删除节点后调整树：
 * 由于删除节点的操作将待删除节点转换到等价B树的叶子节点，调整操作本质上是对这些节点做调整，
 *      使它符合4阶B树结构，也就符合红黑树结构
 * 1. 4阶B树：3阶与4阶叶子节点删除一个元素 =>
 *      红黑树： 删红节点则不用调整，删黑节点则需要在左右任拿一个红节点变黑来补上删空的位置
 * 2. 4阶B树：2阶节点删除一个元素，由于2阶节点只有一个元素，整个2阶节点删除，然后分两种情况：
 *          情况一：被删节点的兄弟节点有多余元素，则拉下父节点某个元素填删空位置，
 *              然后将兄弟节点元素顶上去形成新的父节点
 *          情况二：被删节点的兄弟节点无多余元素，则拉下父节点某个元素去填删空位置，
 *              如果该父节点被拉空，则继续向上拿父节点继续下拉，直到填上被删节点的坑(递归过程)
 *      红黑树：根据等价性质，被删的节点一定是黑色：
 *          等价情况一：
 *              被删节点位于右支，先看左兄弟节点颜色，如果是红色，先左旋父节点(3阶节点的等价转换)，找到正确的左兄弟节点，调整节点颜色
 *               如果左兄弟节点没有右支，还需要右旋左兄弟节点(3阶节点的等价转换)，形成左兄弟的右支，然后再对父节点左旋
 *              被删节点位于左支，同理
 *          等价情况二：
 *              将兄弟节点变红，如果父节点不为红，则对父节点递归调用AdjustAfterRemove，持续调整，直到遇到父节点为红或者遇到根节点
*/
template<class K, class V>
void RBTree<K,V>::AdjustAfterRemove(RBTree<K,V>::RBNode<K, V>* node){
    if(!node) { return; }
    RBNode<K,V>* temp = node;
    //2. 被删节点黑色
    while(temp!=root && ColorOf(temp)!=Color::Reimu) {
        RBNode<K,V>* parent = temp->parent;
        if(temp == parent->left){
            RBNode<K,V>* rNode = parent->right;
            //等价B树中兄弟节点没有元素可借的情形
            if(ColorOf(rNode->left)==Color::Marisa && ColorOf(rNode->right)==Color::Marisa){
                rNode->color = Color::Reimu;
                temp = parent;
                continue;
            }
            //等价B树中兄弟节点有元素可借的情形
            //兄弟节点红色，需要做一次3阶节点等价转换
            if(ColorOf(rNode) == Color::Reimu){
                LeftRotate(parent);
                rNode->color = Color::Marisa;
                parent->color = Color::Reimu;
                rNode = parent->right;
            }
            //兄弟节点的同支子节点为空，需要做一次3阶节点等价转换
            if(!rNode->right){
                rNode = RightRotate(rNode);
                rNode->color = Color::Marisa;
                rNode->right->color = Color::Reimu;
            }
            LeftRotate(parent);
            rNode->color = parent->color;
            rNode->left->color = Color::Marisa;
            rNode->right->color = Color::Marisa;
        } else if (temp == parent->right){
            RBNode<K,V>* lNode = parent->left;
            //等价B树中兄弟节点没有元素可借的情形
            if(ColorOf(lNode->left)==Color::Marisa && ColorOf(lNode->right)==Color::Marisa){
                lNode->color = Color::Reimu;
                temp = parent;
                continue;
            }
            //等价B树中兄弟节点有元素可借的情形
            //兄弟节点红色，需要做一次3阶节点等价转换
            if(ColorOf(lNode) == Color::Reimu){
                RightRotate(parent);
                lNode->color = Color::Marisa;
                parent->color = Color::Reimu;
                lNode = parent->left;
            }
            //兄弟节点的同支子节点为空，需要做一次3阶节点等价转换
            if(!lNode->left){
                lNode = LeftRotate(lNode);
                lNode->color = Color::Marisa;
                lNode->left->color = Color::Reimu;
            }
            RightRotate(parent);
            lNode->color = parent->color;
            lNode->right->color = Color::Marisa;
            lNode->left->color = Color::Marisa;
        }
        temp = root;
    }
    // 1. 节点是红色，需要变色
    temp->color = Color::Marisa;
}

template<class K, class V>
void RBTree<K,V>::Print(RBTree<K,V>::RBNode<K,V>* node){
    if(!node) { return;}
    Print(node->left);
    string str = "|";
    if(node == root){
        str += "根";
    }
    if(node->color==Color::Marisa){
        str+="黑";
    } else if(node->color==Color::Reimu){
        str+="红";
    }
    if(node->right&&node->left){
        str += "lr";
    }else if(node->right){
        str += "r";
    }else if(node->left){
        str += "l";
    }
    cout<<node->key<<str<<", ";
    Print(node->right);
}


int main(){
    RBTree<float,int> tree;
    tree.Insert(1,1);
    tree.Print(tree.root);
    cout<<endl;
    tree.Insert(2,2);
    tree.Print(tree.root);
    cout<<endl;
    tree.Insert(3,3);
    tree.Print(tree.root);
    cout<<endl;
    tree.Insert(4,3);
    tree.Print(tree.root);
    cout<<endl;
    tree.Insert(5,3);
    tree.Print(tree.root);
    cout<<endl;
    tree.Insert(6,3);
    tree.Print(tree.root);
    cout<<endl;
    tree.Insert(7,3);
    tree.Print(tree.root);
    cout<<endl;
    tree.Insert(8,3);
    tree.Print(tree.root);
    cout<<endl;
    tree.Insert(9,3);
    tree.Print(tree.root);
    cout<<endl;
    tree.Insert(8.5,3);
    tree.Print(tree.root);
    cout<<endl;

    tree.Remove(7);
    tree.Print(tree.root);
    cout<<endl;

    tree.Remove(1);
    tree.Print(tree.root);
    cout<<endl;
    return 0;
}