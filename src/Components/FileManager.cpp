#include "Components/FileManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace FileManager
{
  // Data members to store the path to the folders containing the images and shaders, respectively.
  const char* imageDirectory;
  const char* shaderDirectory;

  // Reads the text from a file and returns it as a string, while also checking for errors in the reading of the file.
  std::string readFromFile(std::string filePath)
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
    catch(std::ifstream::failure e)
    {
      std::cout << "Failed to read file properly" << std::endl;
      return "";
    }
  }

  // Sets the folder path for images referred by this file maager
  void setImageDirectory(const char* imageFolderPath)
  {
    // Checks if the folder path given has a / at the end to signify a directory, if not, append a / to the string(otherwise an error would occur in the getImage function).
    //if(imageFolderPath[imageFolderPath.length()-1] != '/')
    //  imageFolderPath = imageFolderPath + '/';

    imageDirectory = imageFolderPath;
  }

  // Sets the folder path for shaders referred by this file manager
  void setShaderDirectory(const char* shaderFolderPath)
  {
    // Checks if the folder path given has a / at the end to signify a directory, if not, append a / to the string(otherwise an error would occur in the getShader function).
    //if(shaderFolderPath[shaderFolderPath.length()-1] != '/')
    //  shaderFolderPath = shaderFolderPath + '/';

    shaderDirectory = shaderFolderPath;
  }

  // Returns a full path to the file name given according to the imageDirectory set before.
  std::string getImage(const char* fileName)
  {
    return imageDirectory + (std::string)fileName;
  }

  // Returns a full path to the file name given according to the shaderDirectory set before.
  std::string getShader(const char* fileName)
  {
    return shaderDirectory + (std::string)fileName;
  }
}
