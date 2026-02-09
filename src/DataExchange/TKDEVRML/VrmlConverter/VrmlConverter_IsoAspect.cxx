

#include <Vrml_Material.hpp>
#include <VrmlConverter_IsoAspect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(VrmlConverter_IsoAspect, VrmlConverter_LineAspect)

VrmlConverter_IsoAspect::VrmlConverter_IsoAspect()

{
  myNumber = 10;
}

VrmlConverter_IsoAspect::VrmlConverter_IsoAspect(const occ::handle<Vrml_Material>& aMaterial,
                                                 const bool                        OnOff,
                                                 const int                         aNumber)
    : VrmlConverter_LineAspect(aMaterial, OnOff)
{
  myNumber = aNumber;
}

void VrmlConverter_IsoAspect::SetNumber(const int aNumber)
{
  myNumber = aNumber;
}

int VrmlConverter_IsoAspect::Number() const
{
  return myNumber;
}
