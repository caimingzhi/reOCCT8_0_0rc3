#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_GenericEmpty.hpp>
#include <Standard_Boolean.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_IndexedDataMap.hpp>

class XCAFDoc_ShapeTool;
class TDF_Label;
class Standard_GUID;
class TCollection_HAsciiString;

class XCAFDoc_DimTolTool : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT XCAFDoc_DimTolTool();

  Standard_EXPORT static occ::handle<XCAFDoc_DimTolTool> Set(const TDF_Label& L);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDF_Label BaseLabel() const;

  Standard_EXPORT const occ::handle<XCAFDoc_ShapeTool>& ShapeTool();

  Standard_EXPORT bool IsDimension(const TDF_Label& theLab) const;

  Standard_EXPORT void GetDimensionLabels(NCollection_Sequence<TDF_Label>& theLabels) const;

  Standard_EXPORT void SetDimension(const NCollection_Sequence<TDF_Label>& theFirstLS,
                                    const NCollection_Sequence<TDF_Label>& theSecondLS,
                                    const TDF_Label&                       theDimL) const;

  Standard_EXPORT void SetDimension(const TDF_Label& theFirstL,
                                    const TDF_Label& theSecondL,
                                    const TDF_Label& theDimL) const;

  Standard_EXPORT void SetDimension(const TDF_Label& theL, const TDF_Label& theDimL) const;

  Standard_EXPORT bool GetRefDimensionLabels(const TDF_Label&                 theShapeL,
                                             NCollection_Sequence<TDF_Label>& theDimensions) const;

  Standard_EXPORT TDF_Label AddDimension();

  Standard_EXPORT bool IsGeomTolerance(const TDF_Label& theLab) const;

  Standard_EXPORT void GetGeomToleranceLabels(NCollection_Sequence<TDF_Label>& theLabels) const;

  Standard_EXPORT void SetGeomTolerance(const TDF_Label& theL, const TDF_Label& theGeomTolL) const;

  Standard_EXPORT void SetGeomTolerance(const NCollection_Sequence<TDF_Label>& theL,
                                        const TDF_Label&                       theGeomTolL) const;

  Standard_EXPORT bool GetRefGeomToleranceLabels(const TDF_Label&                 theShapeL,
                                                 NCollection_Sequence<TDF_Label>& theDimTols) const;

  Standard_EXPORT TDF_Label AddGeomTolerance();

  Standard_EXPORT bool IsDimTol(const TDF_Label& theLab) const;

  Standard_EXPORT void GetDimTolLabels(NCollection_Sequence<TDF_Label>& Labels) const;

  Standard_EXPORT bool FindDimTol(const int                                       theKind,
                                  const occ::handle<NCollection_HArray1<double>>& theVal,
                                  const occ::handle<TCollection_HAsciiString>&    theName,
                                  const occ::handle<TCollection_HAsciiString>&    theDescription,
                                  TDF_Label&                                      lab) const;

  Standard_EXPORT TDF_Label
    FindDimTol(const int                                       theKind,
               const occ::handle<NCollection_HArray1<double>>& theVal,
               const occ::handle<TCollection_HAsciiString>&    theName,
               const occ::handle<TCollection_HAsciiString>&    theDescription) const;

  Standard_EXPORT TDF_Label
    AddDimTol(const int                                       theKind,
              const occ::handle<NCollection_HArray1<double>>& theVal,
              const occ::handle<TCollection_HAsciiString>&    theName,
              const occ::handle<TCollection_HAsciiString>&    theDescription) const;

  Standard_EXPORT void SetDimTol(const TDF_Label& theL, const TDF_Label& theDimTolL) const;

  Standard_EXPORT TDF_Label
    SetDimTol(const TDF_Label&                                theL,
              const int                                       theKind,
              const occ::handle<NCollection_HArray1<double>>& theVal,
              const occ::handle<TCollection_HAsciiString>&    theName,
              const occ::handle<TCollection_HAsciiString>&    theDescription) const;

  Standard_EXPORT static bool GetRefShapeLabel(const TDF_Label&                 theL,
                                               NCollection_Sequence<TDF_Label>& theShapeLFirst,
                                               NCollection_Sequence<TDF_Label>& theShapeLSecond);

  Standard_EXPORT bool GetDimTol(const TDF_Label&                          theDimTolL,
                                 int&                                      theKind,
                                 occ::handle<NCollection_HArray1<double>>& theVal,
                                 occ::handle<TCollection_HAsciiString>&    theName,
                                 occ::handle<TCollection_HAsciiString>&    theDescription) const;

  Standard_EXPORT bool IsDatum(const TDF_Label& lab) const;

  Standard_EXPORT void GetDatumLabels(NCollection_Sequence<TDF_Label>& Labels) const;

  Standard_EXPORT bool FindDatum(const occ::handle<TCollection_HAsciiString>& theName,
                                 const occ::handle<TCollection_HAsciiString>& theDescription,
                                 const occ::handle<TCollection_HAsciiString>& theIdentification,
                                 TDF_Label&                                   lab) const;

  Standard_EXPORT TDF_Label
    AddDatum(const occ::handle<TCollection_HAsciiString>& theName,
             const occ::handle<TCollection_HAsciiString>& theDescription,
             const occ::handle<TCollection_HAsciiString>& theIdentification) const;

  Standard_EXPORT TDF_Label AddDatum();

  Standard_EXPORT void SetDatum(const NCollection_Sequence<TDF_Label>& theShapeLabels,
                                const TDF_Label&                       theDatumL) const;

  Standard_EXPORT void SetDatum(
    const TDF_Label&                             theL,
    const TDF_Label&                             theTolerL,
    const occ::handle<TCollection_HAsciiString>& theName,
    const occ::handle<TCollection_HAsciiString>& theDescription,
    const occ::handle<TCollection_HAsciiString>& theIdentification) const;

  Standard_EXPORT void SetDatumToGeomTol(const TDF_Label& theDatumL,
                                         const TDF_Label& theTolerL) const;

  Standard_EXPORT bool GetDatum(const TDF_Label&                       theDatumL,
                                occ::handle<TCollection_HAsciiString>& theName,
                                occ::handle<TCollection_HAsciiString>& theDescription,
                                occ::handle<TCollection_HAsciiString>& theIdentification) const;

  Standard_EXPORT static bool GetDatumOfTolerLabels(const TDF_Label&                 theDimTolL,
                                                    NCollection_Sequence<TDF_Label>& theDatums);

  Standard_EXPORT static bool GetDatumWithObjectOfTolerLabels(
    const TDF_Label&                 theDimTolL,
    NCollection_Sequence<TDF_Label>& theDatums);

  Standard_EXPORT bool GetTolerOfDatumLabels(const TDF_Label&                 theDatumL,
                                             NCollection_Sequence<TDF_Label>& theTols) const;

  Standard_EXPORT bool GetRefDatumLabel(const TDF_Label&                 theShapeL,
                                        NCollection_Sequence<TDF_Label>& theDatum) const;

  Standard_EXPORT bool IsLocked(const TDF_Label& theViewL) const;

  Standard_EXPORT void Lock(const TDF_Label& theViewL) const;

  Standard_EXPORT void GetGDTPresentations(
    NCollection_IndexedDataMap<TDF_Label, TopoDS_Shape>& theGDTLabelToShape) const;

  Standard_EXPORT void SetGDTPresentations(
    NCollection_IndexedDataMap<TDF_Label, TopoDS_Shape>& theGDTLabelToPrs);

  Standard_EXPORT void Unlock(const TDF_Label& theViewL) const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_DimTolTool, TDataStd_GenericEmpty)

private:
  occ::handle<XCAFDoc_ShapeTool> myShapeTool;
};
