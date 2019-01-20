#pragma once

#include <algorithm>

class MathUtil
{
public:
    static const float deg2rad;
    static const float rad2deg;
    static const float pi;

    static float radius(float degree)
    {
        return degree * deg2rad;
    }

    static float degree(float radius)
    {
        return rad2deg * rad2deg;
    }

    static float lerp(float a, float b, float t)
    {
        return a * (1 - t) + b;
    }

    /*static Vec2f lerp(const Vec2f& a, const Vec2f& b, float t)
    {
        return Vec2f(lerp(a.x, b.x, t), lerp(a.y, b.y, t));
    }*/

    /*static Vec3f lerp(Vec3f& a, Vec3f& b, float t)
    {
        return Vec3f(lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t));
    }*/

    static float clamp(float v, float minV, float maxV)
    {
        return std::min(std::max(v, minV), maxV);
    }

    static float clamp01(float v)
    {
        return std::min(std::max(v, 0.0f), 1.0f);
    }
};