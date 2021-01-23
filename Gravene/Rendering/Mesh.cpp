#include "Mesh.h"

#include "Renderer.h"

#include "Platform/OpenGL/MeshOpenGL.h"
//#include "Platform/DX12/MeshDX12.h"
//#include "Platform/Vulkan/MeshVulkan.h"

Mesh* Mesh::Create() 
{
    switch(Renderer::s_RendererAPI) 
    {
        case RendererAPI::OpenGL:
            return new MeshOpenGL();
        //case RendererAPI::DX12:
            //return new MeshDX12();
        //case RendererAPI::DX12:
            //return new MeshVulkan();
    }

    return nullptr;
}