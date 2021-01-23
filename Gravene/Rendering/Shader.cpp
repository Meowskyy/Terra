#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/ShaderOpenGL.h"
//#include "Platform/DX12/ShaderDX12.h"
//#include "Platform/Vulkan/ShaderVulkan.h"

Shader* Shader::s_Current;

Shader* Shader::Create(const char* vertexPath, const char* fragmentPath) 
{
    switch(Renderer::s_RendererAPI) 
    {
        case RendererAPI::OpenGL:
            return new ShaderOpenGL(vertexPath, fragmentPath);
        //case RendererAPI::DX12:
            //return new ShaderDX12();
        //case RendererAPI::Vulkan:
            //return new ShaderVulkan();
    }

    return nullptr;
}