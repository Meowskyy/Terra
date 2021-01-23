#include "ShaderOpenGL.h"

#include "glad/glad.h"

#include <istream>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

void checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

ShaderOpenGL::ShaderOpenGL(const char* vertexPath, const char* fragmentPath) 
{
    std::cout << "SHADER::VERTEX::LOADING - " << vertexPath << '\n';
    std::cout << "SHADER::FRAGMENT::LOADING - " << fragmentPath << '\n';

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    m_ProgramId = glCreateProgram();
    glAttachShader(m_ProgramId, vertex);
    glAttachShader(m_ProgramId, fragment);
    glLinkProgram(m_ProgramId);
    checkCompileErrors(m_ProgramId, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void ShaderOpenGL::Bind() 
{ 
    s_Current = this;
    glUseProgram(m_ProgramId); 
}

void ShaderOpenGL::SetMatrix3(const char* name, const glm::mat3& matrix) 
{
    if (m_UniformLocations.count(name) == 0) 
    {
        m_UniformLocations[name] = glGetUniformLocation(m_ProgramId, name);
    }

    glUniformMatrix3fv(m_UniformLocations[name], 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderOpenGL::SetMatrix4(const char* name, const glm::mat4& matrix) 
{
    if (m_UniformLocations.count(name) == 0) 
    {
        m_UniformLocations[name] = glGetUniformLocation(m_ProgramId, name);
    }

    glUniformMatrix4fv(m_UniformLocations[name], 1, GL_FALSE, glm::value_ptr(matrix));
}