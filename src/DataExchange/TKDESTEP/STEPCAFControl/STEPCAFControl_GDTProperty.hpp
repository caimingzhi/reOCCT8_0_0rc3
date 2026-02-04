#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <STEPConstruct_Tool.hpp>
#include <Standard_CString.hpp>
#include <StepDimTol_GeometricTolerance.hpp>
#include <StepDimTol_GeometricToleranceModifier.hpp>
#include <StepDimTol_GeometricToleranceType.hpp>
#include <StepDimTol_DatumReferenceModifier.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_CompoundRepresentationItem.hpp>
#include <StepVisual_TessellatedGeometricSet.hpp>
#include <NCollection_Sequence.hpp>
#include <XCAFDimTolObjects_DimensionModif.hpp>
#include <StepShape_LimitsAndFits.hpp>
#include <XCAFDimTolObjects_DatumSingleModif.hpp>
#include <XCAFDimTolObjects_DatumModifWithValue.hpp>
#include <XCAFDimTolObjects_DimensionFormVariance.hpp>
#include <XCAFDimTolObjects_DimensionGrade.hpp>
#include <XCAFDimTolObjects_DimensionType.hpp>
#include <XCAFDimTolObjects_DatumTargetType.hpp>
#include <XCAFDimTolObjects_DimensionQualifier.hpp>
#include <XCAFDimTolObjects_GeomToleranceModif.hpp>
#include <XCAFDimTolObjects_GeomToleranceType.hpp>
#include <XCAFDimTolObjects_GeomToleranceTypeValue.hpp>

//! This class provides tools for access (read)
//! the GDT properties.
class STEPCAFControl_GDTProperty
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT             STEPCAFControl_GDTProperty();
  Standard_EXPORT static void GetDimModifiers(
    const occ::handle<StepRepr_CompoundRepresentationItem>& theCRI,
    NCollection_Sequence<XCAFDimTolObjects_DimensionModif>& theModifiers);

  Standard_EXPORT static void GetDimClassOfTolerance(
    const occ::handle<StepShape_LimitsAndFits>& theLAF,
    bool&                                       theHolle,
    XCAFDimTolObjects_DimensionFormVariance&    theFV,
    XCAFDimTolObjects_DimensionGrade&           theG);

  Standard_EXPORT static bool GetDimType(const occ::handle<TCollection_HAsciiString>& theName,
                                         XCAFDimTolObjects_DimensionType&             theType);

  Standard_EXPORT static bool GetDatumTargetType(
    const occ::handle<TCollection_HAsciiString>& theDescription,
    XCAFDimTolObjects_DatumTargetType&           theType);

  Standard_EXPORT static bool GetDimQualifierType(
    const occ::handle<TCollection_HAsciiString>& theDescription,
    XCAFDimTolObjects_DimensionQualifier&        theType);

  Standard_EXPORT static bool GetTolValueType(
    const occ::handle<TCollection_HAsciiString>& theDescription,
    XCAFDimTolObjects_GeomToleranceTypeValue&    theType);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> GetTolValueType(
    const XCAFDimTolObjects_GeomToleranceTypeValue& theType);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> GetDimTypeName(
    const XCAFDimTolObjects_DimensionType theType);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> GetDimQualifierName(
    const XCAFDimTolObjects_DimensionQualifier theQualifier);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> GetDimModifierName(
    const XCAFDimTolObjects_DimensionModif theModifier);

  Standard_EXPORT static occ::handle<StepShape_LimitsAndFits> GetLimitsAndFits(
    bool                                    theHole,
    XCAFDimTolObjects_DimensionFormVariance theFormVariance,
    XCAFDimTolObjects_DimensionGrade        theGrade);

  Standard_EXPORT static occ::handle<TCollection_HAsciiString> GetDatumTargetName(
    const XCAFDimTolObjects_DatumTargetType theDatumType);

  Standard_EXPORT static StepDimTol_GeometricToleranceType GetGeomToleranceType(
    const XCAFDimTolObjects_GeomToleranceType theType);

  Standard_EXPORT static XCAFDimTolObjects_GeomToleranceType GetGeomToleranceType(
    const StepDimTol_GeometricToleranceType theType);

  Standard_EXPORT static occ::handle<StepDimTol_GeometricTolerance> GetGeomTolerance(
    const XCAFDimTolObjects_GeomToleranceType theType);

  Standard_EXPORT static StepDimTol_GeometricToleranceModifier GetGeomToleranceModifier(
    const XCAFDimTolObjects_GeomToleranceModif theModifier);

  Standard_EXPORT static occ::handle<NCollection_HArray1<StepDimTol_DatumReferenceModifier>>
    GetDatumRefModifiers(
      const NCollection_Sequence<XCAFDimTolObjects_DatumSingleModif>& theModifiers,
      const XCAFDimTolObjects_DatumModifWithValue&                    theModifWithVal,
      const double                                                    theValue,
      const StepBasic_Unit&                                           theUnit);

  Standard_EXPORT static occ::handle<StepVisual_TessellatedGeometricSet> GetTessellation(
    const TopoDS_Shape& theShape);
};

