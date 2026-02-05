#include <IGESAppli_DrilledHole.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_DrilledHole, IGESData_IGESEntity)

IGESAppli_DrilledHole::IGESAppli_DrilledHole() = default;

void IGESAppli_DrilledHole::Init(const int    nbPropVal,
                                 const double aSize,
                                 const double anotherSize,
                                 const int    aPlating,
                                 const int    aLayer,
                                 const int    anotherLayer)
{
  theNbPropertyValues = nbPropVal;
  theDrillDiaSize     = aSize;
  theFinishDiaSize    = anotherSize;
  thePlatingFlag      = aPlating;
  theNbLowerLayer     = aLayer;
  theNbHigherLayer    = anotherLayer;
  InitTypeAndForm(406, 6);
}

int IGESAppli_DrilledHole::NbPropertyValues() const
{
  return theNbPropertyValues;
}

double IGESAppli_DrilledHole::DrillDiaSize() const
{
  return theDrillDiaSize;
}

double IGESAppli_DrilledHole::FinishDiaSize() const
{
  return theFinishDiaSize;
}

bool IGESAppli_DrilledHole::IsPlating() const
{
  return (thePlatingFlag != 0);
}

int IGESAppli_DrilledHole::NbLowerLayer() const
{
  return theNbLowerLayer;
}

int IGESAppli_DrilledHole::NbHigherLayer() const
{
  return theNbHigherLayer;
}
