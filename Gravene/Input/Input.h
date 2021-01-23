#ifndef INPUT_H
#define INPUT_H

#include "../Rendering/Window.h"

#include <vector>
#include <map>

class Input {
    enum class KeyState {
        NotPressed,
        Pressed,
        Down,
        Released
    };

    private:
        static GLFWwindow* m_GLFWwindow;
        static Window* m_Window;

        static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        //static void GLFWCursorPosCallback(GLFWwindow* window, double xpos, double ypos);

        static std::map<std::string, float> axisMap;
        static std::vector<int> keysToMonitor;
        static KeyState keyStates[512];
        static KeyState mouseKeyStates[32];

        Input() {}
        
    public:
        static const Input& GetInstance();

        static void Setup(Window* window);
        static void Update();

        static const float GetAxis(const std::string& axis);

        static const bool GetKeyDown(const int key);
        static const bool GetKeyPressed(const int key);
        static const bool GetKeyReleased(const int key);

        static const bool GetMouseDown(const int key);
        static const bool GetMousePressed(const int key);
        static const bool GetMouseReleased(const int key);

        Input(Input const &)            = delete;
        void operator=(Input const &)   = delete;
};

#endif