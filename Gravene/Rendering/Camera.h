#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include <iostream>

class Camera : public GameObject {
    private:
        glm::mat4 m_Projection;
        float m_Fov = 70.0f;
        float m_zNear = 0.1f;
        float m_zFar = 1000.0f;

        bool isDirty = true;
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);

        void Recalculate() 
        {
            transform->GetModelMatrix();
            //std::cout << "Camera::RecalculateViewMatrix: " << transform->GetPosition().x << '\n';
            //m_ViewMatrix = glm::translate(glm::mat4(1.0), transform->GetPosition()) * glm::toMat4(transform->GetRotation());

            const glm::vec3 position = transform->GetPosition();
            m_ViewMatrix = glm::lookAt(position, position + transform->GetForward(), glm::vec3(0, 1, 0));
        }
    public:
        Camera() 
        {
            Recalculate();
            UpdateProjection(1280, 720);
        }

        const glm::mat4& GetViewMatrix() { if (isDirty) Recalculate(); return m_ViewMatrix; }
        const glm::mat4& GetProjectionMatrix() const { return m_Projection; }

        void UpdateProjection(const int width, const int height) 
        {
            m_Projection = glm::perspective(glm::radians(m_Fov), (float)width / height, m_zNear, m_zFar); 
        }
};

#endif