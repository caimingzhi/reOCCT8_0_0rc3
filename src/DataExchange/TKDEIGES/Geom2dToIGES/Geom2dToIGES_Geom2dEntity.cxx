#include <Geom2dToIGES_Geom2dCurve.hpp>
#include <Geom2dToIGES_Geom2dEntity.hpp>
#include <Geom2dToIGES_Geom2dPoint.hpp>
#include <IGESData_IGESModel.hpp>

//=================================================================================================

Geom2dToIGES_Geom2dEntity::Geom2dToIGES_Geom2dEntity()
    : TheUnitFactor(0.)
{
}

//=================================================================================================

Geom2dToIGES_Geom2dEntity::Geom2dToIGES_Geom2dEntity(const Geom2dToIGES_Geom2dEntity& other)
{
  TheUnitFactor = other.GetUnit();
  TheModel      = other.GetModel();
}

//=================================================================================================

void Geom2dToIGES_Geom2dEntity::SetModel(const occ::handle<IGESData_IGESModel>& model)
{
  TheModel          = model;
  double unitfactor = TheModel->GlobalSection().UnitValue();
  TheUnitFactor     = unitfactor;
}

//=================================================================================================

occ::handle<IGESData_IGESModel> Geom2dToIGES_Geom2dEntity::GetModel() const
{
  return TheModel;
}

//=================================================================================================

void Geom2dToIGES_Geom2dEntity::SetUnit(const double unit)
{
  TheUnitFactor = unit;
}

//=================================================================================================

double Geom2dToIGES_Geom2dEntity::GetUnit() const
{
  return TheUnitFactor;
}
