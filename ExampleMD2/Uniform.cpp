/*
MIT License

Copyright (c) 2019 Michal Bubn�r

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
// [Credit] https://github.com/michalbb1/opengl4-tutorials-mbsoftworks
// [Credit] https://www.mbsoftworks.sk/tutorials/opengl4/030-animation-pt1-keyframe-md2/
// With minor modifications to fit this project.
#include "Uniform.h"

#include <iostream>

#include "ShaderProgram.h"


Uniform::Uniform(const std::string& name, ShaderProgram* shaderProgram)
    : name_(name)
    , shaderProgram_(shaderProgram)
{
    location_ = glGetUniformLocation(shaderProgram_->getShaderProgramID(), name_.c_str());
    if (location_ == -1)
    {
        std::cout << "WARNING: uniform with name " << name << " does not exist, setting it will fail!" << std::endl;
    }
}

Uniform& Uniform::operator=(const glm::vec2& vector2D)
{
    set(vector2D);
    return *this;
}

// Family of functions setting vec2 uniforms

void Uniform::set(const glm::vec2& vector2D) const
{
    glUniform2fv(location_, 1, reinterpret_cast<const GLfloat*>(&vector2D));
}

void Uniform::set(const glm::vec2* vectors2D, GLsizei count) const
{
    glUniform2fv(location_, count, reinterpret_cast<const GLfloat*>(vectors2D));
}

// Family of functions setting vec3 uniforms

Uniform& Uniform::operator=(const glm::vec3& vector3D)
{
    set(vector3D);
    return *this;
}

void Uniform::set(const glm::vec3& vector3D) const
{
    glUniform3fv(location_, 1, reinterpret_cast<const GLfloat*>(&vector3D));
}

void Uniform::set(const glm::vec3* vectors3D, GLsizei count) const
{
    glUniform3fv(location_, count, reinterpret_cast<const GLfloat*>(vectors3D));
}

// Family of functions setting vec4 uniforms

Uniform& Uniform::operator=(const glm::vec4& vector4D)
{
    set(vector4D);
    return *this;
}

void Uniform::set(const glm::vec4& vector4D) const
{
    glUniform4fv(location_, 1, reinterpret_cast<const GLfloat*>(&vector4D));
}

void Uniform::set(const glm::vec4* vectors4D, GLsizei count) const
{
    glUniform4fv(location_, count, reinterpret_cast<const GLfloat*>(vectors4D));
}

// Family of functions setting float uniforms

Uniform& Uniform::operator=(const GLfloat floatValue)
{
    set(floatValue);
    return *this;
}

Uniform& Uniform::operator=(const std::vector<GLfloat>& floatValues)
{
    set(floatValues.data(), static_cast<GLsizei>(floatValues.size()));
    return *this;
}

void Uniform::set(GLfloat floatValue) const
{
    glUniform1fv(location_, 1, static_cast<const GLfloat*>(&floatValue));
}

void Uniform::set(const GLfloat* floatValues, GLsizei count) const
{
    glUniform1fv(location_, count, floatValues);
}

// Family of functions setting integer uniforms

Uniform& Uniform::operator=(const GLint integerValue)
{
    set(integerValue);
    return *this;
}

void Uniform::set(GLint integerValue) const
{
    glUniform1iv(location_, 1, static_cast<const GLint*>(&integerValue));
}

void Uniform::set(const GLint* integerValues, GLsizei count) const
{
    glUniform1iv(location_, count, integerValues);
}

// Family of functions setting 3x3 matrices uniforms

Uniform& Uniform::operator=(const glm::mat3& matrix)
{
    set(matrix);
    return *this;
}

void Uniform::set(const glm::mat3& matrix) const
{
    glUniformMatrix3fv(location_, 1, false, reinterpret_cast<const GLfloat*>(&matrix));
}

void Uniform::set(const glm::mat3* matrices, GLsizei count) const
{
    glUniformMatrix3fv(location_, count, false, reinterpret_cast<const GLfloat*>(matrices));
}

// Family of functions setting 4x4 matrices uniforms

Uniform& Uniform::operator=(const glm::mat4& matrix)
{
    set(matrix);
    return *this;
}

void Uniform::set(const glm::mat4& matrix) const
{
    glUniformMatrix4fv(location_, 1, false, reinterpret_cast<const GLfloat*>(&matrix));
}

void Uniform::set(const glm::mat4* matrices, GLsizei count) const
{
    glUniformMatrix4fv(location_, count, false, reinterpret_cast<const GLfloat*>(matrices));
}
