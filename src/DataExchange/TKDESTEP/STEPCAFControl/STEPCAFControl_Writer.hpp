#pragma once

#include <TopoDS_Shape.hpp>
#include <Standard_Transient.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Vector.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <TDF_Label.hpp>
#include <STEPCAFControl_ExternFile.hpp>
#include <STEPControl_Writer.hpp>
#include <StepAP242_GeometricItemSpecificUsage.hpp>
#include <DESTEP_Parameters.hpp>
#include <StepData_Factors.hpp>
#include <StepDimTol_Datum.hpp>
#include <StepDimTol_GeometricTolerance.hpp>
#include <StepDimTol_DatumSystemOrReference.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>
#include <StepVisual_DraughtingModel.hpp>
#include <StepVisual_PresentationStyleAssignment.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Map.hpp>
#include <XCAFDimTolObjects_GeomToleranceObject.hpp>

class XSControl_WorkSession;
class TDocStd_Document;
class STEPCAFControl_ExternFile;
class TopoDS_Shape;
class StepShape_ShapeDefinitionRepresentation;

class STEPCAFControl_Writer
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT STEPCAFControl_Writer();

  Standard_EXPORT STEPCAFControl_Writer(const occ::handle<XSControl_WorkSession>& theWS,
                                        const bool theScratch = true);

  Standard_EXPORT void Init(const occ::handle<XSControl_WorkSession>& theWS,
                            const bool                                theScratch = true);

  Standard_EXPORT IFSelect_ReturnStatus Write(const char* theFileName);

  Standard_EXPORT IFSelect_ReturnStatus WriteStream(std::ostream& theStream);

  Standard_EXPORT bool Transfer(const occ::handle<TDocStd_Document>& theDoc,
                                const STEPControl_StepModelType      theMode    = STEPControl_AsIs,
                                const char*                          theIsMulti = nullptr,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Transfer(const occ::handle<TDocStd_Document>& theDoc,
                                const DESTEP_Parameters&             theParams,
                                const STEPControl_StepModelType      theMode    = STEPControl_AsIs,
                                const char*                          theIsMulti = nullptr,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Transfer(const TDF_Label&                theLabel,
                                const STEPControl_StepModelType theMode    = STEPControl_AsIs,
                                const char*                     theIsMulti = nullptr,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Transfer(const TDF_Label&                theLabel,
                                const DESTEP_Parameters&        theParams,
                                const STEPControl_StepModelType theMode    = STEPControl_AsIs,
                                const char*                     theIsMulti = nullptr,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Transfer(const NCollection_Sequence<TDF_Label>& theLabelSeq,
                                const STEPControl_StepModelType        theMode = STEPControl_AsIs,
                                const char*                            theIsMulti = nullptr,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Transfer(const NCollection_Sequence<TDF_Label>& theLabelSeq,
                                const DESTEP_Parameters&               theParams,
                                const STEPControl_StepModelType        theMode = STEPControl_AsIs,
                                const char*                            theIsMulti = nullptr,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Perform(const occ::handle<TDocStd_Document>& theDoc,
                               const TCollection_AsciiString&       theFileName,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Perform(const occ::handle<TDocStd_Document>& theDoc,
                               const char*                          theFileName,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Perform(const occ::handle<TDocStd_Document>& theDoc,
                               const char*                          theFileName,
                               const DESTEP_Parameters&             theParams,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  const NCollection_DataMap<TCollection_AsciiString, occ::handle<STEPCAFControl_ExternFile>>&
    ExternFiles() const
  {
    return myFiles;
  };

  Standard_EXPORT bool ExternFile(const TDF_Label&                        theLabel,
                                  occ::handle<STEPCAFControl_ExternFile>& theExtFile) const;

  Standard_EXPORT bool ExternFile(const char*                             theName,
                                  occ::handle<STEPCAFControl_ExternFile>& theExtFile) const;

  STEPControl_Writer& ChangeWriter() { return myWriter; }

  const STEPControl_Writer& Writer() const { return myWriter; }

  void SetColorMode(const bool theColorMode) { myColorMode = theColorMode; }

  bool GetColorMode() const { return myColorMode; }

  void SetNameMode(const bool theNameMode) { myNameMode = theNameMode; }

  bool GetNameMode() const { return myNameMode; }

  void SetLayerMode(const bool theLayerMode) { myLayerMode = theLayerMode; }

  bool GetLayerMode() const { return myLayerMode; }

  void SetPropsMode(const bool thePropsMode) { myPropsMode = thePropsMode; }

  bool GetPropsMode() const { return myPropsMode; }

  void SetMetadataMode(const bool theMetadataMode) { myMetadataMode = theMetadataMode; }

  bool GetMetadataMode() const { return myMetadataMode; }

  void SetSHUOMode(const bool theSHUOMode) { mySHUOMode = theSHUOMode; }

  bool GetSHUOMode() const { return mySHUOMode; }

  void SetDimTolMode(const bool theDimTolMode) { myGDTMode = theDimTolMode; };

  bool GetDimTolMode() const { return myGDTMode; }

  void SetMaterialMode(const bool theMaterialMode) { myMatMode = theMaterialMode; }

  bool GetMaterialMode() const { return myMatMode; }

  void SetVisualMaterialMode(const bool theVisualMaterialMode)
  {
    myVisMatMode = theVisualMaterialMode;
  }

  bool GetVisualMaterialMode() const { return myVisMatMode; }

  void SetCleanDuplicates(const bool theCleanDuplicates)
  {
    myIsCleanDuplicates = theCleanDuplicates;
  }

  bool GetCleanDuplicates() const { return myIsCleanDuplicates; }

  Standard_EXPORT void SetShapeFixParameters(
    const XSAlgo_ShapeProcessor::ParameterMap& theParameters);

  Standard_EXPORT void SetShapeFixParameters(XSAlgo_ShapeProcessor::ParameterMap&& theParameters);

  Standard_EXPORT void SetShapeFixParameters(
    const DE_ShapeFixParameters&               theParameters,
    const XSAlgo_ShapeProcessor::ParameterMap& theAdditionalParameters = {});

  Standard_EXPORT const XSAlgo_ShapeProcessor::ParameterMap& GetShapeFixParameters() const;

  Standard_EXPORT void SetShapeProcessFlags(const ShapeProcess::OperationsFlags& theFlags);

  Standard_EXPORT const XSAlgo_ShapeProcessor::ProcessingFlags& GetShapeProcessFlags() const;

protected:
  bool transfer(STEPControl_Writer&                    theWriter,
                const NCollection_Sequence<TDF_Label>& theLabels,
                const STEPControl_StepModelType        theMode      = STEPControl_AsIs,
                const char*                            theIsMulti   = nullptr,
                const bool                             isExternFile = false,
                const Message_ProgressRange&           theProgress  = Message_ProgressRange());

  TopoDS_Shape transferExternFiles(
    const TDF_Label&                 theLabel,
    const STEPControl_StepModelType  theMode,
    NCollection_Sequence<TDF_Label>& theLabelSeq,
    const StepData_Factors&          theLocalFactors = StepData_Factors(),
    const char*                      thePrefix       = "",
    const Message_ProgressRange&     theProgress     = Message_ProgressRange());

  bool writeExternRefs(const occ::handle<XSControl_WorkSession>& theWS,
                       const NCollection_Sequence<TDF_Label>&    theLabels) const;

  bool writeColors(const occ::handle<XSControl_WorkSession>& theWS,
                   const NCollection_Sequence<TDF_Label>&    theLabels);

  bool writeNames(const occ::handle<XSControl_WorkSession>& theWS,
                  const NCollection_Sequence<TDF_Label>&    theLabels) const;

  bool writeMetadata(const occ::handle<XSControl_WorkSession>& theWS,
                     const NCollection_Sequence<TDF_Label>&    theLabels) const;

  bool writeMetadataForLabel(const occ::handle<XSControl_WorkSession>& theWS,
                             const TDF_Label&                          theLabel) const;

  void writeMetadataRepresentationItem(
    const TCollection_AsciiString&                              theKey,
    const occ::handle<StepData_StepModel>&                      theModel,
    const occ::handle<StepShape_ShapeDefinitionRepresentation>& theShapeDefRep,
    const occ::handle<StepBasic_ProductDefinition>&             theProdDef,
    const occ::handle<StepRepr_RepresentationItem>&             theItem) const;

  bool writeDGTs(const occ::handle<XSControl_WorkSession>& theWS,
                 const NCollection_Sequence<TDF_Label>&    theLabels) const;

  bool writeDGTsAP242(const occ::handle<XSControl_WorkSession>& theWS,
                      const NCollection_Sequence<TDF_Label>&    theLabels,
                      const StepData_Factors& theLocalFactors = StepData_Factors());

  bool writeMaterials(const occ::handle<XSControl_WorkSession>& theWS,
                      const NCollection_Sequence<TDF_Label>&    theLabels) const;

  bool writeValProps(const occ::handle<XSControl_WorkSession>& theWS,
                     const NCollection_Sequence<TDF_Label>&    theLabels,
                     const char*                               theIsMulti) const;

  bool writeLayers(const occ::handle<XSControl_WorkSession>& theWS,
                   const NCollection_Sequence<TDF_Label>&    theLabels) const;

  bool writeSHUOs(const occ::handle<XSControl_WorkSession>& theWS,
                  const NCollection_Sequence<TDF_Label>&    theLabels);

  void prepareUnit(const TDF_Label&                       theLabel,
                   const occ::handle<StepData_StepModel>& theModel,
                   StepData_Factors&                      theLocalFactors);

  occ::handle<StepRepr_ShapeAspect> writeShapeAspect(
    const occ::handle<XSControl_WorkSession>&          theWS,
    const TDF_Label                                    theLabel,
    const TopoDS_Shape&                                theShape,
    occ::handle<StepRepr_RepresentationContext>&       theRC,
    occ::handle<StepAP242_GeometricItemSpecificUsage>& theGISU);

  void writePresentation(const occ::handle<XSControl_WorkSession>&    theWS,
                         const TopoDS_Shape&                          thePresentation,
                         const occ::handle<TCollection_HAsciiString>& thePrsName,
                         const bool                                   theHasSemantic,
                         const bool                                   theHasPlane,
                         const gp_Ax2&                                theAnnotationPlane,
                         const gp_Pnt&                                theTextPosition,
                         const occ::handle<Standard_Transient>&       theDimension,
                         const StepData_Factors& theLocalFactors = StepData_Factors());

  occ::handle<StepDimTol_Datum> writeDatumAP242(
    const occ::handle<XSControl_WorkSession>& theWS,
    const NCollection_Sequence<TDF_Label>&    theShapeL,
    const TDF_Label&                          theDatumL,
    const bool                                isFirstDTarget,
    const occ::handle<StepDimTol_Datum>&      theWrittenDatum,
    const StepData_Factors&                   theLocalFactors = StepData_Factors());

  void writeToleranceZone(const occ::handle<XSControl_WorkSession>&                 theWS,
                          const occ::handle<XCAFDimTolObjects_GeomToleranceObject>& theObject,
                          const occ::handle<StepDimTol_GeometricTolerance>&         theEntity,
                          const occ::handle<StepRepr_RepresentationContext>&        theRC);

  void writeGeomTolerance(
    const occ::handle<XSControl_WorkSession>&                                  theWS,
    const NCollection_Sequence<TDF_Label>&                                     theShapeSeqL,
    const TDF_Label&                                                           theGeomTolL,
    const occ::handle<NCollection_HArray1<StepDimTol_DatumSystemOrReference>>& theDatumSystem,
    const occ::handle<StepRepr_RepresentationContext>&                         theRC,
    const StepData_Factors& theLocalFactors = StepData_Factors());

private:
  STEPControl_Writer                                                                   myWriter;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<STEPCAFControl_ExternFile>> myFiles;
  NCollection_Map<TDF_Label>                                                           myRootLabels;
  NCollection_DataMap<TDF_Label, TopoDS_Shape>                                         myLabels;
  NCollection_DataMap<TDF_Label, occ::handle<STEPCAFControl_ExternFile>>               myLabEF;
  NCollection_DataMap<TDF_Label, TopoDS_Shape> myPureRefLabels;
  bool                                         myColorMode;
  bool                                         myNameMode;
  bool                                         myLayerMode;
  bool                                         myPropsMode;
  bool                                         myMetadataMode;
  bool                                         mySHUOMode;
  NCollection_DataMap<TopoDS_Shape, occ::handle<Standard_Transient>, TopTools_ShapeMapHasher>
                                                               myMapCompMDGPR;
  bool                                                         myGDTMode;
  bool                                                         myMatMode;
  bool                                                         myVisMatMode;
  bool                                                         myIsCleanDuplicates;
  NCollection_Vector<occ::handle<StepRepr_RepresentationItem>> myGDTAnnotations;
  occ::handle<StepVisual_DraughtingModel>                      myGDTPresentationDM;
  occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>>
                                               myGDTPrsCurveStyle;
  occ::handle<StepRepr_ProductDefinitionShape> myGDTCommonPDS;
};
