/*
MIT License

Copyright (c) 2019 Michal Bubnár

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
#pragma once

#include <vector>
#include <string>

#include <glm/glm/glm.hpp>
#include <GLES3/gl31.h>


// Forward class declaration of ShaderProgram (because of cross-inclusion)
class ShaderProgram;

/**
 * Wraps OpenGL shader uniform variable.
 */
class Uniform
{
public:
    Uniform() = default; // Required to work with ShaderProgram [] operator
    Uniform(const std::string& name, ShaderProgram* shaderProgram);

    // Family of functions setting vec2 uniforms
    Uniform& operator=(const glm::vec2& vector2D);
    void set(const glm::vec2& vector2D) const;
    void set(const glm::vec2* vectors2D, GLsizei count = 1) const;

    // Family of functions setting vec3 uniforms
    Uniform& operator=(const glm::vec3& vector3D);
    void set(const glm::vec3& vector3D) const;
    void set(const glm::vec3* vectors3D, GLsizei count = 1) const;

    // Family of functions setting vec4 uniforms
    Uniform& operator=(const glm::vec4& vector4D);
    void set(const glm::vec4& vector4D) const;
    void set(const glm::vec4* vectors4D, GLsizei count = 1) const;

    // Family of functions setting float uniforms
    Uniform& operator=(GLfloat floatValue);
    Uniform& operator=(const std::vector<GLfloat>& floatValues);
    void set(GLfloat floatValue) const;
    void set(const GLfloat* floatValues, GLsizei count = 1) const;

    // Family of functions setting integer uniforms
    Uniform& operator=(GLint integerValue);
    void set(GLint integerValue) const;
    void set(const GLint* integerValues, GLsizei count = 1) const;

    // Family of functions setting 3x3 matrices uniforms
    Uniform& operator=(const glm::mat3& matrix);
    void set(const glm::mat3& matrix) const;
    void set(const glm::mat3* matrices, GLsizei count = 1) const;

    // Family of functions setting 4x4 matrices uniforms
    Uniform& operator=(const glm::mat4& matrix);
    void set(const glm::mat4& matrix) const;
    void set(const glm::mat4* matrices, GLsizei count = 1) const;

private:
    std::string name_; // Name of the uniform variable
    ShaderProgram* shaderProgram_{ nullptr }; // Pointer to shader program this uniform belongs to
    GLint location_{ -1 }; // OpenGL assigned uniform location (cached in this variable)
};
