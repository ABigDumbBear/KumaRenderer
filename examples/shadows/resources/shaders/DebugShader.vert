#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 3) in vec2 aTexCoords;

out vec2 texCoords;

void main()
{
  texCoords = aTexCoords;

  gl_Position = vec4(aPosition.x * 2, aPosition.y * 2, 0, 1);
}
