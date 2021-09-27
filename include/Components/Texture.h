#pragma once

#include <string>

class Texture
{
  private:
    unsigned int texture;
    int width, height, channelCount;
  public:
    Texture(std::string textureImagePath);
    unsigned int getTexture();
};
