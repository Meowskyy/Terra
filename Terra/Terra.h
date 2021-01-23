#ifndef TERRA_H
#define TERRA_H

#include "Chunk.h"

class Terra {
    private:
        Camera m_Camera;
        Shader* m_ChunkShader;

        int m_RenderDistance = 3;
        std::vector<Chunk> m_Chunks;
    public:
        void Init();
        void RenderChunks();
};

#endif