#pragma once

#include <Message_ProgressRange.hpp>
#include <OSD_OpenFile.hpp>
#include <RWMesh_CoordinateSystemConverter.hpp>
#include <RWMesh_NodeAttributes.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TDF_Label.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>

class TDocStd_Document;
class XCAFDoc_ShapeTool;
class XCAFDoc_ColorTool;
class XCAFDoc_VisMaterialTool;

enum RWMesh_CafReaderStatusEx
{
  RWMesh_CafReaderStatusEx_NONE    = 0,
  RWMesh_CafReaderStatusEx_Partial = 0x01,
};

class RWMesh_CafReader : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(RWMesh_CafReader, Standard_Transient)
public:
  struct CafDocumentTools
  {
    occ::handle<XCAFDoc_ShapeTool>                                        ShapeTool;
    occ::handle<XCAFDoc_ColorTool>                                        ColorTool;
    occ::handle<XCAFDoc_VisMaterialTool>                                  VisMaterialTool;
    NCollection_DataMap<TopoDS_Shape, TDF_Label, TopTools_ShapeMapHasher> ComponentMap;
    NCollection_DataMap<TopoDS_Shape, TDF_Label, TopTools_ShapeMapHasher> OriginalShapeMap;
  };

public:
  Standard_EXPORT RWMesh_CafReader();

  Standard_EXPORT ~RWMesh_CafReader() override;

  const occ::handle<TDocStd_Document>& Document() const { return myXdeDoc; }

  Standard_EXPORT void SetDocument(const occ::handle<TDocStd_Document>& theDoc);

  const TCollection_AsciiString& RootPrefix() const { return myRootPrefix; }

  void SetRootPrefix(const TCollection_AsciiString& theRootPrefix) { myRootPrefix = theRootPrefix; }

  bool ToFillIncompleteDocument() const { return myToFillIncomplete; }

  void SetFillIncompleteDocument(bool theToFillIncomplete)
  {
    myToFillIncomplete = theToFillIncomplete;
  }

  int MemoryLimitMiB() const { return myMemoryLimitMiB; }

  void SetMemoryLimitMiB(int theLimitMiB) { myMemoryLimitMiB = theLimitMiB; }

public:
  const RWMesh_CoordinateSystemConverter& CoordinateSystemConverter() const
  {
    return myCoordSysConverter;
  }

  void SetCoordinateSystemConverter(const RWMesh_CoordinateSystemConverter& theConverter)
  {
    myCoordSysConverter = theConverter;
  }

  double SystemLengthUnit() const { return myCoordSysConverter.OutputLengthUnit(); }

  void SetSystemLengthUnit(double theUnits) { myCoordSysConverter.SetOutputLengthUnit(theUnits); }

  bool HasSystemCoordinateSystem() const { return myCoordSysConverter.HasOutputCoordinateSystem(); }

  const gp_Ax3& SystemCoordinateSystem() const
  {
    return myCoordSysConverter.OutputCoordinateSystem();
  }

  void SetSystemCoordinateSystem(const gp_Ax3& theCS)
  {
    myCoordSysConverter.SetOutputCoordinateSystem(theCS);
  }

  void SetSystemCoordinateSystem(RWMesh_CoordinateSystem theCS)
  {
    myCoordSysConverter.SetOutputCoordinateSystem(theCS);
  }

  double FileLengthUnit() const { return myCoordSysConverter.InputLengthUnit(); }

  void SetFileLengthUnit(double theUnits) { myCoordSysConverter.SetInputLengthUnit(theUnits); }

  bool HasFileCoordinateSystem() const { return myCoordSysConverter.HasInputCoordinateSystem(); }

  const gp_Ax3& FileCoordinateSystem() const { return myCoordSysConverter.InputCoordinateSystem(); }

  void SetFileCoordinateSystem(const gp_Ax3& theCS)
  {
    myCoordSysConverter.SetInputCoordinateSystem(theCS);
  }

  void SetFileCoordinateSystem(RWMesh_CoordinateSystem theCS)
  {
    myCoordSysConverter.SetInputCoordinateSystem(theCS);
  }

public:
  bool Perform(const TCollection_AsciiString& theFile, const Message_ProgressRange& theProgress)
  {
    std::ifstream aStream;
    OSD_OpenStream(aStream, theFile, std::ios_base::in | std::ios_base::binary);
    return Perform(aStream, theProgress, theFile);
  }

  bool Perform(std::istream&                  theStream,
               const Message_ProgressRange&   theProgress,
               const TCollection_AsciiString& theFile = "")
  {
    return perform(theStream, theFile, theProgress, false);
  }

  int ExtraStatus() const { return myExtraStatus; }

public:
  Standard_EXPORT TopoDS_Shape SingleShape() const;

  const NCollection_IndexedMap<TCollection_AsciiString>& ExternalFiles() const
  {
    return myExternalFiles;
  }

  const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& Metadata()
    const
  {
    return myMetadata;
  }

  bool ProbeHeader(const TCollection_AsciiString& theFile,
                   const Message_ProgressRange&   theProgress = Message_ProgressRange())
  {
    std::ifstream aStream;
    OSD_OpenStream(aStream, theFile, std::ios_base::in | std::ios_base::binary);
    return ProbeHeader(aStream, theFile, theProgress);
  }

  bool ProbeHeader(std::istream&                  theStream,
                   const TCollection_AsciiString& theFile     = "",
                   const Message_ProgressRange&   theProgress = Message_ProgressRange())
  {
    return perform(theStream, theFile, theProgress, true);
  }

protected:
  Standard_EXPORT virtual bool perform(const TCollection_AsciiString& theFile,
                                       const Message_ProgressRange&   theProgress,
                                       const bool                     theToProbe);

  Standard_EXPORT virtual bool perform(std::istream&                  theStream,
                                       const TCollection_AsciiString& theFile,
                                       const Message_ProgressRange&   theProgress,
                                       const bool                     theToProbe);

  Standard_EXPORT virtual bool performMesh(const TCollection_AsciiString& theFile,
                                           const Message_ProgressRange&   theProgress,
                                           const bool                     theToProbe)
  {
    std::ifstream aStream;
    OSD_OpenStream(aStream, theFile, std::ios_base::in | std::ios_base::binary);
    return performMesh(aStream, theFile, theProgress, theToProbe);
  }

  Standard_EXPORT virtual bool performMesh(std::istream&                  theStream,
                                           const TCollection_AsciiString& theFile,
                                           const Message_ProgressRange&   theProgress,
                                           const bool                     theToProbe) = 0;

protected:
  Standard_EXPORT virtual void fillDocument();

  Standard_EXPORT bool addShapeIntoDoc(CafDocumentTools&              theTools,
                                       const TopoDS_Shape&            theShape,
                                       const TDF_Label&               theLabel,
                                       const TCollection_AsciiString& theParentName);

  Standard_EXPORT bool addSubShapeIntoDoc(CafDocumentTools&   theTools,
                                          const TopoDS_Shape& theShape,
                                          const TDF_Label&    theParentLabel);

  Standard_EXPORT void setShapeName(const TDF_Label&               theLabel,
                                    const TopAbs_ShapeEnum         theShapeType,
                                    const TCollection_AsciiString& theName,
                                    const TDF_Label&               theParentLabel,
                                    const TCollection_AsciiString& theParentName);

  Standard_EXPORT void setShapeStyle(const CafDocumentTools& theTools,
                                     const TDF_Label&        theLabel,
                                     const XCAFPrs_Style&    theStyle);

  Standard_EXPORT void setShapeNamedData(const CafDocumentTools&                theTools,
                                         const TDF_Label&                       theLabel,
                                         const occ::handle<TDataStd_NamedData>& theNameData);

  Standard_EXPORT void generateNames(const TCollection_AsciiString& theFile,
                                     const int                      theRootLower,
                                     const bool                     theWithSubLabels);

  static TCollection_AsciiString shapeTypeToString(TopAbs_ShapeEnum theType)
  {
    TCollection_AsciiString aString = TopAbs::ShapeTypeToString(theType);
    aString.Capitalize();
    return aString;
  }

protected:
  occ::handle<TDocStd_Document> myXdeDoc;

  NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString> myMetadata;
  NCollection_IndexedMap<TCollection_AsciiString>

                                                                                    myExternalFiles;
  TCollection_AsciiString                                                           myRootPrefix;
  NCollection_Sequence<TopoDS_Shape>                                                myRootShapes;
  NCollection_DataMap<TopoDS_Shape, RWMesh_NodeAttributes, TopTools_ShapeMapHasher> myAttribMap;

  RWMesh_CoordinateSystemConverter myCoordSysConverter;
  bool                             myToFillDoc;
  bool                             myToFillIncomplete;

  int myMemoryLimitMiB;
  int myExtraStatus;
};
