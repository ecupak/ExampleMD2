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
#include "ShaderProgram.h"

#include <iostream>


ShaderProgram::~ShaderProgram()
{
    deleteProgram();
}

void ShaderProgram::createProgram()
{
    shaderProgramID_ = glCreateProgram();
}

bool ShaderProgram::addShaderToProgram(const Shader& shader) const
{
    if (!shader.isCompiled())
        return false;

    glAttachShader(shaderProgramID_, shader.getShaderID());
    return true;
}

bool ShaderProgram::linkProgram()
{
	if (_isLinked) {
		return true;
	}

    // Try to link program and get the link status
    glLinkProgram(shaderProgramID_);
    GLint linkStatus;
    glGetProgramiv(shaderProgramID_, GL_LINK_STATUS, &linkStatus);
    _isLinked = linkStatus == GL_TRUE;

    if (!_isLinked)
    {
        std::cerr << "Error! Shader program wasn't linked!";

        // Get length of the error log first
        GLint logLength;
        glGetProgramiv(shaderProgramID_, GL_INFO_LOG_LENGTH, &logLength);

        // If there is some log, then retrieve it and output extra information
        if (logLength > 0)
        {
            GLchar* logMessage = new GLchar[logLength];
            glGetProgramInfoLog(shaderProgramID_, logLength, nullptr, logMessage);
            std::cerr << " The linker returned: " << std::endl << std::endl << logMessage;
            delete[] logMessage;
        }

        std::cerr << std::endl;
        return false;
    }

    return _isLinked;
}

void ShaderProgram::useProgram() const
{
    if (_isLinked) {
        glUseProgram(shaderProgramID_);
    }
}

void ShaderProgram::deleteProgram()
{
    if (shaderProgramID_ == 0) {
        return;
    }

    std::cout << "Deleting shader program with ID " << shaderProgramID_ << std::endl;
    glDeleteProgram(shaderProgramID_);
    _isLinked = false;
}

GLuint ShaderProgram::getShaderProgramID() const
{
    return shaderProgramID_;
}

Uniform& ShaderProgram::operator[](const std::string& varName)
{
    if (_uniforms.count(varName) == 0)
    {
        _uniforms[varName] = Uniform(varName, this);
    }

    return _uniforms[varName];
}

// Model and normal matrix setting is pretty common, that's why this convenience function

void ShaderProgram::setModelAndNormalMatrix(const glm::mat4& modelMatrix)
{
    (*this)[ShaderConstants::modelMatrix()] = modelMatrix;
    (*this)[ShaderConstants::normalMatrix()] = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
}

GLuint ShaderProgram::getUniformBlockIndex(const std::string& uniformBlockName) const
{
    if (!_isLinked)
    {
        std::cerr << "Cannot get index of uniform block " << uniformBlockName << " when program has not been linked!" << std::endl;
        return GL_INVALID_INDEX;
    }

    const auto result = glGetUniformBlockIndex(shaderProgramID_, uniformBlockName.c_str());
    if (result == GL_INVALID_INDEX) {
        std::cerr << "Could not get index of uniform block " << uniformBlockName << ", check if such uniform block really exists!" << std::endl;
    }

    return result;
}

void ShaderProgram::bindUniformBlockToBindingPoint(const std::string& uniformBlockName, const GLuint bindingPoint) const
{
    const auto blockIndex = getUniformBlockIndex(uniformBlockName);
    if (blockIndex != GL_INVALID_INDEX) {
        glUniformBlockBinding(shaderProgramID_, blockIndex, bindingPoint);
    }
}

void ShaderProgram::setTransformFeedbackRecordedVariables(const std::vector<std::string>& recordedVariablesNames, const GLenum bufferMode) const
{
	std::vector<const char*> recordedVariablesNamesPtrs;
	for (const auto& recordedVariableName : recordedVariablesNames) {
		recordedVariablesNamesPtrs.push_back(recordedVariableName.c_str());
	}

	glTransformFeedbackVaryings(shaderProgramID_, static_cast<GLsizei>(recordedVariablesNamesPtrs.size()), recordedVariablesNamesPtrs.data(), bufferMode);
}
