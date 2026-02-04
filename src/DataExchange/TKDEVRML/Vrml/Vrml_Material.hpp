#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Quantity_Color.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>

//! defines a Material node of VRML specifying properties of geometry
//! and its appearance.
//! This node defines the current surface material properties for all subsequent shapes.
//! Material sets several components of the current material during traversal. Different shapes
//! interpret materials with multiple values differently. To bind materials to shapes, use a
//! MaterialBinding node.
class Vrml_Material : public Standard_Transient
{

public:
  Standard_EXPORT Vrml_Material(
    const occ::handle<NCollection_HArray1<Quantity_Color>>& aAmbientColor,
    const occ::handle<NCollection_HArray1<Quantity_Color>>& aDiffuseColor,
    const occ::handle<NCollection_HArray1<Quantity_Color>>& aSpecularColor,
    const occ::handle<NCollection_HArray1<Quantity_Color>>& aEmissiveColor,
    const occ::handle<NCollection_HArray1<double>>&         aShininess,
    const occ::handle<NCollection_HArray1<double>>&         aTransparency);

  Standard_EXPORT Vrml_Material();

  Standard_EXPORT void SetAmbientColor(
    const occ::handle<NCollection_HArray1<Quantity_Color>>& aAmbientColor);

  Standard_EXPORT occ::handle<NCollection_HArray1<Quantity_Color>> AmbientColor() const;

  Standard_EXPORT void SetDiffuseColor(
    const occ::handle<NCollection_HArray1<Quantity_Color>>& aDiffuseColor);

  Standard_EXPORT occ::handle<NCollection_HArray1<Quantity_Color>> DiffuseColor() const;

  Standard_EXPORT void SetSpecularColor(
    const occ::handle<NCollection_HArray1<Quantity_Color>>& aSpecularColor);

  Standard_EXPORT occ::handle<NCollection_HArray1<Quantity_Color>> SpecularColor() const;

  Standard_EXPORT void SetEmissiveColor(
    const occ::handle<NCollection_HArray1<Quantity_Color>>& aEmissiveColor);

  Standard_EXPORT occ::handle<NCollection_HArray1<Quantity_Color>> EmissiveColor() const;

  Standard_EXPORT void SetShininess(const occ::handle<NCollection_HArray1<double>>& aShininess);

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> Shininess() const;

  Standard_EXPORT void SetTransparency(
    const occ::handle<NCollection_HArray1<double>>& aTransparency);

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> Transparency() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

  DEFINE_STANDARD_RTTIEXT(Vrml_Material, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<Quantity_Color>> myAmbientColor;
  occ::handle<NCollection_HArray1<Quantity_Color>> myDiffuseColor;
  occ::handle<NCollection_HArray1<Quantity_Color>> mySpecularColor;
  occ::handle<NCollection_HArray1<Quantity_Color>> myEmissiveColor;
  occ::handle<NCollection_HArray1<double>>         myShininess;
  occ::handle<NCollection_HArray1<double>>         myTransparency;
};

