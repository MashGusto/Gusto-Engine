#pragma once

/**
 * The File Manager for the Engine.
 *
 * Helps with working with files, such as reading files as text and images.
 */

#include <string>

namespace FileManager
{
    

    std::string readFromFile(std::string filePath);
    
    void setImageDirectory(const char* imageFolderPath);
    void setShaderDirectory(const char* shaderFolderPath);

    std::string getImage(const char* fileName);
    std::string getShader(const char* fileName);
}
