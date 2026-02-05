#include <IGESAppli_PWBDrilledHole.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_PWBDrilledHole, IGESData_IGESEntity)

IGESAppli_PWBDrilledHole::IGESAppli_PWBDrilledHole() = default;

void IGESAppli_PWBDrilledHole::Init(const int    nbPropVal,
                                    const double aDrillDia,
                                    const double aFinishDia,
                                    const int    aCode)
{
  theNbPropertyValues = nbPropVal;
  theDrillDiameter    = aDrillDia;
  theFinishDiameter   = aFinishDia;
  theFunctionCode     = aCode;
  InitTypeAndForm(406, 26);
}

int IGESAppli_PWBDrilledHole::NbPropertyValues() const
{
  return theNbPropertyValues;
}

double IGESAppli_PWBDrilledHole::DrillDiameterSize() const
{
  return theDrillDiameter;
}

double IGESAppli_PWBDrilledHole::FinishDiameterSize() const
{
  return theFinishDiameter;
}

int IGESAppli_PWBDrilledHole::FunctionCode() const
{
  return theFunctionCode;
}
