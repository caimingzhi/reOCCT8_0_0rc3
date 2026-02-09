#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class IGESData_IGESModel;

class Geom2dToIGES_Geom2dEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dToIGES_Geom2dEntity();

  Standard_EXPORT Geom2dToIGES_Geom2dEntity(const Geom2dToIGES_Geom2dEntity& GE);

  Standard_EXPORT void SetModel(const occ::handle<IGESData_IGESModel>& model);

  Standard_EXPORT occ::handle<IGESData_IGESModel> GetModel() const;

  Standard_EXPORT void SetUnit(const double unit);

  Standard_EXPORT double GetUnit() const;

private:
  occ::handle<IGESData_IGESModel> TheModel;
  double                          TheUnitFactor;
};
