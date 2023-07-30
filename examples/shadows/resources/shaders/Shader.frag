#version 330 core

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;
in vec4 fragPosLightSpace;

out vec4 fragColor;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D shadowMapTexture;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float shininess;

/******************************************************************************/
float CalculateShadow(vec4 aFragPos) {
  // Convert the fragment position to the range [0,1] so it can be compared with
  // the shadow map.
  vec3 coord = fragPosLightSpace.xyz / fragPosLightSpace.w;
  coord = (coord * 0.5) + 0.5;

  float closestDepth = texture(shadowMapTexture, coord.xy).r;
  float currentDepth = coord.z;

  return currentDepth > closestDepth ? 1.0 : 0.0;
}

/******************************************************************************/
void main() {
  // Calculate the lighting values of the fragment using the supplied textures.
  vec3 diffVal = texture(diffuseTexture, texCoords).xyz;
  vec3 specVal = texture(specularTexture, texCoords).xyz;

  // Calculate any direction vectors needed for lighting.
  vec3 lightDir = normalize(lightPos - fragPos);
  vec3 lightDirReflect = reflect(-lightDir, normal);
  vec3 viewDir = normalize(viewPos - fragPos);

  // Calculate the diffuse component.
  float d = max(dot(normal, lightDir), 0.0);
  vec3 diffuse = lightColor * diffVal * d;

  // Calculate the specular component.
  float s = pow(max(dot(viewDir, lightDirReflect), 0.0), shininess);
  vec3 specular = lightColor * specVal * s;

  // Calculate the shadow component.
  float shadow = CalculateShadow(fragPosLightSpace);

  // Combine each component.
  fragColor = vec4((diffuse + specular) * (1.2 - shadow), 1.0);
}
