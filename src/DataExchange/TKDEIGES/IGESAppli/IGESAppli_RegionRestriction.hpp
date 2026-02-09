#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESAppli_RegionRestriction : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_RegionRestriction();

  Standard_EXPORT void Init(const int nbPropVal,
                            const int aViasRest,
                            const int aCompoRest,
                            const int aCktRest);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT int ElectricalViasRestriction() const;

  Standard_EXPORT int ElectricalComponentRestriction() const;

  Standard_EXPORT int ElectricalCktRestriction() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_RegionRestriction, IGESData_IGESEntity)

private:
  int theNbPropertyValues;
  int theElectViasRestrict;
  int theElectCompRestrict;
  int theElectCktRestrict;
};
