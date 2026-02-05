#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Draw_Interpretor.hpp>

//! this package provides commands for curves and
//! surface.
class GeometryTest
{
public:
  DEFINE_STANDARD_ALLOC

  //! defines all geometric commands.
  Standard_EXPORT static void AllCommands(Draw_Interpretor& I);

  //! defines curve commands.
  Standard_EXPORT static void CurveCommands(Draw_Interpretor& I);

  //! defines tangent curve commands.
  Standard_EXPORT static void CurveTanCommands(Draw_Interpretor& I);

  //! defines fair curve commands.
  Standard_EXPORT static void FairCurveCommands(Draw_Interpretor& I);

  //! defines surface commands.
  Standard_EXPORT static void SurfaceCommands(Draw_Interpretor& I);

  //! defines constrained curves commands.
  Standard_EXPORT static void ConstraintCommands(Draw_Interpretor& I);

  //! defines commands to test the GeomAPI
  //! - Intersection
  //! - Extrema
  //! - Projection
  //! - Approximation, interpolation
  Standard_EXPORT static void APICommands(Draw_Interpretor& I);

  //! defines commands to check local
  //! continuity between curves or surfaces
  Standard_EXPORT static void ContinuityCommands(Draw_Interpretor& I);

  //! defines command to test the polyhedral
  //! triangulations and the polygons from the Poly package.
  Standard_EXPORT static void PolyCommands(Draw_Interpretor& I);

  //! defines commands to test projection of geometric objects
  Standard_EXPORT static void TestProjCommands(Draw_Interpretor& I);
};
