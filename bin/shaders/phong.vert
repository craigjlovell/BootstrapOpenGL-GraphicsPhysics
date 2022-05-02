// a simple shader
#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;

out vec4 vPosition;
out vec3 vNormal;

uniform mat4 ProjectionViewModel;

// This refers to the model matrix to be used in our transform normal
uniform mat4 ModelMatrix;

void main()
{
    vPosition = ModelMatrix * Position;
    vNormal = (ModelMatrix * Normal).xyz;
    gl_Position = ProjectionViewModel * Position;
}