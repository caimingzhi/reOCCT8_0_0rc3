#pragma once

#include <STEPControl_Reader.hpp>
#include <StepData_Factors.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <StepBasic_ProductDefinition.hpp>
#include <NCollection_DataMap.hpp>
#include <STEPCAFControl_ExternFile.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_HSequence.hpp>
#include <XCAFDimTolObjects_DatumSingleModif.hpp>
#include <XCAFDimTolObjects_DatumModifWithValue.hpp>

class XSControl_WorkSession;
class TDataStd_NamedData;
class TDocStd_Document;
class STEPCAFControl_ExternFile;
class TopoDS_Shape;
class XCAFDoc_ShapeTool;
class StepRepr_RepresentationItem;
class Transfer_TransientProcess;
class StepBasic_NamedUnit;
class StepBasic_Product;
class StepShape_ConnectedFaceSet;
class StepShape_ShapeDefinitionRepresentation;
class StepRepr_NextAssemblyUsageOccurrence;
class StepRepr_PropertyDefinition;
class STEPConstruct_Tool;
class StepDimTol_Datum;
class Transfer_Binder;

class STEPCAFControl_Reader
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT STEPCAFControl_Reader();

  Standard_EXPORT STEPCAFControl_Reader(const occ::handle<XSControl_WorkSession>& WS,
                                        const bool                                scratch = true);

  Standard_EXPORT virtual ~STEPCAFControl_Reader();

  Standard_EXPORT void Init(const occ::handle<XSControl_WorkSession>& WS,
                            const bool                                scratch = true);

  Standard_EXPORT IFSelect_ReturnStatus ReadFile(const char* theFileName);

  Standard_EXPORT IFSelect_ReturnStatus ReadFile(const char*              theFileName,
                                                 const DESTEP_Parameters& theParams);

  Standard_EXPORT IFSelect_ReturnStatus ReadStream(const char* theName, std::istream& theIStream);

  Standard_EXPORT int NbRootsForTransfer();

  Standard_EXPORT bool TransferOneRoot(
    const int                            num,
    const occ::handle<TDocStd_Document>& doc,
    const Message_ProgressRange&         theProgress = Message_ProgressRange());

  Standard_EXPORT bool Transfer(const occ::handle<TDocStd_Document>& doc,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Perform(const TCollection_AsciiString&       filename,
                               const occ::handle<TDocStd_Document>& doc,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Perform(const TCollection_AsciiString&       filename,
                               const occ::handle<TDocStd_Document>& doc,
                               const DESTEP_Parameters&             theParams,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Perform(const char*                          filename,
                               const occ::handle<TDocStd_Document>& doc,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool Perform(const char*                          filename,
                               const occ::handle<TDocStd_Document>& doc,
                               const DESTEP_Parameters&             theParams,
                               const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT const NCollection_DataMap<TCollection_AsciiString,
                                            occ::handle<STEPCAFControl_ExternFile>>&
                        ExternFiles() const;

  Standard_EXPORT bool ExternFile(const char*                             name,
                                  occ::handle<STEPCAFControl_ExternFile>& ef) const;

  Standard_EXPORT STEPControl_Reader& ChangeReader();

  Standard_EXPORT const STEPControl_Reader& Reader() const;

  Standard_EXPORT static TDF_Label FindInstance(
    const occ::handle<StepRepr_NextAssemblyUsageOccurrence>&                     NAUO,
    const occ::handle<XCAFDoc_ShapeTool>&                                        STool,
    const STEPConstruct_Tool&                                                    Tool,
    const NCollection_DataMap<TopoDS_Shape, TDF_Label, TopTools_ShapeMapHasher>& ShapeLabelMap);

  Standard_EXPORT void SetColorMode(const bool colormode);

  Standard_EXPORT bool GetColorMode() const;

  Standard_EXPORT void SetNameMode(const bool namemode);

  Standard_EXPORT bool GetNameMode() const;

  Standard_EXPORT void SetLayerMode(const bool layermode);

  Standard_EXPORT bool GetLayerMode() const;

  Standard_EXPORT void SetPropsMode(const bool propsmode);

  Standard_EXPORT bool GetPropsMode() const;

  Standard_EXPORT void SetMetaMode(const bool theMetaMode);

  Standard_EXPORT bool GetMetaMode() const;

  Standard_EXPORT void SetProductMetaMode(const bool theProductMetaMode);

  Standard_EXPORT bool GetProductMetaMode() const;

  Standard_EXPORT void SetSHUOMode(const bool shuomode);

  Standard_EXPORT bool GetSHUOMode() const;

  Standard_EXPORT void SetGDTMode(const bool gdtmode);

  Standard_EXPORT bool GetGDTMode() const;

  Standard_EXPORT void SetMatMode(const bool matmode);

  Standard_EXPORT bool GetMatMode() const;

  Standard_EXPORT void SetViewMode(const bool viewmode);

  Standard_EXPORT bool GetViewMode() const;

  const NCollection_DataMap<TopoDS_Shape, TDF_Label, TopTools_ShapeMapHasher>& GetShapeLabelMap()
    const
  {
    return myMap;
  }

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
  Standard_EXPORT bool Transfer(STEPControl_Reader&                  rd,
                                const int                            num,
                                const occ::handle<TDocStd_Document>& doc,
                                NCollection_Sequence<TDF_Label>&     Lseq,
                                const bool                           asOne = false,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT TDF_Label
    AddShape(const TopoDS_Shape&                                                S,
             const occ::handle<XCAFDoc_ShapeTool>&                              STool,
             const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&      NewShapesMap,
             const NCollection_DataMap<TopoDS_Shape,
                                       occ::handle<StepBasic_ProductDefinition>,
                                       TopTools_ShapeMapHasher>&                ShapePDMap,
             const NCollection_DataMap<occ::handle<StepBasic_ProductDefinition>,
                                       occ::handle<STEPCAFControl_ExternFile>>& PDFileMap);

  Standard_EXPORT occ::handle<STEPCAFControl_ExternFile> ReadExternFile(
    const char*                          file,
    const char*                          fullpath,
    const occ::handle<TDocStd_Document>& doc,
    const Message_ProgressRange&         theProgress = Message_ProgressRange());

  Standard_EXPORT bool ReadColors(
    const occ::handle<XSControl_WorkSession>& WS,
    const occ::handle<TDocStd_Document>&      doc,
    const StepData_Factors&                   theLocalFactors = StepData_Factors()) const;

  Standard_EXPORT bool ReadNames(
    const occ::handle<XSControl_WorkSession>&                          WS,
    const occ::handle<TDocStd_Document>&                               doc,
    const NCollection_DataMap<occ::handle<StepBasic_ProductDefinition>,
                              occ::handle<STEPCAFControl_ExternFile>>& PDFileMap) const;

  Standard_EXPORT bool ReadValProps(
    const occ::handle<XSControl_WorkSession>&                          WS,
    const occ::handle<TDocStd_Document>&                               doc,
    const NCollection_DataMap<occ::handle<StepBasic_ProductDefinition>,
                              occ::handle<STEPCAFControl_ExternFile>>& PDFileMap,
    const StepData_Factors& theLocalFactors = StepData_Factors()) const;

  Standard_EXPORT bool ReadMetadata(
    const occ::handle<XSControl_WorkSession>& theWS,
    const occ::handle<TDocStd_Document>&      theDoc,
    const StepData_Factors&                   theLocalFactors = StepData_Factors()) const;

  Standard_EXPORT bool ReadProductMetadata(const occ::handle<XSControl_WorkSession>& theWS,
                                           const occ::handle<TDocStd_Document>&      theDoc) const;

  Standard_EXPORT bool ReadLayers(const occ::handle<XSControl_WorkSession>& WS,
                                  const occ::handle<TDocStd_Document>&      doc) const;

  Standard_EXPORT bool ReadSHUOs(
    const occ::handle<XSControl_WorkSession>&                          WS,
    const occ::handle<TDocStd_Document>&                               doc,
    const NCollection_DataMap<occ::handle<StepBasic_ProductDefinition>,
                              occ::handle<STEPCAFControl_ExternFile>>& PDFileMap) const;

  Standard_EXPORT bool ReadGDTs(const occ::handle<XSControl_WorkSession>& WS,
                                const occ::handle<TDocStd_Document>&      doc,
                                const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT bool ReadMaterials(
    const occ::handle<XSControl_WorkSession>&                                  WS,
    const occ::handle<TDocStd_Document>&                                       doc,
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& SeqPDS,
    const StepData_Factors& theLocalFactors = StepData_Factors()) const;

  Standard_EXPORT bool ReadViews(
    const occ::handle<XSControl_WorkSession>& theWS,
    const occ::handle<TDocStd_Document>&      theDoc,
    const StepData_Factors&                   theLocalFactors = StepData_Factors()) const;

  Standard_EXPORT TDF_Label
    SettleShapeData(const occ::handle<StepRepr_RepresentationItem>& theItem,
                    const TDF_Label&                                theLab,
                    const occ::handle<XCAFDoc_ShapeTool>&           theShapeTool,
                    const occ::handle<Transfer_TransientProcess>&   theTP) const;

  Standard_EXPORT void ExpandSubShapes(
    const occ::handle<XCAFDoc_ShapeTool>&               theShapeTool,
    const NCollection_DataMap<TopoDS_Shape,
                              occ::handle<StepBasic_ProductDefinition>,
                              TopTools_ShapeMapHasher>& theShapePDMap) const;

  Standard_EXPORT void ExpandManifoldSolidBrep(
    TDF_Label&                                      theLab,
    const occ::handle<StepRepr_RepresentationItem>& theItem,
    const occ::handle<Transfer_TransientProcess>&   theTP,
    const occ::handle<XCAFDoc_ShapeTool>&           theShapeTool) const;

  Standard_EXPORT void ExpandSBSM(TDF_Label&                                      theLab,
                                  const occ::handle<StepRepr_RepresentationItem>& theItem,
                                  const occ::handle<Transfer_TransientProcess>&   theTP,
                                  const occ::handle<XCAFDoc_ShapeTool>& theShapeTool) const;

  Standard_EXPORT void ExpandShell(const occ::handle<StepShape_ConnectedFaceSet>& theShell,
                                   TDF_Label&                                     theLab,
                                   const occ::handle<Transfer_TransientProcess>&  theTP,
                                   const occ::handle<XCAFDoc_ShapeTool>& theShapeTool) const;

  Standard_EXPORT virtual TCollection_ExtendedString convertName(
    const TCollection_AsciiString& theName) const;

private:
  bool setDatumToXCAF(
    const occ::handle<StepDimTol_Datum>&                            theDat,
    const TDF_Label                                                 theGDTL,
    const int                                                       thePositionCounter,
    const NCollection_Sequence<XCAFDimTolObjects_DatumSingleModif>& theXCAFModifiers,
    const XCAFDimTolObjects_DatumModifWithValue                     theXCAFModifWithVal,
    const double                                                    theModifValue,
    const occ::handle<TDocStd_Document>&                            theDoc,
    const occ::handle<XSControl_WorkSession>&                       theWS,
    const StepData_Factors& theLocalFactors = StepData_Factors());

  bool readDatumsAP242(const occ::handle<Standard_Transient>&    theEnt,
                       const TDF_Label                           theGDTL,
                       const occ::handle<TDocStd_Document>&      theDoc,
                       const occ::handle<XSControl_WorkSession>& theWS,
                       const StepData_Factors& theLocalFactors = StepData_Factors());

  TDF_Label createGDTObjectInXCAF(const occ::handle<Standard_Transient>&    theEnt,
                                  const occ::handle<TDocStd_Document>&      theDoc,
                                  const occ::handle<XSControl_WorkSession>& theWS,
                                  const StepData_Factors& theLocalFactors = StepData_Factors());

  void prepareUnits(const occ::handle<StepData_StepModel>& theModel,
                    const occ::handle<TDocStd_Document>&   theDoc,
                    StepData_Factors&                      theLocalFactors) const;

  bool findReprItems(const occ::handle<XSControl_WorkSession>&                   theWS,
                     const occ::handle<StepShape_ShapeDefinitionRepresentation>& theShDefRepr,
                     NCollection_List<occ::handle<Transfer_Binder>>&             theBinders) const;

  bool fillAttributes(const occ::handle<XSControl_WorkSession>&       theWS,
                      const occ::handle<StepRepr_PropertyDefinition>& thePropDef,
                      const StepData_Factors&                         theLocalFactors,
                      occ::handle<TDataStd_NamedData>&                theAttr) const;

  TDF_Label getShapeLabelFromProductDefinition(
    const occ::handle<Transfer_TransientProcess>&   theTransferProcess,
    const occ::handle<StepBasic_ProductDefinition>& theProductDefinition) const;

  occ::handle<StepBasic_Product> getProductFromProductDefinition(
    const occ::handle<StepBasic_ProductDefinition>& theProductDefinition) const;

  std::vector<occ::handle<StepRepr_PropertyDefinition>> collectPropertyDefinitions(
    const occ::handle<XSControl_WorkSession>& theWorkSession,
    const occ::handle<Standard_Transient>&    theGeneralProperty) const;

  std::vector<TDF_Label> collectShapeLabels(
    const occ::handle<XSControl_WorkSession>&       theWorkSession,
    const occ::handle<Transfer_TransientProcess>&   theTransferProcess,
    const occ::handle<StepRepr_PropertyDefinition>& theSource) const;

  std::vector<occ::handle<StepRepr_PropertyDefinition>> collectRelatedPropertyDefinitions(
    const occ::handle<XSControl_WorkSession>&       theWorkSession,
    const occ::handle<StepRepr_PropertyDefinition>& theProperty) const;

  occ::handle<TDataStd_NamedData> getNamedData(const TDF_Label& theLabel) const;

  void collectBinders(const occ::handle<XSControl_WorkSession>&       theWorkSession,
                      const occ::handle<Transfer_TransientProcess>&   theTransientProcess,
                      const occ::handle<StepRepr_PropertyDefinition>& theSource,
                      NCollection_List<occ::handle<Transfer_Binder>>& theBinders) const;

private:
  STEPControl_Reader                                                                   myReader;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<STEPCAFControl_ExternFile>> myFiles;
  NCollection_DataMap<TopoDS_Shape, TDF_Label, TopTools_ShapeMapHasher>                myMap;
  bool                                                                                 myColorMode;
  bool                                                                                 myNameMode;
  bool                                                                                 myLayerMode;
  bool                                                                                 myPropsMode;
  bool                                                                                 myMetaMode;
  bool                                                            myProductMetaMode;
  bool                                                            mySHUOMode;
  bool                                                            myGDTMode;
  bool                                                            myMatMode;
  bool                                                            myViewMode;
  NCollection_DataMap<occ::handle<Standard_Transient>, TDF_Label> myGDTMap;
};
