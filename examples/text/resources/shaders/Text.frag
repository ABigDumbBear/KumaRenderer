#version 330 core

in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D texSampler;

void main()
{
  float textureAlpha = texture(texSampler, texCoords).r;
  fragColor = vec4(1.0, 1.0, 1.0, textureAlpha);
}
