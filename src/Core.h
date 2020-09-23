#pragma once

#include <Log/Log.h>

#include <cmath>

#define IK_ASSERT(x, ...) { if(!x) { IK_TRACE("Assertion Failed {0}", __VA_ARGS__); __asm("int3"); } }

