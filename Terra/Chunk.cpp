#include "Chunk.h"

void Chunk::Initialize() 
{
    m_Mesh = Mesh::Create();
}

void Chunk::Generate() 
{
    m_Vertices.clear();
    //m_UVs.clear();
    m_Indices.clear();
    m_FaceCount = 0;

    for (int x = 0; x < 32; ++x) {
        for (int y = 0; y < 32; ++y) {
            for (int z = 0; z < 32; ++z) {
                CreateBlock(glm::ivec3(x, y, z));
            }
        }
    }

    m_Mesh->SetVertices(m_Vertices);
    m_Mesh->SetIndices(m_Indices);
}

void Chunk::CreateBlock(const glm::ivec3& position) 
{
    FaceTop(position);
    FaceBottom(position);
    FaceNorth(position);
    FaceSouth(position);
    FaceEast(position);
    FaceWest(position);
}

void Chunk::FaceTop(const glm::ivec3& position) 
{
    m_Vertices.push_back(glm::vec3(position.x + 0, position.y + 1, position.z + 0));
    m_Vertices.push_back(glm::vec3(position.x + 0, position.y + 1, position.z + 1));
    m_Vertices.push_back(glm::vec3(position.x + 1, position.y + 1, position.z + 1));
    m_Vertices.push_back(glm::vec3(position.x + 1, position.y + 1, position.z + 0));

    CreateTriangles();
}

void Chunk::FaceBottom(const glm::ivec3& position) 
{

}

void Chunk::FaceNorth(const glm::ivec3& position) 
{

}

void Chunk::FaceSouth(const glm::ivec3& position) 
{

}

void Chunk::FaceEast(const glm::ivec3& position) 
{

}

void Chunk::FaceWest(const glm::ivec3& position) 
{

}

void Chunk::CreateTriangles()
{
    m_Indices.push_back(m_FaceCount * 4 + 0);
    m_Indices.push_back(m_FaceCount * 4 + 1);
    m_Indices.push_back(m_FaceCount * 4 + 2);

    m_Indices.push_back(m_FaceCount * 4 + 0);
    m_Indices.push_back(m_FaceCount * 4 + 2);
    m_Indices.push_back(m_FaceCount * 4 + 3);

    m_FaceCount++;
}

void Chunk::Render()
{
    // TODO: Only draw if visible on screen
    m_Mesh->Bind();
    m_Mesh->Draw();
}