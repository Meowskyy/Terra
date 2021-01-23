#ifndef AABB3D_H
#define AABB3D_H

#include "../AABB.h"

#include "glm/glm.hpp"

class AABB3D : public AABB {
    private:
        glm::vec3 m_Center = glm::vec3(0, 0, 0);
        glm::vec3 m_Half = glm::vec3(1, 1, 1);
    public:
        AABB3D() = default;

        AABB3D(const glm::vec3& center, const glm::vec3& halfSize) 
        {
            m_Center = center;
            m_Half = halfSize;
        }

        const bool IsIntersecting(const AABB3D& other) const;

    public:
        static bool TestAABBIntersection(const AABB3D& a, const AABB3D& b);
};

#endif