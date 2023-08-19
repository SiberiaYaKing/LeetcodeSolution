
#pragma once
#include "ECSDefine.h"

/// @brief 类型为T的Component集群
/// @tparam T Component类型
template<typename T>
class ComponentCluster: public IComponentCluster {
public:
    void InsertComponentData(Entity entity, T component){
        assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

        //新增的Entity加在数组末尾，并更新映射
        size_t newIndex = mSize;
        mEntityToIndexMap[entity] = newIndex;
        mIndexToEntityMap[newIndex] = entity;
        mComponentArray[newIndex] = component;
        ++mSize;
    }

    void RemoveComponentData(Entity entity){
        assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");
        // 将最后一个元素放到被删除的位置，以保持数组数据的紧凑性
        size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
        size_t indexOfLastEntity = mSize - 1;
        std::swap(mComponentArray[indexOfRemovedEntity] , mComponentArray[indexOfLastEntity]);

        //更新映射
        Entity entityOfLastElement = mIndexToEntityMap[indexOfLastEntity];
        mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
        --mSize;
    }

    T& GetComponentData(Entity entity) {
        assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

        // 返回Component的引用
        return mComponentArray[mEntityToIndexMap[entity]];
    }

    void EntityDestroyed(Entity entity) override {
        if(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()){
            RemoveComponentData(entity);
        }
    }

private:
    //类型为T的Component数组
    std::array<T, MAX_ENTITIES> mComponentArray;
    // 以下用了两个字典存储，由于Entity是递增数字，感觉可以用定长数组来优化，空间消耗换取字典缓存命中的时间消耗
    // EntityId到组件索引的映射
    std::unordered_map<Entity, size_t> mEntityToIndexMap;
    // 组件索引到Entity的映射
    std::unordered_map<size_t, Entity> mIndexToEntityMap;
    // *********************************************************************************

    // T类型组件有效Entity的数量
    size_t mSize;
};

/// @brief Component管理器
class ComponentManager {
public:
    template<typename T>
    void RegisterComponent() {
        ComponentName typeName = typeid(T).name();
        assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");

        mComponentTypes[typeName] = mNextComponentType;
        mComponentClusters[typeName] = std::make_shared<ComponentCluster<T>>();
        ++mNextComponentType;
    }

    template<typename T>
    ComponentType GetComponentType() {
        ComponentName typeName = typeid(T).name();
        assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registerd before use.");
        return mComponentTypes[typeName];
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        GetComponentCluster<T>()->InsertComponentData(entity,component);
    }

    template<typename T>
    void RemoveComponent(Entity entity){
        GetComponentCluster<T>()->RemoveComponentData(entity);
    }

    template<typename T>
    T& GetComponent(Entity entity) {
        return GetComponentCluster<T>()->GetComponentData(entity);
    }

    void EntityDestroyed(Entity entity) {
        for(const auto& pair: mComponentClusters){
            auto& component = pair.second;
            component->EntityDestroyed(entity);
        }
    }

private:
    //管理所有的ComponentType
    std::unordered_map<ComponentName,ComponentType> mComponentTypes {};

    //管理所有的ComponentCluster
    std::unordered_map<ComponentName, std::shared_ptr<IComponentCluster>> mComponentClusters {};

    //指向下一个要注册的ComponentType
    ComponentType mNextComponentType {};

    //根据类型获取ComponentCluster
    template<typename T>
    std::shared_ptr<ComponentCluster<T>> GetComponentCluster() {
        ComponentName typeName = typeid(T).name();
        assert(mComponentTypes.find(typeName)!=mComponentTypes.end() && "Component not registered before use.");
        return std::static_pointer_cast<ComponentCluster<T>>(mComponentClusters[typeName]);
    }

};