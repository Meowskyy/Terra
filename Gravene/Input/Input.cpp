#include "Input.h"

//#include "Rendering/Window.h"
#include <GLFW/glfw3.h>

#include <iostream>

std::map<std::string, float> Input::axisMap;
std::vector<int> Input::keysToMonitor;
Input::KeyState Input::keyStates[512];
Input::KeyState Input::mouseKeyStates[32];

GLFWwindow* Input::m_GLFWwindow;
Window* Input::m_Window;

void Input::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (action)
    {
        case GLFW_PRESS:
            keyStates[key] = Input::KeyState::Pressed;
            keysToMonitor.push_back(key);
            //std::cout << "Key: " << key << " is PRESSED!\n";
            break;
        case GLFW_RELEASE:
            keyStates[key] = Input::KeyState::Released;
            keysToMonitor.push_back(key);
            //std::cout << "Key: " << key << " is RELEASED!\n";
            break;
        default:
            break;
    }
}

void Input::Setup(Window* window) 
{
    if (m_Window != nullptr) return;

    keysToMonitor = std::vector<int>();
    keysToMonitor.reserve(256);

    m_Window = window;
    m_GLFWwindow = window->GetGLFWwindow();
    //glfwSetCursorPosCallback(m_GLFWwindow, GLFWCursorPosCallback);
    glfwSetKeyCallback(m_GLFWwindow, GLFWKeyCallback);
}

const Input& Input::GetInstance() 
{
    static Input input;
    return input;
}

void Input::Update() 
{
    glfwPollEvents();

    for (int i = 0; i < keysToMonitor.size(); i++) 
    {
        int keyIndex = keysToMonitor[i];

        switch (keyStates[keyIndex])
        {
            case Input::KeyState::Pressed:
                //std::cout << "Key: " << key << " is DOWN!\n";
                keysToMonitor.erase(keysToMonitor.begin() + i);
                i--;
                keyStates[keyIndex] = Input::KeyState::Down;
                break;
            case Input::KeyState::Released:
                //std::cout << "Key: " << key << " is NOT PRESSED!\n";
                keysToMonitor.erase(keysToMonitor.begin() + i);
                i--;
                keyStates[keyIndex] = Input::KeyState::NotPressed;
                break;      
            default:
                break;
        }
    }

    static bool isFirstUpdate = true;

    static float oldMouseX;
    static float oldMouseY;

    static double xPos;
    static double yPos;
    glfwGetCursorPos(m_GLFWwindow, &xPos, &yPos);

    if (isFirstUpdate) 
    {
        oldMouseX = xPos;
        oldMouseY = yPos;
        isFirstUpdate = false;
    }

    float diffX = xPos - oldMouseX;
    float diffY = oldMouseY - yPos;

    oldMouseX = xPos;
    oldMouseY = yPos;

    axisMap["Mouse X"] = diffX;
    axisMap["Mouse Y"] = diffY;
}

const float Input::GetAxis(const std::string& axis) 
{
    return axisMap[axis];
}

const bool Input::GetKeyDown(const int key) 
{
    return keyStates[key] == Input::KeyState::Down;
}

const bool Input::GetKeyPressed(const int key) 
{
    return keyStates[key] == Input::KeyState::Pressed;
}

const bool Input::GetKeyReleased(const int key) 
{
    return keyStates[key] == Input::KeyState::Released;
}

const bool Input::GetMouseDown(const int key) 
{
    return false;
}

const bool Input::GetMousePressed(const int key)
{
    return false;
}

const bool Input::GetMouseReleased(const int key) 
{
    return false;    
}