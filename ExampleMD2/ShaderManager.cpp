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
#include "ShaderManager.h"

#include <stdexcept>



ShaderManager& ShaderManager::getInstance()
{
    static ShaderManager sm;
    return sm;
}

void ShaderManager::loadVertexShader(const std::string& key, const std::string &filePath)
{
    if (containsVertexShader(key))
    {
        auto msg = "Vertex shader with key '" + key + "' already exists!";
        throw std::runtime_error(msg.c_str());
    }

    auto vertexShader = std::make_unique<Shader>();
    if (!vertexShader->loadShaderFromFile(filePath, GL_VERTEX_SHADER))
    {
        auto msg = "Could not load vertex shader '" + filePath + "'!";
        throw std::runtime_error(msg);
    }

    _vertexShaderCache[key] = std::move(vertexShader);
}

void ShaderManager::loadFragmentShader(const std::string& key, const std::string &filePath)
{
    if (containsFragmentShader(key))
    {
        auto msg = "Fragment shader with key '" + key + "' already exists!";
        throw std::runtime_error(msg.c_str());
    }

    auto fragmentShader = std::make_unique<Shader>();
    if (!fragmentShader->loadShaderFromFile(filePath, GL_FRAGMENT_SHADER))
    {
        auto msg = "Could not load fragment shader '" + filePath + "'!";
        throw std::runtime_error(msg);
    }

    _fragmentShaderCache[key] = std::move(fragmentShader);
}

void ShaderManager::loadGeometryShader(const std::string& key, const std::string& filePath)
{
    /* A not-great way to hide this code without removing it, because GLES 3.1 cannot do geometry shaders.
    if (containsGeometryShader(key))
    {
        auto msg = "Geometry shader with key '" + key + "' already exists!";
        throw std::runtime_error(msg.c_str());
    }

    auto geometryShader = std::make_unique<Shader>();
    if (!geometryShader->loadShaderFromFile(filePath, GL_GEOMETRY_SHADER))
    {
        auto msg = "Could not load geometry shader '" + filePath + "'!";
        throw std::runtime_error(msg);
    }

    _geometryShaderCache[key] = std::move(geometryShader);
    */

    // Remove this if you upgrade to GLES 3.2+ or OGL 4.
    auto msg = "Current GL version does not support geometry shaders!";
    throw std::runtime_error(msg);
}

bool ShaderManager::tryLoadGeometryShader(const std::string& key, const std::string& filePath)
{
    try
    {
        loadGeometryShader(key, filePath);
    }
    catch (const std::exception&)
    {
        return false;
    }

    return true;
}

const Shader& ShaderManager::getVertexShader(const std::string& key) const
{
    if (!containsVertexShader(key))
    {
        auto msg = "Attempting to get non-existing vertex shader with key '" + key + "'!";
        throw std::runtime_error(msg.c_str());
    }

    return *_vertexShaderCache.at(key);
}

const Shader& ShaderManager::getFragmentShader(const std::string& key) const
{
    if (!containsFragmentShader(key))
    {
        auto msg = "Attempting to get non-existing fragment shader with key '" + key + "'!";
        throw std::runtime_error(msg.c_str());
    }

    return *_fragmentShaderCache.at(key);
}

const Shader& ShaderManager::getGeometryShader(const std::string & key) const
{
    if (!containsGeometryShader(key))
    {
        auto msg = "Attempting to get non-existing geometry shader with key '" + key + "'!";
        throw std::runtime_error(msg.c_str());
    }

    return *_geometryShaderCache.at(key);
}

void ShaderManager::clearShaderCache()
{
    _vertexShaderCache.clear();
    _fragmentShaderCache.clear();
    _geometryShaderCache.clear();
}

bool ShaderManager::containsVertexShader(const std::string& key) const
{
    return _vertexShaderCache.count(key) > 0;
}

bool ShaderManager::containsFragmentShader(const std::string& key) const
{
    return _fragmentShaderCache.count(key) > 0;
}

bool ShaderManager::containsGeometryShader(const std::string & key) const
{
    return _geometryShaderCache.count(key) > 0;
}
