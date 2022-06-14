#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"
// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;
void CopyTo(unsigned char* source, unsigned char* target, int sourceW, int sourceH, int targetW, int targetH, int x, int y);
Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char *file, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}
Texture2D ResourceManager::LoadTextureTest(const char* file, const char* file2, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFileTest(file, file2, alpha);
    return Textures[name];
}
Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    // (properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}
Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    // create texture object
    Texture2D texture;
    texture.Internal_Format = GL_RGB;
    texture.Image_Format = GL_RGB;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    int size1 = (sizeof(data) / sizeof(data[0]));
    // now generate texture
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);

    return texture;
}
Texture2D ResourceManager::loadTextureFromFileTest(const char* file, const char* file2, bool alpha)
{
    // create texture object
    Texture2D texture;
    texture.Internal_Format = GL_RGB;
    texture.Image_Format = GL_RGB;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // load image 1
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // load image 2
    int width2, height2, nrChannels2;
    unsigned char* data2 = stbi_load(file2, &width2, &height2, &nrChannels, 0);
    // final

    int newWidth = 2*width;// +width2;
    int newHeight = height + height2;
    std::cout << newWidth << std::endl << newHeight << std::endl;

    unsigned char* target = new unsigned char[newWidth * newHeight * 4];
    for (int i = 0; i < newWidth * newHeight * 4; i++)
    {
        target[i] = 0x0000;
    }
    int targetX = width;
    int targetY = height;
    CopyTo(data, target, width, height, newWidth, newHeight, 0, 0);
    CopyTo(data2, target, width, height, newWidth, newHeight, 0, height);

    // now generate texture
    texture.Generate(newWidth, newHeight, target);
    // and finally free image data
    stbi_image_free(data);
    stbi_image_free(data2);
    stbi_image_free(target);
    return texture;
}
void CopyTo(unsigned char* source, unsigned char* target, int sourceW, int sourceH, int targetW, int targetH, int x, int y)
{
    for (int sourceY = 0; sourceY < sourceH; ++sourceY) {
        for (int sourceX = 0; sourceX < sourceW; ++sourceX) {
            int from = (sourceY * sourceW * 4) + (sourceX * 4); // 4 bytes per pixel (assuming RGBA)
            int to = ((y + sourceY) * targetW * 4) + ((x + sourceX) * 4); // same format as source

            for (int channel = 0; channel < 4; ++channel) {
                target[to + channel] = source[from + channel];
            }
        }
    }
}

