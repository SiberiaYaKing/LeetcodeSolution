#include <chrono>
#include <iostream>
#include <random>
#include "ECSDefine.h"
#include "Coordinator.hpp"
using namespace std;

Coordinator gCoordinator;

struct Vec3{
    Vec3 operator *(float fac){
        return {x*fac, y*fac, z*fac};
    }

    Vec3 operator+( Vec3 v){
        return {x+v.x,y+v.y,z+v.z};
    }

public:
    float x, y ,z;
};

struct Gravity{
    Vec3 force;
};

struct RigidBody {
    Vec3 velocity;
    Vec3 acceleration;
};

struct Transform {
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
};

class DropSystem : public ISystem{
    void Update(float dt){
        cout << "======================== tick ===========================" <<endl;
        for(const auto& entity: mEntities){
            RigidBody& rigidBody = gCoordinator.GetComponent<RigidBody>(entity);
            Transform& transform = gCoordinator.GetComponent<Transform>(entity);
            Gravity& gravity = gCoordinator.GetComponent<Gravity>(entity);

            transform.position = transform.position + rigidBody.velocity * dt;
            rigidBody.velocity = rigidBody.velocity + gravity.force * dt;
            cout<< "entity " << entity << " droping... pos: {" <<transform.position.x <<", "<<transform.position.y<<", "<<transform.position.z<<"}"<<endl;
        }
        cout <<"<<<<<<<<<<<<<<<<<<<<<<<<< tick >>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
        cout <<endl;
    }
};

int main(){
    gCoordinator.Init();
    
    gCoordinator.RegisterComponent<Gravity>();
    gCoordinator.RegisterComponent<RigidBody>();
    gCoordinator.RegisterComponent<Transform>();

    auto dropSystem = gCoordinator.RegisterSystem<DropSystem>();

    Signature signature;
    signature.set(gCoordinator.GetComponentType<Gravity>());
    signature.set(gCoordinator.GetComponentType<RigidBody>());
    signature.set(gCoordinator.GetComponentType<Transform>());
    gCoordinator.SetSystemSignature<DropSystem>(signature);

    std::vector<Entity> entities(200);

    std::default_random_engine generator;
    std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
    std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
    std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
    std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);
    float scale = randScale(generator);

    for(auto& entity: entities){
        entity = gCoordinator.CreateEntity();

        gCoordinator.AddComponent(entity,Gravity{{0,randGravity(generator), 0}});
        gCoordinator.AddComponent(entity, RigidBody{ {0,0,0},{0,0,0} });
        gCoordinator.AddComponent(entity, Transform{
            {randPosition(generator), randPosition(generator), randPosition(generator)},
            {randRotation(generator), randRotation(generator), randRotation(generator)},
            {scale, scale, scale}
        });
    }

    float dt = 0.0f;

    while (true) {
        auto startTime = std::chrono::high_resolution_clock::now();
        //dropSystem->Update(dt);
        gCoordinator.UpdateSystems(dt);
        auto stopTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
    }
}