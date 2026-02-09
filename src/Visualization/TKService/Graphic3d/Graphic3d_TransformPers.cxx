

#include <Graphic3d_TransformPers.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_TransformPers, Standard_Transient)

void Graphic3d_TransformPers::PersParams3d::DumpJson(Standard_OStream& theOStream,
                                                     int               theDepth) const
{
  gp_Pnt anAttachPoint(PntX, PntY, PntZ);
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &anAttachPoint)
}

void Graphic3d_TransformPers::PersParams2d::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, OffsetX)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, OffsetY)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, Corner)
}

void Graphic3d_TransformPers::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myMode)

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myParams.Params3d)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myParams.Params2d)
}
