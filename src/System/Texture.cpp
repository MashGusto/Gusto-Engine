#include "System/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "dependencies/stb_image.h"

#include <iostream>
#include "glad/glad.h"

// Creates a texture from an image, also checking for errors.
Texture::Texture(std::string textureImagePath)
{
  // Generate a new texture and configure it
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  unsigned char *data = stbi_load(&textureImagePath[0], &width, &height, &channelCount, 0);
  if (data)
  {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Checks if the given image has a transparency channel or not.
    if (channelCount == 3)
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    if (channelCount == 4)
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture: " << textureImagePath << std::endl;
  }

  // Clears the data in the data variable, as it is not needed anymore.
  stbi_image_free(data);
}

// Returns the texture id of the current texture.
unsigned int Texture::getTexture()
{
  return texture;
}
