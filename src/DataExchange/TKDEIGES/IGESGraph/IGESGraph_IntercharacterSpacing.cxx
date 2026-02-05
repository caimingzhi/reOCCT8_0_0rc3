#include <IGESGraph_IntercharacterSpacing.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_IntercharacterSpacing, IGESData_IGESEntity)

IGESGraph_IntercharacterSpacing::IGESGraph_IntercharacterSpacing() = default;

void IGESGraph_IntercharacterSpacing::Init(const int nbProps, const double anISpace)
{
  theNbPropertyValues = nbProps;
  theISpace           = anISpace;
  InitTypeAndForm(406, 18);
}

int IGESGraph_IntercharacterSpacing::NbPropertyValues() const
{
  return theNbPropertyValues;
}

double IGESGraph_IntercharacterSpacing::ISpace() const
{
  return theISpace;
}
