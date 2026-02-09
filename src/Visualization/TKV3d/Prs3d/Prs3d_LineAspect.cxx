

#include <Prs3d_LineAspect.hpp>

#include <Standard_Dump.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Prs3d_LineAspect, Prs3d_BasicAspect)

Prs3d_LineAspect::Prs3d_LineAspect(const Quantity_Color&   theColor,
                                   const Aspect_TypeOfLine theType,
                                   const double            theWidth)
    : myAspect(new Graphic3d_AspectLine3d(theColor, theType, theWidth))
{
}

void Prs3d_LineAspect::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myAspect.get())
}
