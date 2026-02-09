

#include <Prs3d_PlaneAspect.hpp>

#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Prs3d_PlaneAspect, Prs3d_BasicAspect)

Prs3d_PlaneAspect::Prs3d_PlaneAspect()
    : myEdgesAspect(new Prs3d_LineAspect(Quantity_NOC_GREEN, Aspect_TOL_SOLID, 1.0)),
      myIsoAspect(new Prs3d_LineAspect(Quantity_NOC_GRAY75, Aspect_TOL_SOLID, 0.5)),
      myArrowAspect(new Prs3d_LineAspect(Quantity_NOC_PEACHPUFF, Aspect_TOL_SOLID, 1.0)),
      myArrowsLength(0.02),
      myArrowsSize(0.1),
      myArrowsAngle(M_PI / 8.0),
      myPlaneXLength(1.0),
      myPlaneYLength(1.0),
      myIsoDistance(0.5),
      myDrawCenterArrow(false),
      myDrawEdgesArrows(false),
      myDrawEdges(true),
      myDrawIso(false)
{
}

void Prs3d_PlaneAspect::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myEdgesAspect.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myIsoAspect.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myArrowAspect.get())

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myArrowsLength)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myArrowsSize)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myArrowsAngle)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myPlaneXLength)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myPlaneYLength)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsoDistance)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDrawCenterArrow)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDrawEdgesArrows)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDrawEdges)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDrawIso)
}
