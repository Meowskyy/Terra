#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/quaternion.hpp"

#include <iostream>

class Transform {
    private:
        bool isDirty = true;

        glm::vec3 m_Position = glm::vec3(0, 0, 0);
        glm::quat m_Rotation = glm::quat();
        glm::vec3 m_Scale = glm::vec3(1, 1, 1);

        glm::vec3 m_Forward;
        glm::vec3 m_Up;
        glm::vec3 m_Right;

        glm::mat4 m_ModelMatrix;
    private:
        void Recalculate() 
        {
            glm::mat4 rot = glm::toMat4(m_Rotation); 
            m_ModelMatrix = glm::translate(glm::mat4(1.0), m_Position) * rot * glm::scale(glm::mat4(1.0), m_Scale);

            glm::mat4 inverted = glm::inverse(rot);
            m_Up = normalize(glm::vec3(inverted[1]));
            m_Forward = normalize(glm::vec3(inverted[2]));
            m_Right = -normalize(glm::vec3(inverted[0]));
            
            isDirty = false;
        }
    public:
        Transform() = default;
        Transform(const glm::vec3& position) 
        {
            m_Position = position;
        }

        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& position) 
        { 
            //std::cout << "Transform::SetPosition: " << position.x << '\n';
            m_Position = position; 
            isDirty = true; 
        }

        const glm::quat& GetRotation() const { return m_Rotation; }
        void SetRotation(const glm::quat& rotation) { m_Rotation = rotation; isDirty = true; }
        void SetEulerAngles(const glm::vec3& eulerAngles) 
        {
            glm::quat QuatAroundX = glm::angleAxis(glm::radians(eulerAngles.x), glm::vec3(1.0, 0.0, 0.0));
            glm::quat QuatAroundY = glm::angleAxis(glm::radians(eulerAngles.y), glm::vec3(0.0, 1.0, 0.0));
            glm::quat QuatAroundZ = glm::angleAxis(glm::radians(eulerAngles.z), glm::vec3(0.0, 0.0, 1.0));
            m_Rotation = QuatAroundX * QuatAroundY * QuatAroundZ;
            isDirty = true;
        }

        const glm::vec3& GetScale() const { return m_Scale; }
        void SetScale(const glm::vec3& scale) { m_Scale = scale; isDirty = true; }

        const glm::mat4& GetModelMatrix() { if (isDirty) Recalculate(); return m_ModelMatrix; }

        const glm::vec3 GetForward() const { return m_Forward; }
        const glm::vec3 GetUp() const { return m_Up; }
        const glm::vec3 GetRight() const { return m_Right; }
};

#endif