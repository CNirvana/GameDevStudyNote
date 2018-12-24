#pragma once

class MathUtil
{
public:
    static const float deg2rad;
    static const float rad2deg;

    static float radius(float degree)
    {
        return degree * deg2rad;
    }

    static float degree(float radius)
    {
        return rad2deg * rad2deg;
    }
};