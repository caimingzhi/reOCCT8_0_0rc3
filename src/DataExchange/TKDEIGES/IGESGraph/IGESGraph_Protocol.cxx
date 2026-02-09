

#include <IGESGraph_Protocol.hpp>

#include <IGESBasic.hpp>
#include <IGESBasic_Protocol.hpp>
#include <IGESGraph_Color.hpp>
#include <IGESGraph_DefinitionLevel.hpp>
#include <IGESGraph_DrawingSize.hpp>
#include <IGESGraph_DrawingUnits.hpp>
#include <IGESGraph_HighLight.hpp>
#include <IGESGraph_IntercharacterSpacing.hpp>
#include <IGESGraph_LineFontDefPattern.hpp>
#include <IGESGraph_LineFontDefTemplate.hpp>
#include <IGESGraph_LineFontPredefined.hpp>
#include <IGESGraph_NominalSize.hpp>
#include <IGESGraph_Pick.hpp>
#include <IGESGraph_TextDisplayTemplate.hpp>
#include <IGESGraph_TextFontDef.hpp>
#include <IGESGraph_UniformRectGrid.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_Protocol, IGESData_Protocol)

IGESGraph_Protocol::IGESGraph_Protocol() = default;

int IGESGraph_Protocol::NbResources() const
{
  return 1;
}

occ::handle<Interface_Protocol> IGESGraph_Protocol::Resource(const int) const
{
  occ::handle<Interface_Protocol> res = IGESBasic::Protocol();
  return res;
}

int IGESGraph_Protocol::TypeNumber(const occ::handle<Standard_Type>& atype) const
{
  if (atype == STANDARD_TYPE(IGESGraph_Color))
    return 1;
  else if (atype == STANDARD_TYPE(IGESGraph_DefinitionLevel))
    return 2;
  else if (atype == STANDARD_TYPE(IGESGraph_DrawingSize))
    return 3;
  else if (atype == STANDARD_TYPE(IGESGraph_DrawingUnits))
    return 4;
  else if (atype == STANDARD_TYPE(IGESGraph_HighLight))
    return 5;
  else if (atype == STANDARD_TYPE(IGESGraph_IntercharacterSpacing))
    return 6;
  else if (atype == STANDARD_TYPE(IGESGraph_LineFontDefPattern))
    return 7;
  else if (atype == STANDARD_TYPE(IGESGraph_LineFontPredefined))
    return 8;
  else if (atype == STANDARD_TYPE(IGESGraph_LineFontDefTemplate))
    return 9;
  else if (atype == STANDARD_TYPE(IGESGraph_NominalSize))
    return 10;
  else if (atype == STANDARD_TYPE(IGESGraph_Pick))
    return 11;
  else if (atype == STANDARD_TYPE(IGESGraph_TextDisplayTemplate))
    return 12;
  else if (atype == STANDARD_TYPE(IGESGraph_TextFontDef))
    return 13;
  else if (atype == STANDARD_TYPE(IGESGraph_UniformRectGrid))
    return 14;
  return 0;
}
