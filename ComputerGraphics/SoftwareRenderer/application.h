#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <common.h>
#include "tinygl.h"
#include "mesh.h"
#include "util.h"

class Application
{
public:
    Application(const std::string& title, int screenWidth, int screenHeight)
        : m_Window(nullptr), m_Renderer(nullptr), m_Texture(nullptr), m_BackBuffer(nullptr), m_GLContext(nullptr),
        m_Title(title), m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight)
    {
    }
    virtual ~Application()
    {
        SAFE_DELETE(m_GLContext);
        if (m_BackBuffer) delete[] m_BackBuffer;
    }

    bool initialize()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_CreateWindowAndRenderer(m_ScreenWidth, m_ScreenHeight, 0, &m_Window, &m_Renderer);
        m_Texture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, m_ScreenWidth, m_ScreenHeight);
        m_BackBuffer = new Uint32[m_ScreenWidth * m_ScreenHeight];

        m_GLContext = new TinyGL();
        m_GLContext->initialize(m_ScreenWidth, m_ScreenHeight);
    }

    void shutdown()
    {
        SDL_Quit();
    }

    void run()
    {
        SDL_Event ev;
        float lastTime = SDL_GetTicks() * 0.001f - 0.016f;
        float debugTime = SDL_GetTicks() * 0.001f;
        m_CurrentTime = debugTime;

        setup();

        while (true)
        {
            if (SDL_PollEvent(&ev) && ev.type == SDL_QUIT)
            {
                break;
            }

            m_CurrentTime = SDL_GetTicks() * 0.001f;
            float dt = m_CurrentTime - lastTime;
            lastTime = m_CurrentTime;

            update(dt);
            swapBuffer();

            if (m_CurrentTime - debugTime > 1.0f)
            {
                std::cout << "FPS: " << (int)(1 / dt) << std::endl;
                debugTime = m_CurrentTime;
            }
        }

        destroy();
    }

    TinyGL* getGLContext() const { return m_GLContext; }
    int getScreenWidth() const { return m_ScreenWidth; }
    int getScreenHeight() const { return m_ScreenHeight; }
    float getTime() const { return m_CurrentTime; }

protected:
    virtual void setup() {}
    virtual void update(float dt) {}
    virtual void destroy() {}

    void swapBuffer()
    {
        auto colorBuffer = m_GLContext->getFrameBuffer()->getColorBuffer();
        auto pixels = colorBuffer->getPixels();

        for (int i = 0; i < m_ScreenHeight; i++)
        {
            for (int j = 0; j < m_ScreenWidth; j++)
            {
                Uint32 iColor = ((uint8_t)(255.0f * pixels[i * m_ScreenWidth + j].b) << 16) |
                    ((uint8_t)(255.0f * pixels[i * m_ScreenWidth + j].g) << 8) |
                    ((uint8_t)(255.0f * pixels[i * m_ScreenWidth + j].r)) & 0xffffff;

                m_BackBuffer[i * m_ScreenWidth + j] = iColor;
            }
        }

        SDL_UpdateTexture(m_Texture, NULL, m_BackBuffer, m_ScreenWidth * sizeof(Uint32));
        SDL_RenderClear(m_Renderer);
        SDL_RenderCopy(m_Renderer, m_Texture, NULL, NULL);
        SDL_RenderPresent(m_Renderer);
    }

private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Texture* m_Texture;
    Uint32* m_BackBuffer;
    TinyGL* m_GLContext;

    int m_ScreenWidth;
    int m_ScreenHeight;
    std::string m_Title;
    float m_CurrentTime;

};