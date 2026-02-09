

#include <Vrml_Material.hpp>
#include <VrmlConverter_LineAspect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(VrmlConverter_LineAspect, Standard_Transient)

VrmlConverter_LineAspect::VrmlConverter_LineAspect()
{
  myHasMaterial = false;
}

VrmlConverter_LineAspect::VrmlConverter_LineAspect(const occ::handle<Vrml_Material>& aMaterial,
                                                   const bool                        OnOff)
{
  myMaterial    = aMaterial;
  myHasMaterial = OnOff;
}

void VrmlConverter_LineAspect::SetMaterial(const occ::handle<Vrml_Material>& aMaterial)
{
  myMaterial = aMaterial;
}

occ::handle<Vrml_Material> VrmlConverter_LineAspect::Material() const
{
  return myMaterial;
}

void VrmlConverter_LineAspect::SetHasMaterial(const bool OnOff)
{
  myHasMaterial = OnOff;
}

bool VrmlConverter_LineAspect::HasMaterial() const
{
  return myHasMaterial;
}
