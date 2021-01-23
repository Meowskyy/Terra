#include "../../Mesh.h"

#include <iostream>

class MeshOpenGL : public Mesh {
    private:
        std::vector<glm::vec3> m_Vertices;
        std::vector<uint32_t> m_Indices;
        std::vector<glm::vec2> m_UVs;

        uint32_t m_VAO, m_VBO, m_EBO;
    public:
        MeshOpenGL() 
        {
            std::cout << "Created mesh!\n";

            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);
            glGenBuffers(1, &m_EBO);
        }

        ~MeshOpenGL() 
        {
            std::cout << "Deleted mesh!\n";
            glDeleteVertexArrays(1, &m_VAO);
            glDeleteBuffers(1, &m_VBO);
            glDeleteBuffers(1, &m_EBO);
        }

        void SetVertices(const std::vector<glm::vec3>& vertices) override
        {
            m_Vertices = vertices;

            std::cout << "OpenGL::MESH::SetVertices\n";

            glBindVertexArray(m_VAO);

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
            glEnableVertexAttribArray(0);

            // UNBIND TO MAKE SURE SO OTHER CALLS DONT MODIFY THIS
            // TODO: NOT 100% SURE IF NECESSARY
            glBindVertexArray(0);
        }

        void SetIndices(const std::vector<uint32_t>& indices) override
        {
            m_Indices = indices;

            std::cout << "OpenGL::MESH::SetIndices\n";

            glBindVertexArray(m_VAO);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

            // UNBIND TO MAKE SURE SO OTHER CALLS DONT MODIFY THIS
            // TODO: NOT 100% SURE IF NECESSARY
            glBindVertexArray(0);
        }

        void SetData(const std::vector<glm::vec3>& vertices, const std::vector<uint32_t>& indices) 
        {
            m_Vertices = vertices;
            m_Indices = indices;

            std::cout << "OpenGL::MESH::SetData\n";

            glBindVertexArray(m_VAO);

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
            glEnableVertexAttribArray(0);

            // UNBIND TO MAKE SURE SO OTHER CALLS DONT MODIFY THIS
            // TODO: NOT 100% SURE IF NECESSARY
            glBindVertexArray(0);
        }

        void Bind() override
        {
            glBindVertexArray(m_VAO);
        }

        void Draw() override
        {
            glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
        }
};