#include "application.h"

class Sandbox : public Application
{
public:
    Sandbox(const std::string& title, int screenWidth, int screenHeight)
        : Application(title, screenWidth, screenHeight) {}

    virtual void setup() override
    {
        m_Mesh = new Mesh("resources/head.obj");
        m_Texture = loadTexture("resources/african_head_diffuse.tga");
    }
    
    virtual void update(float dt) override
    {
        auto tinyGL = getGLContext();

        auto projectionMatrix = Mat4x4::perspective(MathUtil::radius(45.0f), (float)getScreenWidth() / getScreenHeight(), 1.0f, 100.0f);
        float camX = cos(getTime()) * 5.0f;
        float camZ = sin(getTime()) * 5.0f;
        auto viewMatrix = Mat4x4::lookAt({ camX, 0, camZ }, { 0, 0, 0 }, { 0, 1, 0 });

        tinyGL->setViewProjectionMatrix(viewMatrix, projectionMatrix);
        tinyGL->setClearColor(Color::black);
        tinyGL->clear(ClearFlags::ColorBuffer | ClearFlags::DepthBuffer);

        Mesh quad;
        quad.vertices = {
            {{-1, -1, 0}, {0, 0}, {0, 0, 1}, {0, 0, 0, 1}},
            {{1, -1, 0}, {1, 0}, {0, 0, 1}, {1, 1, 1, 1}},
            {{-1, 1, 0}, {0, 1}, {0, 0, 1}, {0, 0, 0, 1}},
            {{1, 1, 0}, {1, 1}, {0, 0, 1}, {1, 1, 1, 1}}
        };
        quad.indices = { 0, 1, 2, 1, 3, 2 };

        Mesh triangle;
        triangle.vertices = { {{-1, -1, 0}, {}, {}, {1, 0, 0, 1}}, {{1, -1, 0}, {}, {}, {0, 1, 0, 1}}, {{0, 1, 0}, {}, {}, {0, 0, 1, 1} } };
        triangle.indices = { 0, 1, 2 };

        tinyGL->bindTexture(m_Texture, 0);
        tinyGL->drawElements(m_Mesh->vertices, m_Mesh->indices, Mat4x4::scale(1.0f));
    }

    virtual void destroy() override
    {
        SAFE_DELETE(m_Mesh);
        SAFE_DELETE(m_Texture);
    }

private:
    Mesh* m_Mesh;
    Texture* m_Texture;
};

int main(int argc, char** argv)
{
    Sandbox sandbox("Tiny GL", 800, 600);
    sandbox.initialize();
    sandbox.run();
    sandbox.shutdown();

	return 0;
}