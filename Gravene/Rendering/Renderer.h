#ifndef RENDERER_H
#define RENDERER_H

enum class RendererAPI {
    OpenGL,
    //DX12,
    //Vulkan
};

class Renderer {
    public:
        static RendererAPI s_RendererAPI;
};

#endif