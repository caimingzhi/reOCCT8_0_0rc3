#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
#include <Standard_Boolean.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>

class TDF_Label;
class Standard_GUID;

class XCAFDoc_ViewTool : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT XCAFDoc_ViewTool();

  Standard_EXPORT static occ::handle<XCAFDoc_ViewTool> Set(const TDF_Label& L);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDF_Label BaseLabel() const;

  Standard_EXPORT bool IsView(const TDF_Label& theLabel) const;

  Standard_EXPORT void GetViewLabels(NCollection_Sequence<TDF_Label>& theLabels) const;

  Standard_EXPORT void SetView(const NCollection_Sequence<TDF_Label>& theShapes,
                               const NCollection_Sequence<TDF_Label>& theGDTs,
                               const NCollection_Sequence<TDF_Label>& theClippingPlanes,
                               const NCollection_Sequence<TDF_Label>& theNotes,
                               const NCollection_Sequence<TDF_Label>& theAnnotations,
                               const TDF_Label&                       theViewL) const;

  Standard_EXPORT void SetView(const NCollection_Sequence<TDF_Label>& theShapes,
                               const NCollection_Sequence<TDF_Label>& theGDTs,
                               const NCollection_Sequence<TDF_Label>& theClippingPlanes,
                               const TDF_Label&                       theViewL) const;

  Standard_EXPORT void SetView(const NCollection_Sequence<TDF_Label>& theShapes,
                               const NCollection_Sequence<TDF_Label>& theGDTs,
                               const TDF_Label&                       theViewL) const;

  Standard_EXPORT void SetClippingPlanes(
    const NCollection_Sequence<TDF_Label>& theClippingPlaneLabels,
    const TDF_Label&                       theViewL) const;

  Standard_EXPORT void RemoveView(const TDF_Label& theViewL);

  Standard_EXPORT bool GetViewLabelsForShape(const TDF_Label&                 theShapeL,
                                             NCollection_Sequence<TDF_Label>& theViews) const;

  Standard_EXPORT bool GetViewLabelsForGDT(const TDF_Label&                 theGDTL,
                                           NCollection_Sequence<TDF_Label>& theViews) const;

  Standard_EXPORT bool GetViewLabelsForClippingPlane(
    const TDF_Label&                 theClippingPlaneL,
    NCollection_Sequence<TDF_Label>& theViews) const;

  Standard_EXPORT bool GetViewLabelsForNote(const TDF_Label&                 theNoteL,
                                            NCollection_Sequence<TDF_Label>& theViews) const;

  Standard_EXPORT bool GetViewLabelsForAnnotation(const TDF_Label&                 theAnnotationL,
                                                  NCollection_Sequence<TDF_Label>& theViews) const;

  Standard_EXPORT TDF_Label AddView();

  Standard_EXPORT bool GetRefShapeLabel(const TDF_Label&                 theViewL,
                                        NCollection_Sequence<TDF_Label>& theShapeLabels) const;

  Standard_EXPORT bool GetRefGDTLabel(const TDF_Label&                 theViewL,
                                      NCollection_Sequence<TDF_Label>& theGDTLabels) const;

  Standard_EXPORT bool GetRefClippingPlaneLabel(
    const TDF_Label&                 theViewL,
    NCollection_Sequence<TDF_Label>& theClippingPlaneLabels) const;

  Standard_EXPORT bool GetRefNoteLabel(const TDF_Label&                 theViewL,
                                       NCollection_Sequence<TDF_Label>& theNoteLabels) const;

  Standard_EXPORT bool GetRefAnnotationLabel(
    const TDF_Label&                 theViewL,
    NCollection_Sequence<TDF_Label>& theAnnotationLabels) const;

  Standard_EXPORT bool IsLocked(const TDF_Label& theViewL) const;

  Standard_EXPORT void Lock(const TDF_Label& theViewL) const;

  Standard_EXPORT void Unlock(const TDF_Label& theViewL) const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_ViewTool, TDataStd_GenericEmpty)
};
