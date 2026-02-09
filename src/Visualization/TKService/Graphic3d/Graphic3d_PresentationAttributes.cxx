#include <Graphic3d_PresentationAttributes.hpp>

#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_PresentationAttributes, Standard_Transient)

void Graphic3d_PresentationAttributes::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myBasicFillAreaAspect.get())

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myBasicColor)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myHiMethod)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myZLayer)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDispMode)
}
