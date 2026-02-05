#include <TopoDS_TShape.hpp>
#include <TopoDS_Shape.hpp>

#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TopoDS_TShape, Standard_Transient)

//=================================================================================================

void TopoDS_TShape::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, this)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, ShapeType())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, NbChildren())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myFlags)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Free())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Free())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Locked())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Modified())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Checked())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Orientable())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Closed())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Infinite())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Convex())
}
