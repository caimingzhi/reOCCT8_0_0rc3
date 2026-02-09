

#include <Vrml_Material.hpp>
#include <VrmlConverter_PointAspect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(VrmlConverter_PointAspect, Standard_Transient)

VrmlConverter_PointAspect::VrmlConverter_PointAspect()
{
  myHasMaterial = false;
}

VrmlConverter_PointAspect::VrmlConverter_PointAspect(const occ::handle<Vrml_Material>& aMaterial,
                                                     const bool                        OnOff)
{
  myMaterial    = aMaterial;
  myHasMaterial = OnOff;
}

void VrmlConverter_PointAspect::SetMaterial(const occ::handle<Vrml_Material>& aMaterial)
{
  myMaterial = aMaterial;
}

occ::handle<Vrml_Material> VrmlConverter_PointAspect::Material() const
{
  return myMaterial;
}

void VrmlConverter_PointAspect::SetHasMaterial(const bool OnOff)
{
  myHasMaterial = OnOff;
}

bool VrmlConverter_PointAspect::HasMaterial() const
{
  return myHasMaterial;
}
