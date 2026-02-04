#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Vrml_ShapeHints.hpp>
#include <Standard_Transient.hpp>
class Vrml_Material;

//! qualifies the aspect properties for
//! the VRML conversation of ShadedShape.
class VrmlConverter_ShadingAspect : public Standard_Transient
{

public:
  //! create a default ShadingAspect.
  Standard_EXPORT VrmlConverter_ShadingAspect();

  Standard_EXPORT void SetFrontMaterial(const occ::handle<Vrml_Material>& aMaterial);

  Standard_EXPORT occ::handle<Vrml_Material> FrontMaterial() const;

  Standard_EXPORT void SetShapeHints(const Vrml_ShapeHints& aShapeHints);

  Standard_EXPORT Vrml_ShapeHints ShapeHints() const;

  //! defines necessary of a calculation of normals for ShadedShape to more
  //! accurately display curved surfaces, pacticularly when smoooth or phong
  //! shading is used in VRML viewer.
  //! By default False - the normals are not calculated,
  //! True - the normals are calculated.
  //! Warning: If normals are calculated the resulting VRML file will
  //! be substantially lager.
  Standard_EXPORT void SetHasNormals(const bool OnOff);

  //! returns True if the normals are calculating
  Standard_EXPORT bool HasNormals() const;

  //! defines necessary of writing Material from Vrml into output OStream.
  //! By default False - the material is not writing into OStream,
  //! True - the material is writing.
  Standard_EXPORT void SetHasMaterial(const bool OnOff);

  //! returns True if the materials is writing into OStream.
  Standard_EXPORT bool HasMaterial() const;

  DEFINE_STANDARD_RTTIEXT(VrmlConverter_ShadingAspect, Standard_Transient)

private:
  occ::handle<Vrml_Material> myFrontMaterial;
  Vrml_ShapeHints            myShapeHints;
  bool                       myHasNormals;
  bool                       myHasMaterial;
};

