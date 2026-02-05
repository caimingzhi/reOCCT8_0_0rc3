#include <IGESBasic_Hierarchy.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESBasic_Hierarchy, IGESData_IGESEntity)

IGESBasic_Hierarchy::IGESBasic_Hierarchy() = default;

void IGESBasic_Hierarchy::Init(const int nbPropVal,
                               const int aLineFont,
                               const int aView,
                               const int anEntityLevel,
                               const int aBlankStatus,
                               const int aLineWt,
                               const int aColorNum)
{
  theLineFont         = aLineFont;
  theView             = aView;
  theEntityLevel      = anEntityLevel;
  theBlankStatus      = aBlankStatus;
  theLineWeight       = aLineWt;
  theColorNum         = aColorNum;
  theNbPropertyValues = nbPropVal;
  InitTypeAndForm(406, 10);
}

int IGESBasic_Hierarchy::NbPropertyValues() const
{
  return theNbPropertyValues;
}

int IGESBasic_Hierarchy::NewLineFont() const
{
  return theLineFont;
}

int IGESBasic_Hierarchy::NewView() const
{
  return theView;
}

int IGESBasic_Hierarchy::NewEntityLevel() const
{
  return theEntityLevel;
}

int IGESBasic_Hierarchy::NewBlankStatus() const
{
  return theBlankStatus;
}

int IGESBasic_Hierarchy::NewLineWeight() const
{
  return theLineWeight;
}

int IGESBasic_Hierarchy::NewColorNum() const
{
  return theColorNum;
}
