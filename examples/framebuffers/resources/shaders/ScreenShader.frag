#version 330 core

in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D texSampler;

void main()
{
  vec3 color = texture(texSampler, texCoords).rgb;
  fragColor = vec4(color, 1.0);
  fragColor.r = 0.3;
}
