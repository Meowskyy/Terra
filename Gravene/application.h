
#include "Rendering/Window.h"
#include "Rendering/Camera.h"
#include "../Terra/Terra.h"

#include "Rendering/Scene.h"

class Application {
    private:
        Window m_Window;
        Camera m_Camera;
        Terra m_Terra;

        Scene m_Scene;

        glm::mat4 view;
        glm::mat4 projection;

        Shader* gridShader;
        Mesh* gridMesh;

        void CreateGrid();

        void EditorCameraMovement();
        void DrawDebug();
    public:
        Application();
        ~Application();

        void Run();
};