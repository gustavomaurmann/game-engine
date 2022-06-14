#include "game.h"

#include <iostream>

#include "camera.h"
#include "renderer_utility.h"
#include "resource_manager.h"
#include "stb_image.h"


bool* Game::Keys;
glm::vec2 Game::MousePos;
// update tick
float deltaTime;

Game::Game(unsigned int width, unsigned int height)
{
    if (Keys == nullptr)
    {
        Keys = new bool[1024];
    }
}
Game::~Game()
{
}
void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("shader/sprite.vs", "shader/sprite.frag", nullptr, "sprite");
    std::cout << "---------------------------" << std::endl << "Loaded Shaders : " << std::endl;
    for (auto const& x : ResourceManager::Shaders)
    {
        std::cout << x.first 
            << "; ID: "
            << x.second.ID
            << std::endl;
    }
    std::cout << "---------------------------" << std::endl << std::endl;

    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, Width * 1.0f, Height * 1.0f, 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    // load textures
    stbi_set_flip_vertically_on_load(true);
    ResourceManager::LoadTexture("texture/grid.png", true, "grid");
    std::cout << "---------------------------" << std::endl << "Loaded Textures : " << std::endl;
    for (auto const& x : ResourceManager::Textures)
    {
        std::cout << x.first
            << "; ID: "
            << x.second.ID
            << std::endl;
    }
    std::cout << "---------------------------" << std::endl << std::endl;

}
void Game::Update(float dt)
{
    // calculate FPS
    deltaTime = dt;
}
void Game::ProcessInput(float dt)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (Keys[GLFW_KEY_P])
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

void Game::Render()
{
    

}