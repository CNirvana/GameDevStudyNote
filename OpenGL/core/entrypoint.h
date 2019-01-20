#pragma once

#include "application.h"

extern Application* CreateApplication();

int main(int argc, char** argv)
{
    auto app = CreateApplication();
    if (!app->setup())
    {
        return -1;
    }

    app->run();
    app->shutdown();
    delete app;
    return 0;
}