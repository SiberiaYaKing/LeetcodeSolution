#pragma once
#include <bitset>
#include <set>
#include <unordered_map>
#include <array>
#include <assert.h>
#include <memory>
#include <queue>

using Entity = std::uint32_t;

extern const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;

extern const ComponentType MAX_COMPONENTS = 32;

using ComponentName = const char*;

using Signature = std::bitset<MAX_COMPONENTS>;

class IComponentCluster {
public:
    virtual ~IComponentCluster() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

using SystemName = const char*;

class ISystem {
public:
    std::set<Entity> mEntities;
    virtual ~ISystem() = default;
    virtual void Update(float dt) = 0;
};