#pragma once

//! Defines types of color assignments
//! Color of shape is defined following way
//! in dependance with type of color.
//! If type of color is XCAFDoc_ColorGen - then this color
//! defines default color for surfaces and curves.
//! If for shape color with types XCAFDoc_ColorSurf or XCAFDoc_ColorCurv is specified
//! then such color overrides generic color.
//! simple color
//! color of surfaces
//! color of curves
enum XCAFDoc_ColorType
{
  XCAFDoc_ColorGen,
  XCAFDoc_ColorSurf,
  XCAFDoc_ColorCurv
};
