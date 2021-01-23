#include "PhysicsWorld3D.h"

#include <iostream>

PhysicsWorld3D::PhysicsWorld3D() {
    std::cout << "Physics::World Initialized\n";

    Rigidbody3D rb = Rigidbody3D();
    AddRigidbody(rb);
}

PhysicsWorld3D::~PhysicsWorld3D() {

}

void PhysicsWorld3D::Update() {
    for (auto& rb : m_Rigidbodies) 
    {
        //rb.AddVelocity(m_Gravity);
        //std::cout << rb.GetVelocity().x << ", " << rb.GetVelocity().y << ", " << rb.GetVelocity().z << '\n';
    }
}