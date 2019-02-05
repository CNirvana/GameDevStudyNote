#include "headers.h"

class Lighting : public Application
{
public:
    Lighting() : Application(), m_DirectionalLight(nullptr), m_SpotLight(nullptr) {}
    ~Lighting() {}

    virtual void initialize() override
    {
        Shader* lightingShader = Resources::loadShaderFromFile("Lighting", "shaders/light.vert", "shaders/light.frag");

        m_DirectionalLight = new DirectionalLight(glm::vec3(1, 1, 1), 1, glm::vec3(1, -1, 1));

        m_Cube = new Cube(lightingShader);
        m_Cube->position = glm::vec3(0, 0, 0);
    }

    virtual void update(float deltaTime) override
    {
    }

    virtual void render(const Renderer& renderer) override
    {
        renderer.clear();
        renderer.draw(*m_Cube);
    }

    virtual void shutdown() override
    {
        SAFE_DELETE(m_DirectionalLight);
        for (int i = 0; i < m_PointLights.size(); i++)
        {
            SAFE_DELETE(m_PointLights[i]);
        }
        m_PointLights.clear();
        SAFE_DELETE(m_SpotLight);

        Resources::unloadAll();
    }

private:
    DirectionalLight* m_DirectionalLight;
    std::vector<PointLight*> m_PointLights;
    SpotLight* m_SpotLight;

    Cube* m_Cube;
};

DECLARE_APPLICATION(Lighting);