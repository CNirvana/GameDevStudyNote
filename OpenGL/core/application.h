#pragma once

#include "camera.h"
#include "renderer.h"

struct ApplicationConfig
{
    std::string title;
    unsigned int width;
    unsigned int height;
    bool MSAA;

    ApplicationConfig(const std::string& _title = "OpenGL", int _width = 1366, int _height = 768, int _MSAA = false)
        : title(_title), width(_width), height(_height), MSAA(_MSAA) {}
};

void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

class Application
{
public:
    Application(const ApplicationConfig& config = ApplicationConfig())
        : m_Config(config), m_Window(nullptr), m_FirstMouse(true)
    {
        s_Instance = this;
        m_LastX = config.width * 0.5f;
        m_LastY = config.height * 0.5f;
    }
    virtual ~Application() {}

    static Application* getInstance() { return s_Instance; }

    bool setup();
    void run();

    int getWidth() const { return m_Config.width; }
    int getHeight() const { return m_Config.height; }

    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void shutdown() = 0;

    virtual void mouseCallback(GLFWwindow* window, double xPos, double yPos);
    virtual void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

protected:
    ApplicationConfig m_Config;
    GLFWwindow* m_Window;

    float m_DeltaTime;

    Renderer m_Renderer;
    Camera m_Camera;

    virtual void processInput(GLFWwindow* window);

private:
    float m_LastX;
    float m_LastY;
    bool m_FirstMouse;
    float m_LastFrame;

    static Application* s_Instance;
};

Application* CreateApplication();