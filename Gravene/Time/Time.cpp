#include "Time.h"

#include "GLFW/glfw3.h"

#include <iostream>

float Time::m_DeltaTime;

void Time::Update() 
{
    static double time = glfwGetTime();
    static double lastTime = glfwGetTime();

    time = glfwGetTime();

    m_DeltaTime = time - lastTime;

    if (m_DeltaTime > 0.25f)
        m_DeltaTime = 0.25f;

    lastTime = time;
}