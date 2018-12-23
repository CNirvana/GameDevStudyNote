#include "tinygl.h"

float edgeFunction(float Ax, float Ay, float Bx, float By, float Px, float Py)
{
    // return (Px - Ax) * (By - Ay) - (Py - Ay) * (Bx -Ax); // CW to right
    return (Ax - Bx) * (Py - Ay) - (Ay - By) * (Px - Ax); // CCW to left
}

bool inTriangle(float Ax, float Ay, float Bx, float By, float Cx, float Cy, float Px, float Py)
{
    bool inside = true;
    inside &= (edgeFunction(Ax, Ay, Bx, By, Px, Py) >= 0);
    inside &= (edgeFunction(Bx, By, Cx, Cy, Px, Py) >= 0);
    inside &= (edgeFunction(Cx, Cy, Ax, Ay, Px, Py) >= 0);

    return inside;
}