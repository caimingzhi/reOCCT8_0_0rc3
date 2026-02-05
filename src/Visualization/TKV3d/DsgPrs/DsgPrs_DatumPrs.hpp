#pragma once

#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Root.hpp>

//! A framework for displaying an XYZ trihedron.
class DsgPrs_DatumPrs : public Prs3d_Root
{
public:
  DEFINE_STANDARD_ALLOC

  //! Draw XYZ axes at specified location with attributes defined by the attribute manager
  //! theDrawer:
  //! - Prs3d_DatumAspect defines arrow, line and length trihedron axis parameters,
  //! - Prs3d_TextAspect defines displayed text.
  //! The thihedron origin and axis directions are defined by theDatum coordinate system.
  //! DsgPrs_XYZAxisPresentation framework is used to create graphical primitives for each axis.
  //! Axes are marked with "X", "Y", "Z" text.
  //! @param[out] thePresentation  the modified presentation
  //! @param[in] theDatum  the source of trihedron position
  //! @param[in] theDrawer  the provider of display attributes
  Standard_EXPORT static void Add(const occ::handle<Prs3d_Presentation>& thePresentation,
                                  const gp_Ax2&                          theDatum,
                                  const occ::handle<Prs3d_Drawer>&       theDrawer);
};
