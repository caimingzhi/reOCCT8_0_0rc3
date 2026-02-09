#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedStructuredItem.hpp>

#include <StepVisual_CoordinatesList.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <StepVisual_FaceOrSurface.hpp>

class StepVisual_TessellatedFace : public StepVisual_TessellatedStructuredItem
{

public:
  Standard_EXPORT StepVisual_TessellatedFace();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const occ::handle<StepVisual_CoordinatesList>&  theCoordinates,
                            const int                                       thePnmax,
                            const occ::handle<NCollection_HArray2<double>>& theNormals,
                            const bool                                      theHasGeometricLink,
                            const StepVisual_FaceOrSurface&                 theGeometricLink);

  Standard_EXPORT occ::handle<StepVisual_CoordinatesList> Coordinates() const;

  Standard_EXPORT void SetCoordinates(
    const occ::handle<StepVisual_CoordinatesList>& theCoordinates);

  Standard_EXPORT int Pnmax() const;

  Standard_EXPORT void SetPnmax(const int thePnmax);

  Standard_EXPORT occ::handle<NCollection_HArray2<double>> Normals() const;

  Standard_EXPORT void SetNormals(const occ::handle<NCollection_HArray2<double>>& theNormals);

  Standard_EXPORT int NbNormals() const;

  Standard_EXPORT StepVisual_FaceOrSurface GeometricLink() const;

  Standard_EXPORT void SetGeometricLink(const StepVisual_FaceOrSurface& theGeometricLink);

  Standard_EXPORT bool HasGeometricLink() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedFace, StepVisual_TessellatedStructuredItem)

private:
  occ::handle<StepVisual_CoordinatesList>  myCoordinates;
  int                                      myPnmax;
  occ::handle<NCollection_HArray2<double>> myNormals;
  StepVisual_FaceOrSurface                 myGeometricLink;
  bool                                     myHasGeometricLink;
};
