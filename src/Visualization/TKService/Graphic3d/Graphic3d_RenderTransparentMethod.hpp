#pragma once

//! Enumerates transparency rendering methods supported by rasterization mode.
enum Graphic3d_RenderTransparentMethod
{
  Graphic3d_RTM_BLEND_UNORDERED, //!< Basic blend transparency with non-commuting blend operator
                                 //!< without sorting
  Graphic3d_RTM_BLEND_OIT, //!< Weighted Blended Order-Independent Transparency with depth weight
                           //!< factor
  Graphic3d_RTM_DEPTH_PEELING_OIT //!< Depth Peeling with specified number of depth layers
};
