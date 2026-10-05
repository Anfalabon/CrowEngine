#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec3 position;  //for now this won't be in use
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 textureCoordinate;


uniform vec3 uLightColor;
uniform vec3 uObjectColor;

out vec3 lightColor;
out vec3 objectColor;


void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    //gl_Position = vec4(aPos + position, 1.0);

    textureCoordinate = aTexCoord;

    lightColor = uLightColor;
    objectColor = uObjectColor;

}


