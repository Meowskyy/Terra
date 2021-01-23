#ifndef MESH_H
#define MESH_H

#include "glm/glm.hpp"
#include <vector>

#include "glad/glad.h"

class Mesh {
    private:

    public:
        Mesh() = default;

        virtual void SetVertices(const std::vector<glm::vec3>& vertices) = 0;
        virtual void SetIndices(const std::vector<uint32_t>& indices) = 0;
        virtual void SetData(const std::vector<glm::vec3>& vertices, const std::vector<uint32_t>& indices) = 0;
        //virtual void SetUVs(const std::vector<glm::vec2>& uvs) = 0;
        //virtual void SetUVs(const std::vector<glm::vec3>& uvs) = 0;

        virtual void Bind() = 0;
        virtual void Draw() = 0;

    public:
        static Mesh* Create();
};

#endif