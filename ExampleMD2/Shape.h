#pragma once

#include <glad/glad.h>

#include "VertexObject.h"
#include "ShaderObject.h"

#include "LightData.h"


class Shape
{
public:
	Shape() = default;
	Shape(const size_t verticiesCapacity, const size_t indiciesCapacity);
	Shape(const char* vertexShader, const char* fragmentShader);
	Shape(const size_t verticiesCapacity, const size_t indiciesCapacity,
		const char* vertexShader, const char* fragmentShader);

	~Shape();


	// Do not allow copying.
	Shape(const Shape& other) = delete;
	Shape& operator=(const Shape& other) = delete;


	// Default properites of all shapes.
	glm::vec3 position_{ 0.0f, 0.0f, 0.0f };
	glm::vec3 color_{ 0.0f, 0.0f, 0.0f };
	float shininess_{ 32.0f };
	float specularValue_{ 0.5f };

	// Vertex object (VBO, EBO, VAO). Call to draw.
	VertexObject VO_;
	
	
	// Shader object (vertex, fragment). Call to use.
	ShaderObject SO_;


	// Light data (if a light source).
	LightData* lightData_{ nullptr };
};