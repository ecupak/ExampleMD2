#version 310 es

uniform struct
{
    mat4 projectionMatrix;
    mat4 viewMatrix;
    mat4 modelMatrix;
    mat3 normalMatrix;
} matrices;


layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 vertexTexCoord;
layout (location = 2) in vec3 vertexNormal;
layout (location = 3) in vec3 nextVertexPosition;
layout (location = 4) in vec3 nextVertexNormal;


uniform float interpolationFactor;

out mediump vec2 texCoord;


void main()
{
    mat4 mvMatrix = matrices.viewMatrix * matrices.modelMatrix;
    mat4 mvpMatrix = matrices.projectionMatrix * mvMatrix;

    vec4 interpolatedPosition = vec4(vertexPosition + (nextVertexPosition - vertexPosition) * interpolationFactor, 1.0);
    
    gl_Position = mvpMatrix * interpolatedPosition;

    texCoord = vertexTexCoord;
}