#include "ShaderObject.h"

#include <glad/glad.h>
#include <iostream>

#include <fstream>
#include <sstream>

#include "AssetFile.h"


ShaderObject::ShaderObject()
    : vertexShaders_{ 1 }
    , fragmentShaders_{ 1 }
    , shaderProgram_{ glCreateProgram() }
{   }


ShaderObject::ShaderObject(const char* vertexSource, const char* fragmentSource)
    : vertexShaders_{ 1 }
    , fragmentShaders_{ 1 }
    , shaderProgram_{ glCreateProgram() }
{
    if (vertexSource != nullptr)
    {
        SetVertexShader(vertexSource);
    }

    if (fragmentSource != nullptr)
    {
        SetFragmentShader(fragmentSource);
    }

    if (vertexSource != nullptr && fragmentSource != nullptr)
    {
        LinkShaderProgram();
    }
}


ShaderObject::~ShaderObject()
{
    delete shaderData_;
}


void ShaderObject::SetVertexShader(const char* vertexSource)
{
    // Create vertex shader.
    vertexShaders_.push_back(glCreateShader(GL_VERTEX_SHADER));
    unsigned int vertexShader{ vertexShaders_.back() };

    // Load and compile vertex data.
    LoadShaderData(vertexSource);
    glShaderSource(vertexShader, 1, &shaderData_, NULL);
    glCompileShader(vertexShader);

    // Error checking.    
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (success)
    {
        glAttachShader(shaderProgram_, vertexShader);
    }
    else
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Shader compilation error:\n" << infoLog << std::endl;
    }
}


void ShaderObject::SetFragmentShader(const char* fragmentSource)
{
    // Create fragment shader.
    fragmentShaders_.push_back(glCreateShader(GL_FRAGMENT_SHADER));
    unsigned int fragmentShader{ fragmentShaders_.back() };

    // Load and compile fragment data.
    LoadShaderData(fragmentSource);
    glShaderSource(fragmentShader, 1, &shaderData_, NULL);
    glCompileShader(fragmentShader);

    // Error checking.    
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (success)
    {
        glAttachShader(shaderProgram_, fragmentShader);
    }
    else
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment compilation error:\n" << infoLog << std::endl;
    }
}


void ShaderObject::LinkShaderProgram()
{
    glLinkProgram(shaderProgram_);

    // Error checking.
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram_, 512, NULL, infoLog);
        std::cout << "Program linkage error:\n" << infoLog << std::endl;
    }
}


void ShaderObject::Use()
{
    glUseProgram(shaderProgram_);
}


const unsigned int ShaderObject::GetShaderProgram() const
{
    return shaderProgram_;
}


const std::vector<unsigned int>& ShaderObject::GetVertexShaders() const
{
    return vertexShaders_;
}


const std::vector<unsigned int>& ShaderObject::GetFragmentShaders() const
{
    return fragmentShaders_;
}


// [Credit] https://stackoverflow.com/questions/2889421/how-to-copy-a-string-into-a-char-array-in-c-without-going-over-the-buffer
void ShaderObject::LoadShaderData(const char* relativeFilePath)
{
    // Open file and release memory.
    std::ifstream fs(AssetFile::GetPath(relativeFilePath));

    // Prepare output stream and read file buffer.
    std::ostringstream sstream;
    sstream << fs.rdbuf();

    // Copy string to char buffer.
    size_t fileLength{ sstream.str().size() };
    // ... Extra space for null terminator.
    shaderData_ = new char[fileLength + 1];
    sstream.str().copy(shaderData_, fileLength);
    // ... Add null terminator.
    shaderData_[fileLength] = '\0';
}


void ShaderObject::Set1i(const char* name, int i) const
{
    glUniform1i(glGetUniformLocation(shaderProgram_, name), i);
}


void ShaderObject::Set1ui(const char* name, unsigned int i) const
{
    glUniform1ui(glGetUniformLocation(shaderProgram_, name), i);
}


void ShaderObject::Set1f(const char* name, float a) const
{
    glUniform1f(glGetUniformLocation(shaderProgram_, name), a);
}


void ShaderObject::SetVec2f(const char* name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(shaderProgram_, name), x, y);
}


void ShaderObject::SetVec2f(const char* name, const glm::vec2& vector2) const
{
    glUniform2f(glGetUniformLocation(shaderProgram_, name), vector2.x, vector2.y);
}


void ShaderObject::SetVec3f(const char* name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(shaderProgram_, name), x, y, z);
}


void ShaderObject::SetVec3f(const char* name, const glm::vec3& vector3) const
{
    glUniform3f(glGetUniformLocation(shaderProgram_, name), vector3.x, vector3.y, vector3.z);
}


void ShaderObject::SetMat4fv(const char* name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram_, name), 1, GL_FALSE, &mat[0][0]);
}