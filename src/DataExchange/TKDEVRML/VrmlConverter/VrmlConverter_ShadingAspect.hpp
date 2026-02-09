#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Vrml_ShapeHints.hpp>
#include <Standard_Transient.hpp>
class Vrml_Material;

class VrmlConverter_ShadingAspect : public Standard_Transient
{

public:
  Standard_EXPORT VrmlConverter_ShadingAspect();

  Standard_EXPORT void SetFrontMaterial(const occ::handle<Vrml_Material>& aMaterial);

  Standard_EXPORT occ::handle<Vrml_Material> FrontMaterial() const;

  Standard_EXPORT void SetShapeHints(const Vrml_ShapeHints& aShapeHints);

  Standard_EXPORT Vrml_ShapeHints ShapeHints() const;

  Standard_EXPORT void SetHasNormals(const bool OnOff);

  Standard_EXPORT bool HasNormals() const;

  Standard_EXPORT void SetHasMaterial(const bool OnOff);

  Standard_EXPORT bool HasMaterial() const;

  DEFINE_STANDARD_RTTIEXT(VrmlConverter_ShadingAspect, Standard_Transient)

private:
  occ::handle<Vrml_Material> myFrontMaterial;
  Vrml_ShapeHints            myShapeHints;
  bool                       myHasNormals;
  bool                       myHasMaterial;
};
