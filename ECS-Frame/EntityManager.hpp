
#pragma once
#include "ECSDefine.h"

/// @brief Entity管理器
class EntityManager {
public:
    EntityManager(){
        // 初始化Entity池
        for(Entity entityId = 0; entityId<MAX_ENTITIES; ++entityId){
            mAvailableEntities.push(entityId);
        }
    }

    Entity CreateEntity() {
        assert(mLivingEntityCount<MAX_ENTITIES && "Too many entities in existance.");
        //从Entity池拿出一个id
        Entity id = mAvailableEntities.front();
        mAvailableEntities.pop();
        ++mLivingEntityCount;
        return id;
    }

    void DestroyEntity(Entity entity) {
        assert( entity < MAX_ENTITIES && "Entity out of range");

        mSignatures[entity].reset();
        //回收id 放在队尾
        mAvailableEntities.push(entity);
        --mLivingEntityCount;
    }

    void SetSignature(Entity entity, Signature signature) {
        assert( entity < MAX_ENTITIES && "Entity out of range");
        mSignatures[entity]  = signature;
    }

    Signature GetSignature(Entity entity){
        assert( entity < MAX_ENTITIES && "Entity out of range");
        return mSignatures[entity];
    }

private:
    //所有未使用的EntityID， Entity池
    std::queue<Entity> mAvailableEntities {};
    //用于管理Entity和的对应的Signature
    std::array<Signature, MAX_ENTITIES> mSignatures {};
    //当前可用的EntityId的数量
    std::uint32_t mLivingEntityCount{};
};