#ifndef PHYSICSWORLD3D_H
#define PHYSICSWORLD3D_H

#include "../PhysicsWorld.h"

#include "glm/glm.hpp"

#include <vector>

#include "Rigidbody3D.h"

class PhysicsWorld3D : public PhysicsWorld {
    private:
        glm::vec3 m_Gravity = glm::vec3(0, -9.81, 0);

        std::vector<Rigidbody3D> m_Rigidbodies;
    public:
        const glm::vec3 GetGravity() const { return m_Gravity; };
        void SetGravity(const glm::vec3& gravity) { m_Gravity = gravity; };

        void AddRigidbody(Rigidbody3D& rigidbody) { m_Rigidbodies.emplace_back(rigidbody); }

        PhysicsWorld3D();
        ~PhysicsWorld3D();
        void Update() override;
};

#endif