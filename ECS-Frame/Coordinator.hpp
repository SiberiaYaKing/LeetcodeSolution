
#pragma once
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

/// @brief ECS协调器，支持ECS与外部的交互
class Coordinator{
public:
    void Init(){
        mComponentManager = std::make_unique<ComponentManager>();
        mEntityManager = std::make_unique<EntityManager>();
        mSystemManager = std::make_unique<SystemManager>();
    }

#pragma region EntityMethod
    Entity CreateEntity(){
        return mEntityManager->CreateEntity();
    }

    void DestroyEntity(Entity entity) {
        mEntityManager->DestroyEntity(entity);
        mComponentManager->EntityDestroyed(entity);
        mSystemManager->EntityDestroyed(entity);
    }
#pragma endregion

#pragma region ComponentMethod
    template<typename T>
    void RegisterComponent() {
        mComponentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        mComponentManager->AddComponent<T>(entity, component);

        Signature signature = mEntityManager->GetSignature(entity);
        signature.set(mComponentManager->GetComponentType<T>(), true);
        mEntityManager->SetSignature(entity,signature);

        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T> 
    void RemoveComponent(Entity entity){
        mComponentManager->RemoveComponent<T>(entity);

        Signature signature = mEntityManager->GetSignature(entity);
        signature.set(mComponentManager->GetComponentType<T>(), false);
        mEntityManager->SetSignature(entity, signature);

        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& GetComponent(Entity entity) {
        return mComponentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType GetComponentType(){
        return mComponentManager->GetComponentType<T>();
    }
#pragma endregion

#pragma region SystemMethod
    template<typename T>
    std::shared_ptr<T> RegisterSystem(){
        return mSystemManager->RegisterSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(Signature signature){
        mSystemManager->SetSignature<T>(signature);
    }

    void UpdateSystems(float dt){
        mSystemManager->UpdateSystems(dt);
    }
#pragma endregion

private:
    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<EntityManager> mEntityManager;
    std::unique_ptr<SystemManager> mSystemManager;
};