#include <GeomToIGES_GeomEntity.hpp>
#include <IGESData_IGESModel.hpp>

GeomToIGES_GeomEntity::GeomToIGES_GeomEntity() = default;

GeomToIGES_GeomEntity::GeomToIGES_GeomEntity(const GeomToIGES_GeomEntity& other)
{
  TheUnitFactor = other.GetUnit();
  TheModel      = other.GetModel();
}

void GeomToIGES_GeomEntity::SetModel(const occ::handle<IGESData_IGESModel>& model)
{
  TheModel          = model;
  double unitfactor = TheModel->GlobalSection().UnitValue();
  TheUnitFactor     = unitfactor;
}

occ::handle<IGESData_IGESModel> GeomToIGES_GeomEntity::GetModel() const
{
  return TheModel;
}

void GeomToIGES_GeomEntity::SetUnit(const double unit)
{
  TheUnitFactor = unit;
}

double GeomToIGES_GeomEntity::GetUnit() const
{
  return TheUnitFactor;
}
