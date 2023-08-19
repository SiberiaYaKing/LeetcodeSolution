#pragma once
#include "ECSDefine.h"

/// @brief System管理器
class SystemManager {
public:
    template<typename T> 
    std::shared_ptr<T> RegisterSystem(){
        SystemName typeName = typeid(T).name();
        assert(mSystems.find(typeName)== mSystems.end() && "Registering system more than once.");
        auto system = std::make_shared<T>();
        mSystems[typeName] = system;
        return system;
    }

    template<typename T>
    void SetSignature(Signature signature){
        SystemName typeName = typeid(T).name();
        assert(mSystems.find(typeName)!=mSystems.end() && "System used before registered.");

        //设置System的签名，该签名描述了该System包含哪些Component
        mSignatures[typeName] = signature;
    }

    void EntityDestroyed(Entity entity) {
        for(const auto& pair: mSystems) {
            auto& system = pair.second;
            system->mEntities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature) {
        for(const auto& pair: mSystems){
            SystemName typeName = pair.first;
            auto& system = pair.second;
            auto& systemSignature = mSignatures[typeName];

            // 如果entity包含了System所需的所有Component
            if((entitySignature & systemSignature) == systemSignature){
                system->mEntities.insert(entity);
            } else { //否则删除该entity (说明此时System需要的某些Component没有被该Entity包含) 此时System无法处理该Entity
                system->mEntities.erase(entity);
            }
        }
    }

    void UpdateSystems(float dt){
        for(const auto& pair: mSystems){
            auto& system = pair.second;
            system->Update(dt);
        }
    }

private:
    //包含所有Entity的签名
    std::unordered_map<SystemName,Signature> mSignatures {};
    //包含所有的System对象
    std::unordered_map<SystemName, std::shared_ptr<ISystem>> mSystems{};
};