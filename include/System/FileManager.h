#pragma once

/**
 * The File Manager for the Engine.
 *
 * Helps with working with files, such as reading files as text and images.
 */

#include <string>

struct ShaderSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

namespace FileManager
{

    std::string readFile(std::string filePath);
    ShaderSource readShader(std::string filePath);

    void setImageDirectory(std::string imageFolderPath);
    void setShaderDirectory(std::string shaderFolderPath);

    std::string getImage(const char *fileName);
    std::string getShader(const char *fileName);
}
