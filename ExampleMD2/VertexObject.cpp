#include "VertexObject.h"

#include <glad/glad.h>
#include <iostream>

#include "StbiLoader.h"
#include "AssetFile.h"


VertexObject::VertexObject()
{
    vertexSets_.reserve(3);
    indexySets_.reserve(1);
}


VertexObject::VertexObject(const size_t verticiesCapacity, const size_t indiciesCapacity)    
{   
    vertexSets_.reserve(verticiesCapacity);
    indexySets_.reserve(indiciesCapacity);
}


void VertexObject::Build()
{
    DeleteObjects();

    // Create vertex array object.
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    // Create vertex buffer object.
    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertexSets_.size() * sizeof(VertexSet), vertexSets_.data(), GL_STATIC_DRAW);

    // Create element buffer object.
    glGenBuffers(1, &EBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexySets_.size() * sizeof(int3), indexySets_.data(), GL_STATIC_DRAW);

    // Assign attributes for vertex position data, &
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSet), (void*)0);
    glEnableVertexAttribArray(0);

    // ... color data, &
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSet), (void*)(1 * sizeof(float3)));
    glEnableVertexAttribArray(1);

    // ... normal data, &
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSet), (void*)(2 * sizeof(float3)));
    glEnableVertexAttribArray(2);

    // ... texture coord data.
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexSet), (void*)(3 * sizeof(float3)));
    glEnableVertexAttribArray(3);

    // Unbind VAO to avoid other VAO calls from modifying it.
    glBindVertexArray(0);
}


void VertexObject::CreateTexture(std::string filepath)
{
    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width;
    int height;
    int nrChannels;
    unsigned char* data{ stbiLoader::LoadImage(AssetFile::GetPath(filepath), width, height, nrChannels, true) };

    if (data)
    {
        GLint imageFormat{ nrChannels == 4 ? GL_RGBA : GL_RGB };
        
        glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbiLoader::FreeImage(data);

    textureIds_.push_back(textureId);
}


void VertexObject::Draw()
{
    for (int i = 0; i < textureIds_.size(); ++i)
    {
        glActiveTexture(GetActiveTextureIndex(i));
        glBindTexture(GL_TEXTURE_2D, textureIds_[i]);
    }

    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, 3 * indexySets_.size(), GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, 0);
}


void VertexObject::DeleteObjects()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &EBO_);
}


const unsigned int VertexObject::GetVAO() const
{
    return VAO_;
}


void VertexObject::SetVBO(const unsigned int VBO)
{
    VBO_ = VBO;
}


const unsigned int VertexObject::GetVBO() const
{
    return VBO_;
}


const unsigned int VertexObject::GetEBO() const
{
    return EBO_;
}


const std::vector<unsigned int>& VertexObject::GetTextureIds() const
{
    return textureIds_;
}


unsigned int VertexObject::GetActiveTextureIndex(const int index)
{
    switch (index)
    {
    case 0:
        return GL_TEXTURE0;
    case 1:
        return GL_TEXTURE1;
    case 2:
        return GL_TEXTURE2;
    case 3:
        return GL_TEXTURE3;
    case 4:
        return GL_TEXTURE4;
    case 5:
        return GL_TEXTURE5;
    case 6:
        return GL_TEXTURE6;
    case 7:
        return GL_TEXTURE7;
    default:
        return GL_TEXTURE0;
    }
}