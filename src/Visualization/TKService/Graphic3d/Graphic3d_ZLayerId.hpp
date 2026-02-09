#pragma once

#include <Standard_Integer.hpp>

typedef int Graphic3d_ZLayerId;

enum
{
  Graphic3d_ZLayerId_UNKNOWN = -1,
  Graphic3d_ZLayerId_Default = 0,
  Graphic3d_ZLayerId_Top     = -2,
  Graphic3d_ZLayerId_Topmost = -3,
  Graphic3d_ZLayerId_TopOSD  = -4,
  Graphic3d_ZLayerId_BotOSD  = -5
};
