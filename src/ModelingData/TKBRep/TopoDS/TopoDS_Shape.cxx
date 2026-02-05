#include <TopoDS_Shape.hpp>

#include <Standard_DomainError.hpp>
#include <Standard_NullObject.hpp>
#include <Standard_Dump.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS_TShape.hpp>

//=================================================================================================

void TopoDS_Shape::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_CLASS_BEGIN(theOStream, TopoDS_Shape)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myTShape.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myLocation)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myOrient)
}
