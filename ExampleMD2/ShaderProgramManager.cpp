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
#include "ShaderProgramManager.h"

#include <stdexcept>


ShaderProgramManager& ShaderProgramManager::getInstance()
{
    static ShaderProgramManager spm;
    return spm;
}

ShaderProgram& ShaderProgramManager::createShaderProgram(const std::string& key)
{
    if (containsShaderProgram(key))
    {
        auto msg = "Shader program with key '" + key + "' already exists!";
        throw std::runtime_error(msg.c_str());
    }

    auto shaderProgram = std::make_unique<ShaderProgram>();
    shaderProgram->createProgram();
    _shaderProgramCache[key] = std::move(shaderProgram);
    
    return getShaderProgram(key);
}

ShaderProgram& ShaderProgramManager::getShaderProgram(const std::string& key) const
{
    if (!containsShaderProgram(key))
    {
        auto msg = "Attempting to get non-existing shader program with key '" + key + "'!";
        throw std::runtime_error(msg.c_str());
    }

    return *_shaderProgramCache.at(key);
}

void ShaderProgramManager::linkAllPrograms()
{
    for (const auto& keyShaderProgramPair : _shaderProgramCache)
    {
        if (!keyShaderProgramPair.second->linkProgram()) {
            auto msg = "Could not link shader program with key '" + keyShaderProgramPair.first + "'!";
            throw std::runtime_error(msg.c_str());
        }
    }
}

void ShaderProgramManager::clearShaderProgramCache()
{
    _shaderProgramCache.clear();
}

bool ShaderProgramManager::containsShaderProgram(const std::string& key) const
{
    return _shaderProgramCache.count(key) > 0;
}
