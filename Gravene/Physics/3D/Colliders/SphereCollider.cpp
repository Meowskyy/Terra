#include "SphereCollider.h"

const bool SphereCollider::IsIntersecting(const SphereCollider& other) const 
{
    float distance = glm::sqrt((center.x - other.center.x) * (center.x - other.center.x) +
                            (center.y - other.center.y) * (center.y - other.center.y) +
                            (center.z - other.center.z) * (center.z - other.center.z));
    return distance < (m_Radius + other.m_Radius);
}

bool SphereCollider::AreIntersecting(const SphereCollider& a, const SphereCollider& b) 
{
    float distance = glm::sqrt((a.center.x - b.center.x) * (a.center.x - b.center.x) +
                        (a.center.y - b.center.y) * (a.center.y - b.center.y) +
                        (a.center.z - b.center.z) * (a.center.z - b.center.z));
    return distance < (a.m_Radius + b.m_Radius);
}