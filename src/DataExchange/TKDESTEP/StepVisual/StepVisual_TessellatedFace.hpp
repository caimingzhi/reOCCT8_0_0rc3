#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedStructuredItem.hpp>

#include <StepVisual_CoordinatesList.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <StepVisual_FaceOrSurface.hpp>

//! Representation of STEP entity TessellatedFace
class StepVisual_TessellatedFace : public StepVisual_TessellatedStructuredItem
{

public:
  //! default constructor
  Standard_EXPORT StepVisual_TessellatedFace();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const occ::handle<StepVisual_CoordinatesList>&  theCoordinates,
                            const int                                       thePnmax,
                            const occ::handle<NCollection_HArray2<double>>& theNormals,
                            const bool                                      theHasGeometricLink,
                            const StepVisual_FaceOrSurface&                 theGeometricLink);

  //! Returns field Coordinates
  Standard_EXPORT occ::handle<StepVisual_CoordinatesList> Coordinates() const;

  //! Sets field Coordinates
  Standard_EXPORT void SetCoordinates(
    const occ::handle<StepVisual_CoordinatesList>& theCoordinates);

  //! Returns field Pnmax
  Standard_EXPORT int Pnmax() const;

  //! Sets field Pnmax
  Standard_EXPORT void SetPnmax(const int thePnmax);

  //! Returns field Normals
  Standard_EXPORT occ::handle<NCollection_HArray2<double>> Normals() const;

  //! Sets field Normals
  Standard_EXPORT void SetNormals(const occ::handle<NCollection_HArray2<double>>& theNormals);

  //! Returns number of Normals
  Standard_EXPORT int NbNormals() const;

  //! Returns field GeometricLink
  Standard_EXPORT StepVisual_FaceOrSurface GeometricLink() const;

  //! Sets field GeometricLink
  Standard_EXPORT void SetGeometricLink(const StepVisual_FaceOrSurface& theGeometricLink);

  //! Returns True if optional field GeometricLink is defined
  Standard_EXPORT bool HasGeometricLink() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedFace, StepVisual_TessellatedStructuredItem)

private:
  occ::handle<StepVisual_CoordinatesList>  myCoordinates;
  int                                      myPnmax;
  occ::handle<NCollection_HArray2<double>> myNormals;
  StepVisual_FaceOrSurface                 myGeometricLink;    //!< optional
  bool                                     myHasGeometricLink; //!< flag "is GeometricLink defined"
};
