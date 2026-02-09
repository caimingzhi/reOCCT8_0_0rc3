

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <Standard_Type.hpp>
#include <StepData_Described.hpp>
#include <StepData_EDescr.hpp>
#include <StepData_Simple.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepData_Described, Standard_Transient)

StepData_Described::StepData_Described(const occ::handle<StepData_EDescr>& descr)
    : thedescr(descr)
{
}

occ::handle<StepData_EDescr> StepData_Described::Description() const
{
  return thedescr;
}
