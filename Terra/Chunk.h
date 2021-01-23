#ifndef CHUNK_H
#define CHUNK_H

#include "../Gravene/Gravene.h"

class Chunk : public GameObject {
    private:
        Mesh* m_Mesh;

        uint32_t m_FaceCount = 0;
        std::vector<glm::vec3> m_Vertices;
        //std::vector<glm::vec3> m_UVs;
        std::vector<uint32_t> m_Indices;

        void CreateBlock(const glm::ivec3& position);

        void FaceNorth(const glm::ivec3& position);
        void FaceSouth(const glm::ivec3& position);
        void FaceEast(const glm::ivec3& position);
        void FaceWest(const glm::ivec3& position);
        void FaceTop(const glm::ivec3& position);
        void FaceBottom(const glm::ivec3& position);

        void CreateTriangles();
    public:
        Chunk() {}
        ~Chunk() { delete m_Mesh; }

        void Initialize();
        void Generate();
        void Render();
};

#endif