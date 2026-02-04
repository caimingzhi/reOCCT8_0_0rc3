#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>

//! this package provides elementary commands for curves and
//! surface.
class GeomliteTest
{
public:
  DEFINE_STANDARD_ALLOC

  //! defines all geometric commands.
  Standard_EXPORT static void AllCommands(Draw_Interpretor& I);

  //! defines curve commands.
  Standard_EXPORT static void CurveCommands(Draw_Interpretor& I);

  //! defines surface commands.
  Standard_EXPORT static void SurfaceCommands(Draw_Interpretor& I);

  //! defines commands to test the Geom2dAPI
  //! - Intersection
  //! - Extrema
  //! - Projection
  //! - Approximation, interpolation
  Standard_EXPORT static void API2dCommands(Draw_Interpretor& I);

  //! defines constrained curves commands.
  Standard_EXPORT static void ApproxCommands(Draw_Interpretor& I);

  //! defines curves and surfaces modification commands.
  //! - Curve extension to point
  //! - Surface extension by length
  Standard_EXPORT static void ModificationCommands(Draw_Interpretor& I);
};

