#include "Terra.h"

void Terra::Init() 
{
    m_ChunkShader = Shader::Create("Assets/Shaders/Unlit.vs", "Assets/Shaders/Unlit.fs");
    int totalChunks = (m_RenderDistance * 2 + 1) * (m_RenderDistance * 2 + 1) * (m_RenderDistance * 2 + 1);
    std::cout << "Total Chunks: " << totalChunks << '\n';
    m_Chunks = std::vector<Chunk>();
    m_Chunks.reserve(totalChunks);

    for (int i = 0; i < totalChunks; ++i) 
    {
        m_Chunks.push_back(Chunk());
        m_Chunks[i].Initialize();
    }
}

void Terra::RenderChunks() 
{
    int WIDTH = 1280;
    int HEIGHT = 720;
    glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)WIDTH / HEIGHT, 0.1f, 1000.0f);

    m_ChunkShader->Bind();
    for (auto& chunk : m_Chunks) 
    {
        glm::mat4 view = m_Camera.GetViewMatrix();
        glm::mat4 model = chunk.transform->GetModelMatrix();
        glm::mat4 MVP = projection * view * model;

        m_ChunkShader->SetMatrix4("MVP", MVP);
        chunk.Render();
    }
}