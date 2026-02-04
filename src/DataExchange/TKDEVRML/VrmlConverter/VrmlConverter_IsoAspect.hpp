#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <VrmlConverter_LineAspect.hpp>
class Vrml_Material;

//! qualifies the aspect properties for
//! the VRML conversation of iso curves.
class VrmlConverter_IsoAspect : public VrmlConverter_LineAspect
{

public:
  //! create a default IsoAspect.
  //! Default value: myNumber - 10.
  Standard_EXPORT VrmlConverter_IsoAspect();

  Standard_EXPORT VrmlConverter_IsoAspect(const occ::handle<Vrml_Material>& aMaterial,
                                          const bool                        OnOff,
                                          const int                         aNumber);

  Standard_EXPORT void SetNumber(const int aNumber);

  //! returns the number of U or V isoparametric curves drawn for a
  //! single face.
  Standard_EXPORT int Number() const;

  DEFINE_STANDARD_RTTIEXT(VrmlConverter_IsoAspect, VrmlConverter_LineAspect)

private:
  int myNumber;
};

