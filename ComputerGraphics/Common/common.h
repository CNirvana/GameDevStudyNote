#pragma once

#include <iostream>
#include <algorithm>

#include <string>
#include <vector>
#include <limits>

#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }