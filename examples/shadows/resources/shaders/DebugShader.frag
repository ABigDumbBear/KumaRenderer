#version 330 core

in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D shadowMap;

void main()
{
  float color = texture(shadowMap, texCoords).r;
  fragColor = vec4(vec3(color), 1.0);
}
