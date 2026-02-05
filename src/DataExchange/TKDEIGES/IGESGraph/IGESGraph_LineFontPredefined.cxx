#include <IGESGraph_LineFontPredefined.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_LineFontPredefined, IGESData_IGESEntity)

IGESGraph_LineFontPredefined::IGESGraph_LineFontPredefined() = default;

void IGESGraph_LineFontPredefined::Init(const int nbProps, const int aLineFontPatternCode)
{
  theNbPropertyValues    = nbProps;
  theLineFontPatternCode = aLineFontPatternCode;
  InitTypeAndForm(406, 19);
}

int IGESGraph_LineFontPredefined::NbPropertyValues() const
{
  return theNbPropertyValues;
}

int IGESGraph_LineFontPredefined::LineFontPatternCode() const
{
  return theLineFontPatternCode;
}
