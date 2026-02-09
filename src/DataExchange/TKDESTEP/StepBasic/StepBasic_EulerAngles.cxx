#include <Standard_Type.hpp>
#include <StepBasic_EulerAngles.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_EulerAngles, Standard_Transient)

StepBasic_EulerAngles::StepBasic_EulerAngles() = default;

void StepBasic_EulerAngles::Init(const occ::handle<NCollection_HArray1<double>>& aAngles)
{

  theAngles = aAngles;
}

occ::handle<NCollection_HArray1<double>> StepBasic_EulerAngles::Angles() const
{
  return theAngles;
}

void StepBasic_EulerAngles::SetAngles(const occ::handle<NCollection_HArray1<double>>& aAngles)
{
  theAngles = aAngles;
}
