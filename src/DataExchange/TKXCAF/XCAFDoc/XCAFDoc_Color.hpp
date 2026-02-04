#pragma once


#include <Standard.hpp>

#include <Quantity_ColorRGBA.hpp>
#include <TDF_Attribute.hpp>
#include <Quantity_NameOfColor.hpp>
class Standard_GUID;
class TDF_Label;
class Quantity_Color;
class TDF_RelocationTable;

//! attribute to store color
class XCAFDoc_Color : public TDF_Attribute
{

public:
  Standard_EXPORT XCAFDoc_Color();

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_Color> Set(const TDF_Label&      label,
                                                        const Quantity_Color& C);

  Standard_EXPORT static occ::handle<XCAFDoc_Color> Set(const TDF_Label&          label,
                                                        const Quantity_ColorRGBA& C);

  Standard_EXPORT static occ::handle<XCAFDoc_Color> Set(const TDF_Label&           label,
                                                        const Quantity_NameOfColor C);

  //! Find, or create, a Color attribute and set it's value
  //! the Color attribute is returned.
  Standard_EXPORT static occ::handle<XCAFDoc_Color> Set(const TDF_Label& label,
                                                        const double     R,
                                                        const double     G,
                                                        const double     B,
                                                        const double     alpha = 1.0);

  Standard_EXPORT void Set(const Quantity_Color& C);

  Standard_EXPORT void Set(const Quantity_ColorRGBA& C);

  Standard_EXPORT void Set(const Quantity_NameOfColor C);

  Standard_EXPORT void Set(const double R,
                           const double G,
                           const double B,
                           const double alpha = 1.0);

  Standard_EXPORT const Quantity_Color& GetColor() const;

  Standard_EXPORT const Quantity_ColorRGBA& GetColorRGBA() const;

  Standard_EXPORT Quantity_NameOfColor GetNOC() const;

  Standard_EXPORT void GetRGB(double& R, double& G, double& B) const;

  Standard_EXPORT float GetAlpha() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(XCAFDoc_Color, TDF_Attribute)

private:
  Quantity_ColorRGBA myColor;
};

