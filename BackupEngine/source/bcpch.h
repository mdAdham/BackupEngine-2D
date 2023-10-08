#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <filesystem>
#include <fstream>
#include <direct.h>
#include <random>
#include <unordered_map>

#include "BackupEngine/Core/Log.h"

#ifdef EN_PLATFORM_WINDOWS
#define NOMINMAX
#include <Windows.h>
#endif // EN_PLATFORM_WINDOWS
