#include "application.h"

// TODO: Better way of setting up window manager
#define GRAVENE_GRAPHICS_API_OPENGL

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

// PHYSICS
#include "Physics/3D/PhysicsWorld3D.h"

// RENDERING
#include "Rendering/Camera.h"
#include "Rendering/Shader.h"
#include "Rendering/Mesh.h"
#include "Rendering/Window.h"

#include "Input/Input.h"
#include "Time/Time.h"

// IMGUI
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

Application::Application() 
{
    std::cout << "Application starting!\n";

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW!\n"; 
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = Window(WIDTH, HEIGHT);
    m_Window.SetWindowName("Gravene");

    if (!m_Window.GetGLFWwindow()) {
        glfwTerminate();
        std::cout << "Failed to create GLFWwindow!\n";
        return;
    }

    m_Window.SetContext();
    //glfwSwapInterval( 0 );
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD!\n";
        return;
    }

    Input::Setup(&m_Window);
}

Application::~Application() {
    glfwTerminate();
}

void Application::Run() {
    std::cout << "Application running!\n";

    m_Scene = Scene();
    PhysicsWorld3D physicsWorld = PhysicsWorld3D();

    m_Camera.transform->SetPosition(glm::vec3(0, 5, -10));

    Transform transform = Transform(glm::vec3(0, 0, 10));
    Shader* shader = Shader::Create("Assets/Shaders/Unlit.vs", "Assets/Shaders/Unlit.fs");
    Mesh* mesh = Mesh::Create();

    std::vector<glm::vec3> cubeVerts = 
    {
        // front
        glm::vec3(-1.0, -1.0,  1.0),
        glm::vec3( 1.0, -1.0,  1.0),
        glm::vec3( 1.0,  1.0,  1.0),
        glm::vec3(-1.0,  1.0,  1.0),
        // back
        glm::vec3(-1.0, -1.0, -1.0),
        glm::vec3( 1.0, -1.0, -1.0),
        glm::vec3( 1.0,  1.0, -1.0),
        glm::vec3(-1.0,  1.0, -1.0)
    };

    std::vector<uint32_t> cubeIndices = 
    {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};
    
    mesh->SetData(cubeVerts, cubeIndices);

    // WIREFRAME
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    //glViewport(0, 0, 640, 480);

    float x = 0;
    float y = 0;
    float time = 0;

    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const int maxFramerate = 144;
    const float frameUpdateTime = 1.0f / maxFramerate;
    float lastUpdate = 0;
    float lastFrameTime = 0;

    CreateGrid();

    // Setup Dear ImGui context
    const char* glsl_version = "#version 130";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool mouseVisible = true;
    while (!glfwWindowShouldClose(m_Window.GetGLFWwindow())) 
    {
        Time::Update();
        physicsWorld.Update();

        float now = glfwGetTime();

        EditorCameraMovement();

        time = glfwGetTime();
        x = glm::sin(time) * 90;
        y = glm::cos(time) * 90;
        transform.SetPosition(glm::vec3(0, glm::sin(time), 10));
        transform.SetEulerAngles(glm::vec3(x, y, 0));

        if (Input::GetKeyPressed(GLFW_KEY_ESCAPE)) 
        {
            if (mouseVisible) 
            {
                glfwSetInputMode(m_Window.GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
            } 
            else 
            {
                glfwSetInputMode(m_Window.GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);  
            }

            mouseVisible = !mouseVisible;
        }


        // RENDERING WITH FRAMERATE LIMITS
        if ((now - lastFrameTime) >= frameUpdateTime) 
        {
                // Start the Dear ImGui frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }



            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(m_Window.GetGLFWwindow(), &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);

            glEnable(GL_CULL_FACE);

            glClearColor(0, 0.33, 0.6, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            projection = m_Camera.GetProjectionMatrix();
            view = m_Camera.GetViewMatrix();

            m_Scene.Draw(m_Camera);

            glm::mat4 MVP = projection * view * transform.GetModelMatrix();
            shader->Bind();
            shader->SetMatrix4("MVP", MVP);
            mesh->Bind();
            mesh->Draw();

            DrawDebug();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            // Update and Render additional Platform Windows
            // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
            //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }

            m_Window.SwapBuffers();

            lastFrameTime = now;
        }

        lastUpdate = now;
        Input::Update();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Application::CreateGrid() 
{
    std::vector<glm::vec3> gridVerts = 
    {   
        glm::vec3(1, 1, 0),      // 0
        glm::vec3(-1, -1, 0),    // 1
        glm::vec3(-1, 1, 0),     // 2
        glm::vec3(1, -1, 0)      // 3
    };

    std::vector<uint32_t> gridIndices = 
    {
        0, 1, 2, 1, 0, 3
    };

    gridShader = Shader::Create("Assets/Shaders/Editor/Grid.vs", "Assets/Shaders/Editor/Grid.fs");
    gridMesh = Mesh::Create();
    gridMesh->SetData(gridVerts, gridIndices);
}

void Application::DrawDebug() 
{
        glDisable(GL_CULL_FACE);
        // GRID
        gridShader->Bind();
        gridShader->SetMatrix4("view", view);
        gridShader->SetMatrix4("projection", projection);
        gridMesh->Bind();
        gridMesh->Draw();
}

void Application::EditorCameraMovement() 
{
    glm::vec3 axis = glm::vec3(0);

    if (Input::GetKeyDown(GLFW_KEY_D)) axis.x++;
    if (Input::GetKeyDown(GLFW_KEY_A)) axis.x--;
    if (Input::GetKeyDown(GLFW_KEY_W)) axis.y++;
    if (Input::GetKeyDown(GLFW_KEY_S)) axis.y--;

    float dt = Time::GetDeltaTime();

    glm::vec3 position = m_Camera.transform->GetPosition(); 
    glm::vec3 movement = m_Camera.transform->GetForward() * axis.y + m_Camera.transform->GetRight() * axis.x;
    glm::vec3 finalPosition = position + movement * dt * 10.0f;

    glm::vec3 forward = m_Camera.transform->GetForward();

    m_Camera.transform->SetPosition(finalPosition);

    // Camera Rotation
    static float x = 0;
    static float y = 0;

    x += Input::GetAxis("Mouse X") * dt * 180;
    y += Input::GetAxis("Mouse Y") * dt * 180;

    if (y >= 89) y = 89;
    if (y <= -89) y = -89;

    m_Camera.transform->SetEulerAngles(glm::vec3(y, x, 0));
}