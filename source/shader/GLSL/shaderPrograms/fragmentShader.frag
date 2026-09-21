#version 330 core

in vec2 textureCoordinate;

uniform sampler2D textureObject;


in vec3 objectColor;
in vec3 lightColor;

void main()
{
    //gl_FragColor = vec4(1.0f, 0.5f, 1.0f, 1.0f);
    //gl_FragColor = vec4(fragColor, 1.0f);

    gl_FragColor = texture(textureObject, textureCoordinate) * vec4(objectColor * lightColor, 1.0f);
}

