#include "app.h"

class Basic : public Application
{
public:
    Basic() : Application() {}
    ~Basic() {}

    virtual void initialize() override;
    virtual void update(float dt) override;
    virtual void render(Renderer& renderer) override;
    virtual void shutdown() override;

private:
    Ref<Quad> m_Mesh;
};

void Basic::initialize()
{
    char* vertexSource =
        "#version 450 core\n"
        "layout(location = 0) in vec3 n_Position;\n"
        "uniform mat4 u_viewProjectionMatrix;\n"
        "uniform mat4 u_modelMatrix;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = u_viewProjectionMatrix * u_modelMatrix * vec4(n_Position, 1.0);\n"
        "}";

    char* fragmentSource =
        "#version 450 core\n"
        "void main()\n"
        "{\n"
        "   gl_FragColor = vec4(1, 1, 1, 1);\n"
        "}";

    auto shader = Resources::loadShaderFromSource("Default", vertexSource, fragmentSource);

    m_Mesh.reset(new Mesh(shader, std::vector<Vertex> {
        { glm::vec3(-0.5, 0, 0.5), glm::vec3(0, 1, 0), glm::vec2(0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1) },
        { glm::vec3(0.5, 0, 0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1) },
        { glm::vec3(0.5, 0, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 1), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1) },
        { glm::vec3(-0.5, 0, -0.5), glm::vec3(0, 1, 0), glm::vec2(0, 1), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1) }
    }, std::vector<unsigned int>{0, 1, 2, 0, 2, 3}, std::vector<Texture*>()));
}

void Basic::update(float dt)
{

}

void Basic::render(Renderer& renderer)
{
    renderer.draw(m_Mesh);
}

void Basic::shutdown()
{

}

DECLARE_APPLICATION(Basic);