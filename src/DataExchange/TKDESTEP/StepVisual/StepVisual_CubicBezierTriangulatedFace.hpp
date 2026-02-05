#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedFace.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

//! Representation of STEP entity CubicBezierTriangulatedFace
class StepVisual_CubicBezierTriangulatedFace : public StepVisual_TessellatedFace
{

public:
  //! default constructor
  Standard_EXPORT StepVisual_CubicBezierTriangulatedFace();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&    theRepresentationItem_Name,
    const occ::handle<StepVisual_CoordinatesList>&  theTessellatedFace_Coordinates,
    const int                                       theTessellatedFace_Pnmax,
    const occ::handle<NCollection_HArray2<double>>& theTessellatedFace_Normals,
    const bool                                      theHasTessellatedFace_GeometricLink,
    const StepVisual_FaceOrSurface&                 theTessellatedFace_GeometricLink,
    const occ::handle<NCollection_HArray2<int>>&    theCtriangles);

  //! Returns field Ctriangles
  Standard_EXPORT occ::handle<NCollection_HArray2<int>> Ctriangles() const;

  //! Sets field Ctriangles
  Standard_EXPORT void SetCtriangles(const occ::handle<NCollection_HArray2<int>>& theCtriangles);

  //! Returns number of Ctriangles
  Standard_EXPORT int NbCtriangles() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_CubicBezierTriangulatedFace, StepVisual_TessellatedFace)

private:
  occ::handle<NCollection_HArray2<int>> myCtriangles;
};
