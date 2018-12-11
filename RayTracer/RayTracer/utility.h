#pragma once

#include <cmath>
#include <algorithm>

float clamp(float value, float min, float max);
float clamp01(float value);

#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }