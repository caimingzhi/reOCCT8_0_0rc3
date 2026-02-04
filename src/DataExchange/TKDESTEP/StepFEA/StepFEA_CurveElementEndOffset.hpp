#pragma once


#include <Standard.hpp>

#include <StepFEA_CurveElementEndCoordinateSystem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>

//! Representation of STEP entity CurveElementEndOffset
class StepFEA_CurveElementEndOffset : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_CurveElementEndOffset();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const StepFEA_CurveElementEndCoordinateSystem&  aCoordinateSystem,
                            const occ::handle<NCollection_HArray1<double>>& aOffsetVector);

  //! Returns field CoordinateSystem
  Standard_EXPORT StepFEA_CurveElementEndCoordinateSystem CoordinateSystem() const;

  //! Set field CoordinateSystem
  Standard_EXPORT void SetCoordinateSystem(
    const StepFEA_CurveElementEndCoordinateSystem& CoordinateSystem);

  //! Returns field OffsetVector
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> OffsetVector() const;

  //! Set field OffsetVector
  Standard_EXPORT void SetOffsetVector(
    const occ::handle<NCollection_HArray1<double>>& OffsetVector);

  DEFINE_STANDARD_RTTIEXT(StepFEA_CurveElementEndOffset, Standard_Transient)

private:
  StepFEA_CurveElementEndCoordinateSystem  theCoordinateSystem;
  occ::handle<NCollection_HArray1<double>> theOffsetVector;
};

