#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedItem.hpp>

#include <StepVisual_CoordinatesList.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

//! Representation of STEP entity TessellatedSurfaceSet
class StepVisual_TessellatedSurfaceSet : public StepVisual_TessellatedItem
{

public:
  //! default constructor
  Standard_EXPORT StepVisual_TessellatedSurfaceSet();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const occ::handle<StepVisual_CoordinatesList>&  theCoordinates,
                            const int                                       thePnmax,
                            const occ::handle<NCollection_HArray2<double>>& theNormals);

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

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedSurfaceSet, StepVisual_TessellatedItem)

private:
  occ::handle<StepVisual_CoordinatesList>  myCoordinates;
  int                                      myPnmax;
  occ::handle<NCollection_HArray2<double>> myNormals;
};

