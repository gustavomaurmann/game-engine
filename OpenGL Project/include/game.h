#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


class Game
{
public:
    static bool* Keys;
    static int Width, Height;
    static glm::vec2 MousePos;

    Game(unsigned int width, unsigned int height);
    ~Game();

    void Init();

    // Loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();

private:
};

#endif

