

#include <Standard_Type.hpp>
#include <Vrml_Material.hpp>
#include <VrmlConverter_ShadingAspect.hpp>

IMPLEMENT_STANDARD_RTTIEXT(VrmlConverter_ShadingAspect, Standard_Transient)

VrmlConverter_ShadingAspect::VrmlConverter_ShadingAspect()
{
  occ::handle<Vrml_Material> m = new Vrml_Material;
  Vrml_ShapeHints            sh;
  myFrontMaterial = m;
  myShapeHints    = sh;
  myHasNormals    = false;
  myHasMaterial   = false;
}

void VrmlConverter_ShadingAspect::SetFrontMaterial(const occ::handle<Vrml_Material>& aMaterial)
{
  myFrontMaterial = aMaterial;
}

occ::handle<Vrml_Material> VrmlConverter_ShadingAspect::FrontMaterial() const
{
  return myFrontMaterial;
}

void VrmlConverter_ShadingAspect::SetShapeHints(const Vrml_ShapeHints& aShapeHints)
{
  myShapeHints = aShapeHints;
}

Vrml_ShapeHints VrmlConverter_ShadingAspect::ShapeHints() const
{
  return myShapeHints;
}

void VrmlConverter_ShadingAspect::SetHasNormals(const bool OnOff)
{
  myHasNormals = OnOff;
}

bool VrmlConverter_ShadingAspect::HasNormals() const
{
  return myHasNormals;
}

void VrmlConverter_ShadingAspect::SetHasMaterial(const bool OnOff)
{
  myHasMaterial = OnOff;
}

bool VrmlConverter_ShadingAspect::HasMaterial() const
{
  return myHasMaterial;
}
