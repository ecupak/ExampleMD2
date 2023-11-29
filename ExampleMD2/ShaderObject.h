#pragma once

#include <vector>

#include "glm/glm/glm.hpp"


// [Credit] https://learnopengl.com/Getting-started/Shaders
// Heavily inspired by.
class ShaderObject
{
public:
	ShaderObject();
	ShaderObject(const char* vertexShader, const char* fragmentShader);
	~ShaderObject();
	
	// Compile and attach a vertex shader to the shader program.
	void SetVertexShader(const char* shaderString);


	// Compile and attach a fragment shader to the shader program.
	void SetFragmentShader(const char* shaderString);

	
	// Link the vertex and fragments shaders into the shader program. Automatically done if 1 of each shader was given to constructor.
	void LinkShaderProgram();


	// Sets shader program to be active.
	void Use();


	// Getter.
	const unsigned int GetShaderProgram() const;
	const std::vector<unsigned int>& GetVertexShaders() const;
	const std::vector<unsigned int>& GetFragmentShaders() const;


	// Setter.
	void Set1i(const char* name, int i) const;

	void Set1ui(const char* name, unsigned int i) const;	
	
	void Set1f(const char* name, float a) const;	

	void SetVec2f(const char* name, float x, float y) const;
	void SetVec2f(const char* name, const glm::vec2& vector2) const;

	void SetVec3f(const char* name, float x, float y, float z) const;
	void SetVec3f(const char* name, const glm::vec3& vector3) const;
	
	void SetMat4fv(const char* name, const glm::mat4& mat) const;


private:
	void LoadShaderData(const char* relativeFilePath);

	std::vector<unsigned int> vertexShaders_;
	std::vector<unsigned int> fragmentShaders_;
	unsigned int shaderProgram_{ 0 };

	char* shaderData_{ nullptr };
};