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
#pragma once

#include <string>
#include <map>
#include <memory>

#include <GLES3/gl31.h>

#include "Shader.h"


/**
 * Singleton class that manages and keeps track of all shaders in the program.
 */
class ShaderManager
{
public:
    /**
     * Gets the one and only instance of the shader manager.
     */
    static ShaderManager& getInstance();

    /**
     * Creates new vertex shader and stores it with specified key.
     *
     * @param key       Key to store vertex shader with
     * @param filePath  Path to vertex shader file
     */
    void loadVertexShader(const std::string& key, const std::string &filePath);

    /**
     * Creates new fragment shader and stores it with specified key.
     *
     * @param key  Key to store fragment shader with
     */
    void loadFragmentShader(const std::string& key, const std::string &filePath);

    /**
     * Creates new geometry shader and stores it with specified key.
     *
     * @param key  Key to store geometry shader with
     */
    void loadGeometryShader(const std::string& key, const std::string &filePath);

    /**
     * Tries to load and store geometry shader with specified key.
     * This method doesn't throw exceptions, just returns true or false.
     *
     * @param key       Key to store geometry shader with
     * @param filePath  File path to load shader from
     *
     * @return True, if the shader was loaded and stored successfully or false otherwise.
     */
    bool tryLoadGeometryShader(const std::string& key, const std::string &filePath);

    /**
     * Retrieves vertex shader with a specified key.
     *
     * @param key  Key to get vertex shader from
     *
     * @return Vertex shader instance from a specified key.
     */
    const Shader& getVertexShader(const std::string& key) const;

    /**
     * Retrieves fragment shader with a specified key.
     *
     * @param key  Key to get fragment shader from
     *
     * @return Fragment shader instance from a specified key.
     */
    const Shader& getFragmentShader(const std::string& key) const;

    /**
     * Retrieves geometry shader with a specified key.
     *
     * @param key  Key to get geometry shader from
     *
     * @return Geometry shader instance from a specified key.
     */
    const Shader& getGeometryShader(const std::string& key) const;

    /**
     * Checks, if vertex shader with specified key exists.
     *
     * @param key  Vertex shader key to check existence of
     *
     * @return True if vertex shader exists or false otherwise.
     */
    bool containsVertexShader(const std::string& key) const;

    /**
     * Checks, if fragment shader with specified key exists.
     *
     * @param key  Fragment shader key to check existence of
     *
     * @return True if fragment shader exists or false otherwise.
     */
    bool containsFragmentShader(const std::string& key) const;

    /**
     * Checks, if geometry shader with specified key exists.
     *
     * @param key  Geometry shader key to check existence of
     *
     * @return True if geometry shader exists or false otherwise.
     */
    bool containsGeometryShader(const std::string& key) const;

    /** 
     * Deletes all the loaded shaders from OpenGL and clears the shaders cache.
     */
    void clearShaderCache();

private:
    ShaderManager() {} // Private constructor to make class singleton
    ShaderManager(const ShaderManager&) = delete; // No copy constructor allowed
    void operator=(const ShaderManager&) = delete; // No copy assignment allowed

    std::map<std::string, std::unique_ptr<Shader>> _vertexShaderCache; // Vertex shader cache - stores vertex shaders within their keys in std::map
    std::map<std::string, std::unique_ptr<Shader>> _fragmentShaderCache; // Fragment shader cache - stores fragment shaders within their keys in std::map
    std::map<std::string, std::unique_ptr<Shader>> _geometryShaderCache; // Gemetry shader cache - stores geometry shaders within their keys in std::map
};