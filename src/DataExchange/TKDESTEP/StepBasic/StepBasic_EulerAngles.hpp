#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>

class StepBasic_EulerAngles : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_EulerAngles();

  Standard_EXPORT void Init(const occ::handle<NCollection_HArray1<double>>& aAngles);

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> Angles() const;

  Standard_EXPORT void SetAngles(const occ::handle<NCollection_HArray1<double>>& Angles);

  DEFINE_STANDARD_RTTIEXT(StepBasic_EulerAngles, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<double>> theAngles;
};
