#version 330

layout(location = 0) in vec3 inVertexPosition;
uniform mat4 projViewMatrix;
void main()
{
    gl_Position = projViewMatrix*vec4(0,0,-1, 1.0);
}