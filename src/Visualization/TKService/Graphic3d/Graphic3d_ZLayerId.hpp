#pragma once


#include <Standard_Integer.hpp>

typedef int Graphic3d_ZLayerId;

//! This enumeration defines the list of predefined layers, which can not be removed (but settings
//! can be overridden). Custom layers might be added with positive index (>= 1) if standard list is
//! insufficient for application needs; these layers will be displayed on top of predefined ones.
enum
{
  Graphic3d_ZLayerId_UNKNOWN = -1, //!< identifier for invalid ZLayer
  Graphic3d_ZLayerId_Default = 0,  //!< default Z-layer for main presentations
  Graphic3d_ZLayerId_Top =
    -2, //!< overlay for 3D presentations which inherits Depth from previous ZLayer
  Graphic3d_ZLayerId_Topmost = -3, //!< overlay for 3D presentations with independent Depth
  Graphic3d_ZLayerId_TopOSD  = -4, //!< overlay for 2D presentations (On-Screen-Display)
  Graphic3d_ZLayerId_BotOSD  = -5  //!< underlay for 2D presentations (On-Screen-Display)
};

