#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepGeom_Point.hpp>
class TCollection_HAsciiString;

//! Representation of STEP entity FeaParametricPoint
class StepFEA_FeaParametricPoint : public StepGeom_Point
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_FeaParametricPoint();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
                            const occ::handle<NCollection_HArray1<double>>& aCoordinates);

  //! Returns field Coordinates
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> Coordinates() const;

  //! Set field Coordinates
  Standard_EXPORT void SetCoordinates(const occ::handle<NCollection_HArray1<double>>& Coordinates);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FeaParametricPoint, StepGeom_Point)

private:
  occ::handle<NCollection_HArray1<double>> theCoordinates;
};
