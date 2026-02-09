#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
class IGESData_IGESModel;

class GeomToIGES_GeomEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToIGES_GeomEntity();

  Standard_EXPORT GeomToIGES_GeomEntity(const GeomToIGES_GeomEntity& GE);

  Standard_EXPORT void SetModel(const occ::handle<IGESData_IGESModel>& model);

  Standard_EXPORT occ::handle<IGESData_IGESModel> GetModel() const;

  Standard_EXPORT void SetUnit(const double unit);

  Standard_EXPORT double GetUnit() const;

private:
  occ::handle<IGESData_IGESModel> TheModel;
  double                          TheUnitFactor;
};
