#version 330 core

in vec2 textureCoordinate;

uniform sampler2D textureObject;

//uniform vec4 color;

void main()
{
    //gl_FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);

    //gl_FragColor = color;

     gl_FragColor = texture(textureObject, textureCoordinate) * vec4(1.0f);
}