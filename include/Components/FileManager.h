#pragma once

#include <string>

namespace FileManager
{
  std::string readFromFile(std::string filePath);
  std::string getImage(const char* fileName);
  std::string getShader(const char* fileName);
}
