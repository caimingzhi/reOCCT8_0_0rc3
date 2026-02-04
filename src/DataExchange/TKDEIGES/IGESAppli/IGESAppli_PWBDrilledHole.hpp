#pragma once


#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>

//! defines PWBDrilledHole, Type <406> Form <26>
//! in package IGESAppli
//! Used to identify an entity that locates a drilled hole
//! and to specify the characteristics of the drilled hole
class IGESAppli_PWBDrilledHole : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_PWBDrilledHole();

  //! This method is used to set the fields of the class
  //! PWBDrilledHole
  //! - nbPropVal  : number of property values, always = 3
  //! - aDrillDia  : Drill diameter size
  //! - aFinishDia : Finish diameter size
  //! - aCode      : Function code for drilled hole
  Standard_EXPORT void Init(const int    nbPropVal,
                            const double aDrillDia,
                            const double aFinishDia,
                            const int    aCode);

  //! returns number of property values, always = 3
  Standard_EXPORT int NbPropertyValues() const;

  //! returns Drill diameter size
  Standard_EXPORT double DrillDiameterSize() const;

  //! returns Finish diameter size
  Standard_EXPORT double FinishDiameterSize() const;

  //! returns Function code for drilled hole
  //! is 0, 1, 2, 3, 4, 5 or 5001-9999
  Standard_EXPORT int FunctionCode() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_PWBDrilledHole, IGESData_IGESEntity)

private:
  int    theNbPropertyValues;
  double theDrillDiameter;
  double theFinishDiameter;
  int    theFunctionCode;
};

