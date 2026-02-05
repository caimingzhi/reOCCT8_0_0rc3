#include <IGESGraph_Pick.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_Pick, IGESData_IGESEntity)

IGESGraph_Pick::IGESGraph_Pick() = default;

void IGESGraph_Pick::Init(const int nbProps, const int aPickStatus)
{
  theNbPropertyValues = nbProps;
  thePick             = aPickStatus;
  InitTypeAndForm(406, 21);
}

int IGESGraph_Pick::NbPropertyValues() const
{
  return theNbPropertyValues;
}

int IGESGraph_Pick::PickFlag() const
{
  return thePick;
}

bool IGESGraph_Pick::IsPickable() const
{
  return (thePick == 0);
}
