#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
#include <Standard_Boolean.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Real.hpp>
class XCAFDoc_ShapeTool;
class TDF_Label;
class Standard_GUID;
class TCollection_HAsciiString;

class XCAFDoc_MaterialTool : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT XCAFDoc_MaterialTool();

  Standard_EXPORT static occ::handle<XCAFDoc_MaterialTool> Set(const TDF_Label& L);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDF_Label BaseLabel() const;

  Standard_EXPORT const occ::handle<XCAFDoc_ShapeTool>& ShapeTool();

  Standard_EXPORT bool IsMaterial(const TDF_Label& lab) const;

  Standard_EXPORT void GetMaterialLabels(NCollection_Sequence<TDF_Label>& Labels) const;

  Standard_EXPORT TDF_Label
    AddMaterial(const occ::handle<TCollection_HAsciiString>& aName,
                const occ::handle<TCollection_HAsciiString>& aDescription,
                const double                                 aDensity,
                const occ::handle<TCollection_HAsciiString>& aDensName,
                const occ::handle<TCollection_HAsciiString>& aDensValType) const;

  Standard_EXPORT void SetMaterial(const TDF_Label& L, const TDF_Label& MatL) const;

  Standard_EXPORT void SetMaterial(const TDF_Label&                             L,
                                   const occ::handle<TCollection_HAsciiString>& aName,
                                   const occ::handle<TCollection_HAsciiString>& aDescription,
                                   const double                                 aDensity,
                                   const occ::handle<TCollection_HAsciiString>& aDensName,
                                   const occ::handle<TCollection_HAsciiString>& aDensValType) const;

  Standard_EXPORT static bool GetMaterial(const TDF_Label&                       MatL,
                                          occ::handle<TCollection_HAsciiString>& aName,
                                          occ::handle<TCollection_HAsciiString>& aDescription,
                                          double&                                aDensity,
                                          occ::handle<TCollection_HAsciiString>& aDensName,
                                          occ::handle<TCollection_HAsciiString>& aDensValType);

  Standard_EXPORT static double GetDensityForShape(const TDF_Label& ShapeL);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_MaterialTool, TDataStd_GenericEmpty)

private:
  occ::handle<XCAFDoc_ShapeTool> myShapeTool;
};
