#pragma once

#include <common.h>
#include <tgaimage.h>
#include "texture.h"

static Texture* loadTexture(const std::string& path)
{
    TGAImage img;
    img.read_tga_file(path.c_str());
    int width = img.get_width();
    int height = img.get_height();

    Color* pixels = new Color[width * height];
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            TGAColor c = img.get(i, j);
            pixels[i + j * width] = Color(c.bgra[2] / 255.0f, c.bgra[1] / 255.0f, c.bgra[0] / 255.0f, 1);
        }
    }

    return new Texture(pixels, width, height);
}

static void saveImage(const Color* pixels, int width, int height, std::string fileName)
{
    TGAImage image(width, height, TGAImage::RGBA);
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            auto color = pixels[i + j * width];
            image.set(i, j, TGAColor(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
        }
    }
    image.write_tga_file(fileName.c_str());
}