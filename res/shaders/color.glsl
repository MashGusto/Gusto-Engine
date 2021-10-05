#shader vertex
#version 330 core

layout(location=0)in vec4 position;
layout(location=1)in vec3 color;

out vec3 inColor;

uniform mat4 transform;

void main()
{
  gl_Position=transform*position;
  inColor=color;
}

#shader fragment
#version 330 core

out vec4 color;

in vec3 inColor;

void main()
{
  color=vec4(inColor,1.f);
}
