#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <IGESData_IGESEntity.hpp>

class IGESAppli_PWBDrilledHole : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESAppli_PWBDrilledHole();

  Standard_EXPORT void Init(const int    nbPropVal,
                            const double aDrillDia,
                            const double aFinishDia,
                            const int    aCode);

  Standard_EXPORT int NbPropertyValues() const;

  Standard_EXPORT double DrillDiameterSize() const;

  Standard_EXPORT double FinishDiameterSize() const;

  Standard_EXPORT int FunctionCode() const;

  DEFINE_STANDARD_RTTIEXT(IGESAppli_PWBDrilledHole, IGESData_IGESEntity)

private:
  int    theNbPropertyValues;
  double theDrillDiameter;
  double theFinishDiameter;
  int    theFunctionCode;
};
