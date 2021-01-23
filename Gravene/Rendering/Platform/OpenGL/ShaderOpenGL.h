#include "../../Shader.h"

#include <cstdint>
#include <unordered_map>
#include <string>

class ShaderOpenGL : public Shader {
    private:
        uint32_t m_ProgramId;
        std::unordered_map<std::string, unsigned int> m_UniformLocations;
    public:
        ShaderOpenGL(const char* vertexPath, const char* fragmentPath);

        void SetMatrix3(const char* name, const glm::mat3& matrix) override;
        void SetMatrix4(const char* name, const glm::mat4& matrix) override;

        void Bind() override;
};