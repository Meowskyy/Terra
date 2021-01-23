#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "Collider3D.h"

class SphereCollider : public Collider3D {
    private:
        glm::vec3 center;
        float m_Radius = 1;
    public:
        SphereCollider() = default;
        SphereCollider(float radius) : m_Radius(radius) {}

        const float GetRadius() const { return m_Radius; }
        void SetRadius(const float radius) { m_Radius = radius; }

        const bool IsIntersecting(const SphereCollider& other) const;
    public:
        static bool AreIntersecting(const SphereCollider& a, const SphereCollider& b);
};

#endif