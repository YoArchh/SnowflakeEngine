#pragma once

#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <thread>
#include <mutex>
#include <queue>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Runtime/Core/Assertion.h"

/* -- Math -- */
#include "Runtime/Core/Math/Vector2.h"

#ifdef SNOWFLAKE_PLATFORM_WIN64
    #include <windows.h>
    #include <winuser.h>
#endif