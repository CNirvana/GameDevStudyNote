#include "headers.h"

class Shadow : public Application
{
public:
    Shadow() : Application() {}
    ~Shadow() {}

    virtual void initialize() override;
    virtual void update() override;
    virtual void shutdown() override;

private:

};

void Shadow::initialize()
{

}

void Shadow::update()
{

}

void Shadow::shutdown()
{

}

Application* CreateApplication()
{
    return new Shadow();
}