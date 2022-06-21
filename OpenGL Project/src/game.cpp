#include "game.h"

#include <iostream>

#include "camera.h"
#include "player.h"
#include "renderer_utility.h"
#include "resource_manager.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
bool* Game::Keys;
glm::vec2 Game::MousePos;
// update tick
float deltaTime;

Camera* cam;
Player* player;

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
    // setup camera
    cam = new Camera();
    cam->position = glm::vec3(0, 0, 2);
    cam->rotation = glm::quat(1, 0, 0, 0);
    cam->fov = 59;

    // player
    player = new Player();
    player->position = glm::vec3(0, 0, 0);
    player->cam = cam;

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
    deltaTime = dt;
}
void Game::ProcessInput(float dt)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (Keys[GLFW_KEY_P])
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (Keys[GLFW_KEY_K])
    {
        std::cout << glm::to_string(player->position) << std::endl;
        std::cout << glm::to_string(player->cam->position) << std::endl;
        std::cout << player->cam->yaw << std::endl;
        std::cout << player->cam->pitch << std::endl;
        std::cout << glm::to_string(player->cam->front) << std::endl;
    }

    glm::vec2 direction = glm::vec2(0,0);
    if (Keys[GLFW_KEY_W]) direction.y = 1;
    else if (Keys[GLFW_KEY_S]) direction.y = -1;
    if (Keys[GLFW_KEY_D]) direction.x = 1;
    else if (Keys[GLFW_KEY_A]) direction.x = -1;

    player->Move(direction, dt);
    player->Look(MousePos);
}
float ang = 0;
void Game::Render()
{
    cam->position = player->position + player->camOffset;
    // set shader view and projection matrixes
    glm::mat4 projection = cam->GetProjectionMatrix();
    glm::mat4 view = cam->GetViewMatrix();
    for (auto it = ResourceManager::Shaders.begin(); it != ResourceManager::Shaders.end(); ++it)
    {
        Shader shader = it->second;
        shader.Use();
        shader.SetMatrix4("projection", projection);
        shader.SetMatrix4("view", view);
    }

    //ang += deltaTime * 60;
    RendererUtility::DrawSprite(
        glm::vec3(0.0f, 0, 0.0f),
        glm::quat(glm::vec3(glm::radians(90.0f),0, 0)),
        // glm::quat(1.0f, 0, 0, 0),
        glm::vec3(5.0f, 5.0f, 5.0f),
        ResourceManager::GetTexture("grid"), 
        ResourceManager::GetShader("sprite"));

}