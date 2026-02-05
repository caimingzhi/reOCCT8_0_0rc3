#include <IGESAppli_RegionRestriction.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_RegionRestriction, IGESData_IGESEntity)

IGESAppli_RegionRestriction::IGESAppli_RegionRestriction() = default;

void IGESAppli_RegionRestriction::Init(const int nbPropVal,
                                       const int aViasRest,
                                       const int aCompoRest,
                                       const int aCktRest)
{
  theNbPropertyValues  = nbPropVal;
  theElectViasRestrict = aViasRest;
  theElectCompRestrict = aCompoRest;
  theElectCktRestrict  = aCktRest;
  InitTypeAndForm(406, 2);
}

int IGESAppli_RegionRestriction::NbPropertyValues() const
{
  return theNbPropertyValues;
}

int IGESAppli_RegionRestriction::ElectricalViasRestriction() const
{
  return theElectViasRestrict;
}

int IGESAppli_RegionRestriction::ElectricalComponentRestriction() const
{
  return theElectCompRestrict;
}

int IGESAppli_RegionRestriction::ElectricalCktRestriction() const
{
  return theElectCktRestrict;
}
