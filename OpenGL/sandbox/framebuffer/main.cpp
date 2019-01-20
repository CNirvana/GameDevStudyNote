#include "headers.h"

class Sandbox : public Application
{
public:
    Sandbox() : Application() {}
    ~Sandbox() {}

    virtual void initialize() override;
    virtual void update() override;
    virtual void shutdown() override;

private:
    FrameBuffer* m_FrameBuffer;
    Shader* m_FrameBufferShader;

    Mesh* m_Plane;
    Cube* m_Cube;
};

void Sandbox::initialize()
{
    // load shaders
    Shader* cubeShader = Resources::loadShaderFromFile("cube", "shaders/reflection.vert", "shaders/reflection.frag");
    Shader* planeShader = Resources::loadShaderFromFile("plane", "shaders/model.vert", "shaders/model.frag");

    // load textures
    Texture* planeTex = Resources::loadTexture("textures/wall.jpg", { TextureType::Diffuse, TextureWrapMode::Clamp, TextureFilterMode::Bilinear, true });

    m_FrameBuffer = new FrameBuffer(m_Config.width, m_Config.height);
    m_FrameBufferShader = Resources::loadShaderFromFile(
        "framebuffer",
        "shaders/framebuffer.vert",
        "shaders/gaussian_blur.frag"
    );

    m_Plane = new Mesh(planeShader, std::vector<Vertex>
    {
        { glm::vec3(-0.5, 0, 0.5), glm::vec3(0, 1, 0), glm::vec2(0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1) },
        { glm::vec3(0.5, 0, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1) },
        { glm::vec3(0.5, 0, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 1), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1) },
        { glm::vec3(-0.5, 0, -0.5), glm::vec3(0, 1, 0), glm::vec2(0, 1), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1) }
    }, std::vector<unsigned int>{0, 1, 2, 0, 2, 3}, std::vector<Texture*>{ planeTex });

    m_Cube = new Cube(cubeShader);

    m_Renderer.setSkybox(new Cubemap(std::vector<std::string>{
        "textures/right.jpg",
        "textures/left.jpg",
        "textures/top.jpg",
        "textures/bottom.jpg",
        "textures/front.jpg",
        "textures/back.jpg"
    }));
}

void Sandbox::shutdown()
{
    SAFE_RELEASE(m_FrameBuffer);
    SAFE_RELEASE(m_Plane);
    SAFE_RELEASE(m_Cube);

    Resources::unloadAll();
}

void Sandbox::update()
{
    m_Renderer.bindFrameBuffer(*m_FrameBuffer);

    m_Renderer.clear();

    glm::mat4 projection = glm::perspective(glm::radians(m_Camera.getZoom()), (float)getWidth() / getHeight(), 0.1f, 100.0f);
    glm::mat4 view = m_Camera.getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    m_Renderer.setProjectionMatrix(projection);
    m_Renderer.setViewMatrix(view);
    m_Renderer.setCameraPos(m_Camera.getPosition());

    m_Cube->position = glm::vec3(5, 5, 0);
    m_Renderer.draw(*m_Cube);

    m_Plane->position = glm::vec3(0, -1, 0);
    m_Plane->scale = glm::vec3(100, 1, 100);
    m_Renderer.draw(*m_Plane);

    m_Renderer.drawSkybox();

    m_Renderer.drawFrameBuffer(*m_FrameBuffer, m_FrameBufferShader);
}

Application* CreateApplication()
{
    return new Sandbox();
}