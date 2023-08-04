
template<class K, class V>
class BSNode{
public:
    BSNode<K,V>* parent;
    BSNode<K,V>* right;
    BSNode<K,V>* left;
    K key;
    V value;
    BSNode(BSNode<K,V>* _p, K _k, V _v): 
        parent(_p),left(nullptr),right(nullptr),key(_k),value(_v){}
    BSNode(K _k, V _v): 
        parent(nullptr),left(nullptr),right(nullptr),key(_k),value(_v){}
    virtual ~BSNode() {}
};

template<class K, class V>
class BSTree{
protected:
    

public:
    BSNode<K, V>* root = nullptr;

protected:
    BSNode<K, V>* LeftRotate(BSNode<K, V>* pivot);
    BSNode<K, V>* RightRotate(BSNode<K, V>* pivot);
    virtual void AdjustAfterInsert(BSNode<K, V>* node) = 0;
    virtual void AdjustAfterRemove(BSNode<K, V>* node) = 0;
    //获取前驱节点
    BSNode<K,V>* Predecessor(BSNode<K,V>* node);
    //获取后继节点
    BSNode<K,V>* Successor(BSNode<K,V>* node);
    BSNode<K,V>* GetNode(K key);

public:
    virtual void Insert(K newKey, V newValue) = 0;
    virtual bool Remove(K key) = 0;
    V GetValue(K key);
    virtual ~BSTree() {}
};

template <class K, class V>
BSNode<K,V>* BSTree<K, V>::GetNode(K key){
    BSNode<K,V>* node = root;
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
V BSTree<K, V>::GetValue(K key){
    BSNode<K,V>* node = GetNode(key);
    if(!node) {
        throw exception("Invalid Key!!!!")
    }
    return node->value;
}

template <class K, class V>
BSNode<K,V>* BSTree<K, V>::Predecessor(BSNode<K,V>* node){
    if(!node) {return nullptr;}
    BSNode<K,V>* temp = node->left;
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
    BSNode<K,V>* lastTemp = nullptr;
    while(temp){
        lastTemp = temp;
        temp = temp->right;
    }
    return lastTemp;
}

template <class K, class V>
BSNode<K,V>* BSTree<K, V>::Successor(BSNode<K,V>* node){
    if(!node) {return nullptr;}
    BSNode<K,V>* temp = node->right;
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
    BSNode<K,V>* lastTemp = nullptr;
    while(temp){
        lastTemp = temp;
        temp = temp->left;
    }
    return lastTemp;
}

template <class K, class V>
BSNode<K, V> *BSTree<K, V>::LeftRotate(BSNode<K, V> *pivot){
    if(!pivot&&!pivot->right) {return nullptr;}
    BSNode<K, V>* newPivot = pivot->right;
    // 变换原轴心的右支为新的轴心
    BSNode<K, V>* parent = pivot->parent;
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
BSNode<K, V>* BSTree<K,V>::RightRotate(BSNode<K, V>* pivot){
    if(!pivot&&!pivot->left) {return nullptr;}
    BSNode<K, V>* newPivot = pivot->left;  
    //变换原轴心的左支为新的轴心
    BSNode<K, V>* parent = pivot->parent;
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