#include "AABB3D.h"

const bool AABB3D::IsIntersecting(const AABB3D& other) const {
    // SIMD optimized AABB-AABB test
    // Optimized by removing conditional branches
    bool x = glm::abs(m_Center[0] - other.m_Center[0]) <= (m_Half[0] + other.m_Half[0]);
    bool y = glm::abs(m_Center[1] - other.m_Center[1]) <= (m_Half[1] + other.m_Half[1]);
    bool z = glm::abs(m_Center[2] - other.m_Center[2]) <= (m_Half[2] + other.m_Half[2]);
 
    return x && y && z;
}

bool AABB3D::TestAABBIntersection(const AABB3D& a, const AABB3D& b) {
    bool x = glm::abs(a.m_Center[0] - b.m_Center[0]) <= (a.m_Half[0] + b.m_Half[0]);
    bool y = glm::abs(a.m_Center[1] - b.m_Center[1]) <= (a.m_Half[1] + b.m_Half[1]);
    bool z = glm::abs(a.m_Center[2] - b.m_Center[2]) <= (a.m_Half[2] + b.m_Half[2]);
 
    return x && y && z;
}