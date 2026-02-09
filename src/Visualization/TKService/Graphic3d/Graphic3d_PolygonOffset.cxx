

#include <Graphic3d_PolygonOffset.hpp>

#include <Standard_Dump.hpp>

void Graphic3d_PolygonOffset::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, Graphic3d_PolygonOffset)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Mode)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Factor)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Units)
}
