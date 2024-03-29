#version 330

in vec4 vPosition;
in vec2 vTexture;
in vec4 vColor;
in vec3 vNormal;

out vec3 normal;
out vec4 color;
out vec2 t;
out vec4 eye;

uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  normal = (normalMatrix * normalize(vNormal));
  eye = - gl_Position; 
  t = vTexture; 
  color = vColor;
}
