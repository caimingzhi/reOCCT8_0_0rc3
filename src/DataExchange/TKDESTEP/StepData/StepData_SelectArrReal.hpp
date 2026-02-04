#pragma once


#include <Standard.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepData_SelectNamed.hpp>
#include <Standard_Integer.hpp>

class StepData_SelectArrReal : public StepData_SelectNamed
{

public:
  Standard_EXPORT StepData_SelectArrReal();

  Standard_EXPORT int Kind() const override;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> ArrReal() const;

  Standard_EXPORT void SetArrReal(const occ::handle<NCollection_HArray1<double>>& arr);

  DEFINE_STANDARD_RTTIEXT(StepData_SelectArrReal, StepData_SelectNamed)

private:
  occ::handle<NCollection_HArray1<double>> theArr;
};

