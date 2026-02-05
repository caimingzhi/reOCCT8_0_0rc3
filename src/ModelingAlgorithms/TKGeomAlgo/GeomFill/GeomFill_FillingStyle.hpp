#pragma once

//! Defines the three filling styles used in this package
//! -   GeomFill_Stretch - the style with the flattest patches
//! -   GeomFill_Coons - a rounded style of patch with
//! less depth than those of Curved
//! -   GeomFill_Curved - the style with the most rounded patches.
enum GeomFill_FillingStyle
{
  GeomFill_StretchStyle,
  GeomFill_CoonsStyle,
  GeomFill_CurvedStyle
};
