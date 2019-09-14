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

};

void Basic::initialize()
{

}

void Basic::update(float dt)
{

}

void Basic::render(Renderer& renderer)
{

}

void Basic::shutdown()
{

}

DECLARE_APPLICATION(Basic);