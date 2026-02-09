#pragma once

#include <gp_Pln.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <TDataStd_GenericEmpty.hpp>

class XCAFDoc_ClippingPlaneTool : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT XCAFDoc_ClippingPlaneTool();

  Standard_EXPORT static occ::handle<XCAFDoc_ClippingPlaneTool> Set(const TDF_Label& theLabel);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDF_Label BaseLabel() const;

  Standard_EXPORT bool IsClippingPlane(const TDF_Label& theLabel) const;

  Standard_EXPORT bool GetClippingPlane(const TDF_Label&            theLabel,
                                        gp_Pln&                     thePlane,
                                        TCollection_ExtendedString& theName,
                                        bool&                       theCapping) const;

  Standard_EXPORT bool GetClippingPlane(const TDF_Label&                       theLabel,
                                        gp_Pln&                                thePlane,
                                        occ::handle<TCollection_HAsciiString>& theName,
                                        bool&                                  theCapping) const;

  Standard_EXPORT TDF_Label AddClippingPlane(const gp_Pln&                     thePlane,
                                             const TCollection_ExtendedString& theName,
                                             const bool                        theCapping) const;

  Standard_EXPORT TDF_Label AddClippingPlane(const gp_Pln&                                thePlane,
                                             const occ::handle<TCollection_HAsciiString>& theName,
                                             const bool theCapping) const;

  Standard_EXPORT TDF_Label AddClippingPlane(const gp_Pln&                     thePlane,
                                             const TCollection_ExtendedString& theName) const;

  Standard_EXPORT TDF_Label
    AddClippingPlane(const gp_Pln&                                thePlane,
                     const occ::handle<TCollection_HAsciiString>& theName) const;

  Standard_EXPORT bool RemoveClippingPlane(const TDF_Label& theLabel) const;

  Standard_EXPORT void GetClippingPlanes(NCollection_Sequence<TDF_Label>& Labels) const;

  Standard_EXPORT void UpdateClippingPlane(const TDF_Label&                  theLabelL,
                                           const gp_Pln&                     thePlane,
                                           const TCollection_ExtendedString& theName) const;

  Standard_EXPORT void SetCapping(const TDF_Label& theClippingPlaneL, const bool theCapping);

  Standard_EXPORT bool GetCapping(const TDF_Label& theClippingPlaneL) const;

  Standard_EXPORT bool GetCapping(const TDF_Label& theClippingPlaneL, bool& theCapping) const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_ClippingPlaneTool, TDataStd_GenericEmpty)
};
