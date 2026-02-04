#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>

//! defines RegionRestriction, Type <406> Form <2>
//! in package IGESAppli
//! Defines regions to set an application's restriction
//! over a region.
class IGESAppli_RegionRestriction : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_RegionRestriction();

  //! This method is used to set the fields of the class
  //! RegionRestriction
  //! - nbPropVal  : Number of property values, always = 3
  //! - aViasRest  : Electrical Vias restriction
  //! - aCompoRest : Electrical components restriction
  //! - aCktRest   : Electrical circuitry restriction
  Standard_EXPORT void Init(const int nbPropVal,
                            const int aViasRest,
                            const int aCompoRest,
                            const int aCktRest);

  //! is always 3
  Standard_EXPORT int NbPropertyValues() const;

  //! returns the Electrical vias restriction
  //! is 0, 1 or 2
  Standard_EXPORT int ElectricalViasRestriction() const;

  //! returns the Electrical components restriction
  //! is 0, 1 or 2
  Standard_EXPORT int ElectricalComponentRestriction() const;

  //! returns the Electrical circuitry restriction
  //! is 0, 1 or 2
  Standard_EXPORT int ElectricalCktRestriction() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_RegionRestriction, IGESData_IGESEntity)

private:
  int theNbPropertyValues;
  int theElectViasRestrict;
  int theElectCompRestrict;
  int theElectCktRestrict;
};

