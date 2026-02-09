#pragma once

enum Aspect_GradientFillMethod
{
  Aspect_GradientFillMethod_None,
  Aspect_GradientFillMethod_Horizontal,
  Aspect_GradientFillMethod_Vertical,
  Aspect_GradientFillMethod_Diagonal1,

  Aspect_GradientFillMethod_Diagonal2,

  Aspect_GradientFillMethod_Corner1,
  Aspect_GradientFillMethod_Corner2,
  Aspect_GradientFillMethod_Corner3,
  Aspect_GradientFillMethod_Corner4,
  Aspect_GradientFillMethod_Elliptical,

  Aspect_GFM_NONE    = Aspect_GradientFillMethod_None,
  Aspect_GFM_HOR     = Aspect_GradientFillMethod_Horizontal,
  Aspect_GFM_VER     = Aspect_GradientFillMethod_Vertical,
  Aspect_GFM_DIAG1   = Aspect_GradientFillMethod_Diagonal1,
  Aspect_GFM_DIAG2   = Aspect_GradientFillMethod_Diagonal2,
  Aspect_GFM_CORNER1 = Aspect_GradientFillMethod_Corner1,
  Aspect_GFM_CORNER2 = Aspect_GradientFillMethod_Corner2,
  Aspect_GFM_CORNER3 = Aspect_GradientFillMethod_Corner3,
  Aspect_GFM_CORNER4 = Aspect_GradientFillMethod_Corner4
};
