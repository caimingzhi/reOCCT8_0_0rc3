// Created on : Thu Mar 24 18:30:11 2022

#include <StepVisual_CubicBezierTriangulatedFace.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepVisual_CubicBezierTriangulatedFace, StepVisual_TessellatedFace)

//=================================================================================================

StepVisual_CubicBezierTriangulatedFace::StepVisual_CubicBezierTriangulatedFace() = default;

//=================================================================================================

void StepVisual_CubicBezierTriangulatedFace::Init(
  const occ::handle<TCollection_HAsciiString>&    theRepresentationItem_Name,
  const occ::handle<StepVisual_CoordinatesList>&  theTessellatedFace_Coordinates,
  const int                                       theTessellatedFace_Pnmax,
  const occ::handle<NCollection_HArray2<double>>& theTessellatedFace_Normals,
  const bool                                      theHasTessellatedFace_GeometricLink,
  const StepVisual_FaceOrSurface&                 theTessellatedFace_GeometricLink,
  const occ::handle<NCollection_HArray2<int>>&    theCtriangles)
{
  StepVisual_TessellatedFace::Init(theRepresentationItem_Name,
                                   theTessellatedFace_Coordinates,
                                   theTessellatedFace_Pnmax,
                                   theTessellatedFace_Normals,
                                   theHasTessellatedFace_GeometricLink,
                                   theTessellatedFace_GeometricLink);

  myCtriangles = theCtriangles;
}

//=================================================================================================

occ::handle<NCollection_HArray2<int>> StepVisual_CubicBezierTriangulatedFace::Ctriangles() const
{
  return myCtriangles;
}

//=================================================================================================

void StepVisual_CubicBezierTriangulatedFace::SetCtriangles(
  const occ::handle<NCollection_HArray2<int>>& theCtriangles)
{
  myCtriangles = theCtriangles;
}

int StepVisual_CubicBezierTriangulatedFace::NbCtriangles() const
{
  if (myCtriangles.IsNull())
  {
    return 0;
  }
  return myCtriangles->ColLength();
}
