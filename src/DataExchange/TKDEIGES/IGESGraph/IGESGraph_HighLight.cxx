#include <IGESGraph_HighLight.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_HighLight, IGESData_IGESEntity)

IGESGraph_HighLight::IGESGraph_HighLight() = default;

void IGESGraph_HighLight::Init(const int nbProps, const int aHighLightStatus)
{
  theNbPropertyValues = nbProps;
  theHighLight        = aHighLightStatus;
  InitTypeAndForm(406, 20);
}

int IGESGraph_HighLight::NbPropertyValues() const
{
  return theNbPropertyValues;
}

int IGESGraph_HighLight::HighLightStatus() const
{
  return theHighLight;
}

bool IGESGraph_HighLight::IsHighLighted() const
{
  return (theHighLight != 0);
}
