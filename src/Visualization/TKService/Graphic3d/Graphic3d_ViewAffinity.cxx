#include <Graphic3d_ViewAffinity.hpp>

#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_ViewAffinity, Standard_Transient)

void Graphic3d_ViewAffinity::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myMask)
}
