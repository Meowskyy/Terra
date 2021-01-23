#ifndef WINDOW_H
#define WINDOW_H

struct GLFWwindow;

class Window {
    private:
        GLFWwindow* m_GLFWwindow;

        int m_Width = 1280, m_Height = 720;
    public:
        Window();
        Window(const int width, const int height);

        void SetWindowSize(const int width, const int height);
        void SetWindowName(const char* name);

        GLFWwindow* GetGLFWwindow() const { return m_GLFWwindow; }
        
        const int GetWindowWidth() const;
        const int GetWindowHeight() const;

        void SetContext();
        void SwapBuffers();
};

#endif