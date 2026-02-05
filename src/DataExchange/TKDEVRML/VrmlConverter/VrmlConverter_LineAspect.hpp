#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class Vrml_Material;

//! qualifies the aspect properties for
//! the VRML conversation of a Curve and a DeflectionCurve.
class VrmlConverter_LineAspect : public Standard_Transient
{

public:
  //! create a default LineAspect.
  //! Default value: HasMaterial = False - a line hasn't own material (color)
  Standard_EXPORT VrmlConverter_LineAspect();

  Standard_EXPORT VrmlConverter_LineAspect(const occ::handle<Vrml_Material>& aMaterial,
                                           const bool                        OnOff);

  Standard_EXPORT void SetMaterial(const occ::handle<Vrml_Material>& aMaterial);

  Standard_EXPORT occ::handle<Vrml_Material> Material() const;

  //! defines the necessary of writing own Material from Vrml into output OStream.
  //! By default False - the material is not writing into OStream,
  //! True - the material is writing.
  Standard_EXPORT void SetHasMaterial(const bool OnOff);

  //! returns True if the materials is writing into OStream.
  Standard_EXPORT bool HasMaterial() const;

  DEFINE_STANDARD_RTTIEXT(VrmlConverter_LineAspect, Standard_Transient)

private:
  occ::handle<Vrml_Material> myMaterial;
  bool                       myHasMaterial;
};
