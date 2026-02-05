#include <Graphic3d_CameraTile.hpp>

#include <Standard_Dump.hpp>

//=================================================================================================

void Graphic3d_CameraTile::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &TotalSize)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &TileSize)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &Offset)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsTopDown)
}
