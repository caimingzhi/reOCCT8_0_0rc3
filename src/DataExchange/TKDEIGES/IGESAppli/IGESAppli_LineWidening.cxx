#include <IGESAppli_LineWidening.hpp>
#include <IGESData_LevelListEntity.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_LineWidening, IGESData_IGESEntity)

IGESAppli_LineWidening::IGESAppli_LineWidening() = default;

void IGESAppli_LineWidening::Init(const int    nbPropVal,
                                  const double aWidth,
                                  const int    aCornering,
                                  const int    aExtnFlag,
                                  const int    aJustifFlag,
                                  const double aExtnVal)
{
  theNbPropertyValues  = nbPropVal;
  theWidth             = aWidth;
  theCorneringCode     = aCornering;
  theExtensionFlag     = aExtnFlag;
  theJustificationFlag = aJustifFlag;
  theExtensionValue    = aExtnVal;
  InitTypeAndForm(406, 5);
}

int IGESAppli_LineWidening::NbPropertyValues() const
{
  return theNbPropertyValues;
}

double IGESAppli_LineWidening::WidthOfMetalization() const
{
  return theWidth;
}

int IGESAppli_LineWidening::CorneringCode() const
{
  return theCorneringCode;
}

int IGESAppli_LineWidening::ExtensionFlag() const
{
  return theExtensionFlag;
}

int IGESAppli_LineWidening::JustificationFlag() const
{
  return theJustificationFlag;
}

double IGESAppli_LineWidening::ExtensionValue() const
{
  return theExtensionValue;
}
