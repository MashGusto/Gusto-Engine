#include "System/FileManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace FileManager
{
  // Data members to store the path to the folders containing the images and shaders, respectively.
  std::string imageDirectory;
  std::string shaderDirectory;

  // Reads the text from a file and returns it as a string, while also checking for errors in the reading of the file.
  std::string readFile(std::string filePath)
  {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
      file.open(filePath);
      std::stringstream fileStream;
      fileStream << file.rdbuf();
      file.close();
      return fileStream.str();
    }
    catch (std::ifstream::failure e)
    {
      std::cout << "Failed to read file properly" << std::endl;
      return "";
    }
  }

  // Reads the text from a shader file and returns the vertex and fragment shaders as different strings
  // Also checks for errors in the reading of the file.
  ShaderSource readShader(std::string filePath)
  {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    enum class ShaderType
    {
      NONE = -1,
      VERTEX = 0,
      FRAGMENT = 1
    };

    try
    {
      file.open(filePath);
      std::stringstream fileStream;
      fileStream << file.rdbuf();
      std::string line;
      std::stringstream ss[2];

      ShaderType type = ShaderType::NONE;

      while (std::getline(fileStream, line))
      {
        if (line.find("#shader") != std::string::npos)
        {
          if (line.find("vertex") != std::string::npos)
            type = ShaderType::VERTEX;
          else if (line.find("fragment") != std::string::npos)
            type = ShaderType::FRAGMENT;
        }
        else
        {
          ss[(int)type] << line << '\n';
        }
      }
      file.close();
      return {ss[0].str(), ss[1].str()};
    }
    catch (std::ifstream::failure e)
    {
      std::cout << "Failed to read shader file[" << filePath << "] properly: " << e.what() << std::endl;
      return {"", ""};
    }
  }

  // Sets the folder path for images referred by this file maager
  void setImageDirectory(std::string imageFolderPath)
  {
    // Checks if the folder path given has a / at the end to signify a directory, if not, append a / to the string(otherwise an error would occur in the getImage function).
    if (imageFolderPath[imageFolderPath.length() - 1] != '/')
      imageFolderPath = imageFolderPath + '/';

    imageDirectory = imageFolderPath;
  }

  // Sets the folder path for shaders referred by this file manager
  void setShaderDirectory(std::string shaderFolderPath)
  {
    // Checks if the folder path given has a / at the end to signify a directory, if not, append a / to the string(otherwise an error would occur in the getShader function).
    if (shaderFolderPath[shaderFolderPath.length() - 1] != '/')
      shaderFolderPath = shaderFolderPath + '/';

    shaderDirectory = shaderFolderPath.c_str();
  }

  // Returns a full path to the file name given according to the imageDirectory set before.
  std::string getImage(const char *fileName)
  {
    return imageDirectory + (std::string)fileName;
  }

  // Returns a full path to the file name given according to the shaderDirectory set before.
  std::string getShader(const char *fileName)
  {
    return shaderDirectory + (std::string)fileName;
  }
}
