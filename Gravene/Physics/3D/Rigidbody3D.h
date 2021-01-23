#ifndef RIGIDBODY3D_H
#define RIGIDBODY3D_H

#include "../Rigidbody.h"

#include "glm/glm.hpp"

class Rigidbody3D : public Rigidbody {
    private:
        float m_Mass = 1;
        glm::vec3 m_Velocity = glm::vec3(0, 0, 0);
        glm::vec3 m_Acceleration = glm::vec3(0, 0, 0);
        float m_Bounciness = 0.5f;
    public:
        Rigidbody3D() = default;
        virtual ~Rigidbody3D() { };

        const float GetMass() const { return m_Mass; }
        void SetMass(float mass) { m_Mass = mass; } 

        const glm::vec3& GetVelocity() const { return m_Velocity; }
        void SetVelocity(const glm::vec3& velocity) { m_Velocity = velocity; }
        void AddVelocity(const glm::vec3& velocity) { m_Velocity += velocity; }

        void SetBounciness(const float bounciness) { m_Bounciness = bounciness; }
        const float GetBounciness() const { return m_Bounciness; }
    
        const bool IsIntersecting(const Rigidbody3D& other) const;

    public:
        static bool AreIntersecting(const Rigidbody3D& a, const Rigidbody3D& b);
};

#endif