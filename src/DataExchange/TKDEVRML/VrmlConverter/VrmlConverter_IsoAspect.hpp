#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <VrmlConverter_LineAspect.hpp>
class Vrml_Material;

class VrmlConverter_IsoAspect : public VrmlConverter_LineAspect
{

public:
  Standard_EXPORT VrmlConverter_IsoAspect();

  Standard_EXPORT VrmlConverter_IsoAspect(const occ::handle<Vrml_Material>& aMaterial,
                                          const bool                        OnOff,
                                          const int                         aNumber);

  Standard_EXPORT void SetNumber(const int aNumber);

  Standard_EXPORT int Number() const;

  DEFINE_STANDARD_RTTIEXT(VrmlConverter_IsoAspect, VrmlConverter_LineAspect)

private:
  int myNumber;
};
