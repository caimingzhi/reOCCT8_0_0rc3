#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>

//! Representation of STEP entity EulerAngles
class StepBasic_EulerAngles : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_EulerAngles();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<NCollection_HArray1<double>>& aAngles);

  //! Returns field Angles
  Standard_EXPORT occ::handle<NCollection_HArray1<double>> Angles() const;

  //! Set field Angles
  Standard_EXPORT void SetAngles(const occ::handle<NCollection_HArray1<double>>& Angles);

  DEFINE_STANDARD_RTTIEXT(StepBasic_EulerAngles, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<double>> theAngles;
};
