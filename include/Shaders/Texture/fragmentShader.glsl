#version 330 core

out vec4 tex;

in vec2 inTexCoord;

uniform sampler2D texCoord;

void main()
{
  tex = texture(texCoord, inTexCoord);
}
