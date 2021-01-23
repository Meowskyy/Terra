#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Collider.h"
#include "Transform.h"

#include <iostream>

class Rigidbody {
    private:
        std::vector<Collider*> m_Colliders;
        const Transform& m_Transform;
    public:
        Rigidbody() : m_Transform(Transform()) { std::cout << "Constructor\n"; }
        Rigidbody(Transform& transform) : m_Transform(transform) {}

        //Rigidbody(const Rigidbody& t) : m_Transform(Transform()) { std::cout << "Copy ctor\n"; }                         // copy ctor
        //Rigidbody& operator=(const Rigidbody& t) { std::cout << "Copy assign\n"; }              // copy assign

        //Rigidbody(Rigidbody&& t) : m_Transform(Transform()) { std::cout << "Move ctor\n"; }                              // move ctor
        //Rigidbody &operator=(Rigidbody&& t) { std::cout << "Move Assign\n"; }                   // move assign

        virtual ~Rigidbody()
        {
            for (auto collider : m_Colliders) 
            {
                delete collider;
            }
        }

        /// <summary> Returns the first collider on the rigidbody </summary>
        const Collider* GetCollider() const { return m_Colliders[0]; }
        /// <summary> Returns a vector of all the colliders on the rigidbody </summary>
        const std::vector<Collider*> GetColliders() const { return m_Colliders; }
        void SetCollider(Collider* collider, const int index) { m_Colliders[index] = collider; }
        void AddCollider(Collider* collider) { m_Colliders.emplace_back(collider); }
};

#endif