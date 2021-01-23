#ifndef SHADER_H
#define SHADER_H

#include "glm/glm.hpp"

class Shader {
    protected:
        static Shader* s_Current;
        
    public:
        virtual void Bind() = 0;

        //virtual void SetInt(uint32_t value) = 0;
        //virtual void SetInt2(glm::ivec2 values) = 0;
        //virtual void SetInt3(glm::ivec3 values) = 0;

        //virtual void SetFloat(float value) = 0;
        //virtual void SetVector2(glm::vec2 values) = 0;
        //virtual void SetVector3(glm::vec3 values) = 0;

        virtual void SetMatrix3(const char* name, const glm::mat3& matrix) = 0;
        virtual void SetMatrix4(const char* name, const glm::mat4& matrix) = 0;

    public:
        static Shader* Create(const char* vertexPath, const char* fragmentPath);
};

#endif