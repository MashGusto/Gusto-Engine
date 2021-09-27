#include "Components/FileManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::string FileManager::readFromFile(std::string filePath)
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

std::string FileManager::getImage(const char* fileName)
{
  return "../assets/images/" + (std::string)fileName;
}

std::string FileManager::getShader(const char* fileName)
{
  return "../include/Shaders/" + (std::string)fileName;
}
