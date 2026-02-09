#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_Point.hpp>
class TCollection_HAsciiString;

class StepFEA_FeaParametricPoint : public StepGeom_Point
{

public:
  Standard_EXPORT StepFEA_FeaParametricPoint();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const occ::handle<NCollection_HArray1<double>>& aCoordinates);

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> Coordinates() const;

  Standard_EXPORT void SetCoordinates(const occ::handle<NCollection_HArray1<double>>& Coordinates);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaParametricPoint, StepGeom_Point)

private:
  occ::handle<NCollection_HArray1<double>> theCoordinates;
};
