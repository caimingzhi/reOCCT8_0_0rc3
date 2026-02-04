#pragma once


//! Defines the vertical position of the text
//! relative to its anchor.
enum Graphic3d_VerticalTextAlignment
{
  Graphic3d_VTA_BOTTOM, //!< The anchor lies on the last line of the text.
  Graphic3d_VTA_CENTER, //!< The anchor lies on the center of the text (not bounding box).
  Graphic3d_VTA_TOP,    //!< The anchor lies on the line preceding to the first line of the text.
  Graphic3d_VTA_TOPFIRSTLINE //!< The anchor lies on the first line of the text.
};

