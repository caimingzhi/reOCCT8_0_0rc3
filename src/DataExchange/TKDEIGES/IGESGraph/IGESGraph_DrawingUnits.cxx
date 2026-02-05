#include <IGESGraph_DrawingUnits.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESGraph_DrawingUnits, IGESData_IGESEntity)

IGESGraph_DrawingUnits::IGESGraph_DrawingUnits() = default;

void IGESGraph_DrawingUnits::Init(const int                                    nbProps,
                                  const int                                    aFlag,
                                  const occ::handle<TCollection_HAsciiString>& anUnit)
{
  theNbPropertyValues = nbProps;
  theFlag             = aFlag;
  theUnit             = anUnit;
  InitTypeAndForm(406, 17);
}

int IGESGraph_DrawingUnits::NbPropertyValues() const
{
  return theNbPropertyValues;
}

int IGESGraph_DrawingUnits::Flag() const
{
  return theFlag;
}

occ::handle<TCollection_HAsciiString> IGESGraph_DrawingUnits::Unit() const
{
  return theUnit;
}

double IGESGraph_DrawingUnits::UnitValue() const
{
  switch (theFlag)
  {
    case 1:
      return 0.0254;
    case 2:
      return 0.001;
    case 3:
      return 1.;
    case 4:
      return 0.3048;
    case 5:
      return 1609.27;
    case 6:
      return 1.;
    case 7:
      return 1000.;
    case 8:
      return 0.0000254;
    case 9:
      return 0.000001;
    case 10:
      return 0.01;
    case 11:
      return 0.0000000254;
    default:
      break;
  }
  return 1.;
}
