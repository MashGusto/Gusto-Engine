#shader vertex
#version 330 core

layout(location=0)in vec4 position;
layout(location=1)in vec2 texCoord;

out vec2 inTexCoord;

uniform mat4 transform;

void main()
{
  gl_Position=transform*position;
  inTexCoord=texCoord;
}

#shader fragment
#version 330 core

out vec4 tex;

in vec2 inTexCoord;

uniform sampler2D texCoord;

void main()
{
  tex=texture(texCoord,inTexCoord);
}
