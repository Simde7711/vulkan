#pragma once

// #include "lve_game_object.hpp"
#include "ECS/components/components.hpp"
#include "lve_window.hpp"

namespace lve
{
    class KeyboardMovementController
    {
        public:
            struct KeyMappings 
            {
                int moveLeft = GLFW_KEY_A;
                int moveRight = GLFW_KEY_D;
                int moveForward = GLFW_KEY_W;
                int moveBackward = GLFW_KEY_S;
                int lookLeft = GLFW_KEY_LEFT;
                int lookRight = GLFW_KEY_RIGHT;
                int lookUp = GLFW_KEY_UP;
                int lookDown = GLFW_KEY_DOWN;
            };

            KeyMappings keys{};
            float moveSpeed{3.f};
            float lookSpeed{1.5f};

            void MoveInPlaneXZ(GLFWwindow *window, float deltaTime, Transform &transform);
    };
}