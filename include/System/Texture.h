#pragma once

/**
 * The texture class that is implemented on the sprites, to give them a texture from a given image.
 */

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
