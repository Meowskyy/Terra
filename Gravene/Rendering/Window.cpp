#include "Window.h"

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>

Window::Window() 
{
    m_GLFWwindow = glfwCreateWindow(m_Width, m_Height, "Gravene", nullptr, nullptr);
}

Window::Window(const int width, const int height) 
{
    m_Width = width;
    m_Height = height;

    m_GLFWwindow = glfwCreateWindow(m_Width, m_Height, "Gravene", nullptr, nullptr);
}

void Window::SetWindowSize(const int width, const int height) 
{
    m_Width = width;
    m_Height = height;

    glfwSetWindowSize(m_GLFWwindow, m_Width, m_Height);
}

void Window::SetWindowName(const char* name) 
{
    glfwSetWindowTitle(m_GLFWwindow, name);
}

void Window::SetContext() 
{
    glfwMakeContextCurrent(m_GLFWwindow);
}

void Window::SwapBuffers() 
{
    glfwSwapBuffers(m_GLFWwindow);
}

const int Window::GetWindowWidth() const 
{
    return m_Width;
}

const int Window::GetWindowHeight() const
{
    return m_Height;
}