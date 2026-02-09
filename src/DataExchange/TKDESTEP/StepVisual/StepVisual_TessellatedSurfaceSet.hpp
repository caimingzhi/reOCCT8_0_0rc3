#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <StepVisual_TessellatedItem.hpp>

#include <StepVisual_CoordinatesList.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

class StepVisual_TessellatedSurfaceSet : public StepVisual_TessellatedItem
{

public:
  Standard_EXPORT StepVisual_TessellatedSurfaceSet();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theRepresentationItem_Name,
                            const occ::handle<StepVisual_CoordinatesList>&  theCoordinates,
                            const int                                       thePnmax,
                            const occ::handle<NCollection_HArray2<double>>& theNormals);

  Standard_EXPORT occ::handle<StepVisual_CoordinatesList> Coordinates() const;

  Standard_EXPORT void SetCoordinates(
    const occ::handle<StepVisual_CoordinatesList>& theCoordinates);

  Standard_EXPORT int Pnmax() const;

  Standard_EXPORT void SetPnmax(const int thePnmax);

  Standard_EXPORT occ::handle<NCollection_HArray2<double>> Normals() const;

  Standard_EXPORT void SetNormals(const occ::handle<NCollection_HArray2<double>>& theNormals);

  Standard_EXPORT int NbNormals() const;

  DEFINE_STANDARD_RTTIEXT(StepVisual_TessellatedSurfaceSet, StepVisual_TessellatedItem)

private:
  occ::handle<StepVisual_CoordinatesList>  myCoordinates;
  int                                      myPnmax;
  occ::handle<NCollection_HArray2<double>> myNormals;
};
