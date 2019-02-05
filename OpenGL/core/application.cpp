#include "application.h"

Application* Application::s_Instance = nullptr;

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    Application::getInstance()->mouseCallback(window, xPos, yPos);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    Application::getInstance()->scrollCallback(window, xOffset, yOffset);
}

bool Application::setup()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_Window = glfwCreateWindow(m_Config.width, m_Config.height, m_Config.title.c_str(), nullptr, nullptr);
    if (m_Window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    });
    glfwSetCursorPosCallback(m_Window, mouse_callback);
    glfwSetScrollCallback(m_Window, scroll_callback);

    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    initialize();

    return true;
}

void Application::run()
{
    m_LastFrame = 0;

    m_Renderer.setup();

    while (!glfwWindowShouldClose(m_Window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;

        processInput(m_Window, deltaTime);

        update(deltaTime);
        setRenderState();
        render(m_Renderer);

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void Application::setRenderState()
{
    glm::mat4 projection = glm::perspective(glm::radians(m_Camera.getZoom()), (float)getWidth() / getHeight(), 0.1f, 100.0f);
    glm::mat4 view = m_Camera.getViewMatrix();
    m_Renderer.setProjectionMatrix(projection);
    m_Renderer.setViewMatrix(view);
    m_Renderer.setCameraPos(m_Camera.getPosition());
}

void Application::mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (m_FirstMouse)
    {
        m_LastX = xPos;
        m_LastY = yPos;
        m_FirstMouse = false;
    }

    float xOffset = xPos - m_LastX;
    float yOffset = m_LastY - yPos;
    m_LastX = xPos;
    m_LastY = yPos;

    m_Camera.processMouseMovement(xOffset, yOffset);
}

void Application::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    m_Camera.processMouseScroll(yOffset);
}

void Application::processInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) m_Camera.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) m_Camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) m_Camera.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) m_Camera.processKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE))
    {
        m_Config.MSAA = !m_Config.MSAA;
        if (m_Config.MSAA) glEnable(GL_MULTISAMPLE);
        else glDisable(GL_MULTISAMPLE);
    }
}