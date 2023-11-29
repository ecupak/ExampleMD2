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

#include <string>
#include <map>
#include <memory>

#include <GLES3/gl31.h>

#include "ShaderProgram.h"

/**
 * Singleton class that manages and keeps track of all shader programs in the program.
 */
class ShaderProgramManager
{
public:
	/**
	 * Gets the one and only instance of the shader program manager.
	 */
	static ShaderProgramManager& getInstance();
	
	/**
	 * Creates new shader program and stores it with specified key.
	 *
	 * @param key  Key to store shader program with
	 *
	 * @return Shader program instance with specified key.
	 */
	ShaderProgram& createShaderProgram(const std::string& key);

	/**
	 * Retrieves shader program with a specified key.
	 *
	 * @param key  Key to get shader program from
	 *
	 * @return Shader program instance from a specified key.
	 */
	ShaderProgram& getShaderProgram(const std::string& key) const;

	/**
	 * Performs linkage of all existing shader programs.
	 */
	void linkAllPrograms();

	/**
	 * Deletes all the shader programs loaded and clears the shader program cache.
	 */
	void clearShaderProgramCache();

private:
	ShaderProgramManager() {} // Private constructor to make class singleton
	ShaderProgramManager(const ShaderProgramManager&) = delete; // No copy constructor allowed
	void operator=(const ShaderProgramManager&) = delete; // No copy assignment allowed

	/**
	 * Checks, if shader program with specified key exists.
	 *
	 * @param  key  Shader program key to check existence of
	 *
	 * @return True if shader program exists, or false otherwise.
	 */
	bool containsShaderProgram(const std::string& key) const;

	std::map<std::string, std::unique_ptr<ShaderProgram>> _shaderProgramCache; // Shader program cache - stores shader programs within their keys in std::map
};