#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Prs3d_Presentation.hpp>

class Prs3d_LineAspect;
class gp_Dir;
class gp_Pnt;
class Prs3d_ArrowAspect;
class Prs3d_TextAspect;

//! A framework for displaying the axes of an XYZ trihedron.
class DsgPrs_XYZAxisPresentation
{
public:
  DEFINE_STANDARD_ALLOC

  //! Draws each axis of a trihedron displayed in the
  //! presentation aPresentation and with lines shown by
  //! the values of aLineAspect. Each axis is defined by:
  //! -   the first and last points aPfirst and aPlast
  //! -   the direction aDir and
  //! -   the value aVal which provides a value for length.
  //! The value for length is provided so that the trihedron
  //! can vary in length relative to the scale of shape display.
  //! Each axis will be identified as X, Y, or Z by the text aText.
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_LineAspect>&   anLineAspect,
                                  const gp_Dir&                          aDir,
                                  const double                           aVal,
                                  const char*                            aText,
                                  const gp_Pnt&                          aPfirst,
                                  const gp_Pnt&                          aPlast);

  //! draws the presentation X ,Y ,Z axis
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                  const occ::handle<Prs3d_LineAspect>&   aLineAspect,
                                  const occ::handle<Prs3d_ArrowAspect>&  anArrowAspect,
                                  const occ::handle<Prs3d_TextAspect>&   aTextAspect,
                                  const gp_Dir&                          aDir,
                                  const double                           aVal,
                                  const char*                            aText,
                                  const gp_Pnt&                          aPfirst,
                                  const gp_Pnt&                          aPlast);
};
