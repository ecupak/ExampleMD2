#pragma once

#include <vector>
#include <string>

#include "Math.h"


class VertexObject
{
public:
    struct VertexSet
    {
        float3 position_{ 0.0f, 0.0f, 0.0f };
        float3 color_{ 0.0f, 0.0f, 0.0f };
        float3 normal_{ 0.0f, 0.0f, 0.0f };
        float2 texture_{ 0.0f, 0.0f };
    };


    VertexObject();
    VertexObject(const size_t verticiesCapacity, const size_t indiciesCapacity);


    // Create VBO, EBO, and VAO from current verticies and indicies data.
    void Build();


    // Create texture.
    void CreateTexture(std::string filepath);


    // Draw using element buffer.
    void Draw();


    // Getters.
    const unsigned int GetVAO() const;
    const unsigned int GetVBO() const;
    const unsigned int GetEBO() const;
    const std::vector<unsigned int>& GetTextureIds() const;


    // Setters.
    void SetVBO(const unsigned int VBO_);
    

    // Each vertex set contains a position, color, and texture coord.
    // A minimum of 3 vertex sets are required to draw at least 1 triangle.
    std::vector<VertexSet> vertexSets_;


    // Each index set contains 3 indicies to the vertex sets and describes 1 triangle.
    // A minimum of 1 index set is required to draw at least 1 triangle.
    std::vector<int3> indexySets_;


private:
    void DeleteObjects();

    unsigned int GetActiveTextureIndex(const int index);


    unsigned int VAO_{ 0 };
    unsigned int VBO_{ 0 };
    unsigned int EBO_{ 0 };
    std::vector<unsigned int> textureIds_;

};