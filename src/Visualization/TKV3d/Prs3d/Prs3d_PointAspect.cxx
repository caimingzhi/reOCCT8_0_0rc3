

#include <Prs3d_PointAspect.hpp>

#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Prs3d_PointAspect, Prs3d_BasicAspect)

Prs3d_PointAspect::Prs3d_PointAspect(const Aspect_TypeOfMarker theType,
                                     const Quantity_Color&     theColor,
                                     const double              theScale)
    : myAspect(new Graphic3d_AspectMarker3d(theType, theColor, theScale))
{
}

Prs3d_PointAspect::Prs3d_PointAspect(const Quantity_Color&                            theColor,
                                     const int                                        theWidth,
                                     const int                                        theHeight,
                                     const occ::handle<NCollection_HArray1<uint8_t>>& theTexture)
    : myAspect(new Graphic3d_AspectMarker3d(theColor, theWidth, theHeight, theTexture))
{
}

void Prs3d_PointAspect::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myAspect.get())
}
