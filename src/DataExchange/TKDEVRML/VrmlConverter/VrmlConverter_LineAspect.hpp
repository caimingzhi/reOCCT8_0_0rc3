#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class Vrml_Material;

class VrmlConverter_LineAspect : public Standard_Transient
{

public:
  Standard_EXPORT VrmlConverter_LineAspect();

  Standard_EXPORT VrmlConverter_LineAspect(const occ::handle<Vrml_Material>& aMaterial,
                                           const bool                        OnOff);

  Standard_EXPORT void SetMaterial(const occ::handle<Vrml_Material>& aMaterial);

  Standard_EXPORT occ::handle<Vrml_Material> Material() const;

  Standard_EXPORT void SetHasMaterial(const bool OnOff);

  Standard_EXPORT bool HasMaterial() const;

  DEFINE_STANDARD_RTTIEXT(VrmlConverter_LineAspect, Standard_Transient)

private:
  occ::handle<Vrml_Material> myMaterial;
  bool                       myHasMaterial;
};
