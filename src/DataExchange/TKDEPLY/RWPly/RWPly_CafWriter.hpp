#pragma once

#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Map.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <RWMesh_CoordinateSystemConverter.hpp>
#include <XCAFPrs_Style.hpp>

#include <memory>

class Message_ProgressRange;
class RWMesh_FaceIterator;
class TDocStd_Document;

class Message_LazyProgressScope;
class RWPly_PlyWriterContext;

class RWPly_CafWriter : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(RWPly_CafWriter, Standard_Transient)
public:
  Standard_EXPORT RWPly_CafWriter(const TCollection_AsciiString& theFile);

  Standard_EXPORT ~RWPly_CafWriter() override;

  const RWMesh_CoordinateSystemConverter& CoordinateSystemConverter() const { return myCSTrsf; }

  RWMesh_CoordinateSystemConverter& ChangeCoordinateSystemConverter() { return myCSTrsf; }

  void SetCoordinateSystemConverter(const RWMesh_CoordinateSystemConverter& theConverter)
  {
    myCSTrsf = theConverter;
  }

  const XCAFPrs_Style& DefaultStyle() const { return myDefaultStyle; }

  void SetDefaultStyle(const XCAFPrs_Style& theStyle) { myDefaultStyle = theStyle; }

public:
  bool IsDoublePrecision() const { return myIsDoublePrec; }

  void SetDoublePrecision(bool theDoublePrec) { myIsDoublePrec = theDoublePrec; }

  bool HasNormals() const { return myHasNormals; }

  void SetNormals(const bool theHasNormals) { myHasNormals = theHasNormals; }

  bool HasTexCoords() const { return myHasTexCoords; }

  void SetTexCoords(const bool theHasTexCoords) { myHasTexCoords = theHasTexCoords; }

  bool HasColors() const { return myHasColors; }

  void SetColors(bool theToWrite) { myHasColors = theToWrite; }

  bool HasPartId() const { return myHasPartId; }

  void SetPartId(bool theSurfId)
  {
    myHasPartId = theSurfId;
    myHasFaceId = myHasFaceId && !myHasPartId;
  }

  bool HasFaceId() const { return myHasFaceId; }

  void SetFaceId(bool theSurfId)
  {
    myHasFaceId = theSurfId;
    myHasPartId = myHasPartId && !myHasFaceId;
  }

public:
  Standard_EXPORT virtual bool Perform(
    const occ::handle<TDocStd_Document>&            theDocument,
    const NCollection_Sequence<TDF_Label>&          theRootLabels,
    const NCollection_Map<TCollection_AsciiString>* theLabelFilter,
    const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theFileInfo,
    const Message_ProgressRange& theProgress);

  Standard_EXPORT virtual bool Perform(
    const occ::handle<TDocStd_Document>&                                                theDocument,
    const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theFileInfo,
    const Message_ProgressRange& theProgress);

protected:
  Standard_EXPORT virtual bool toSkipFaceMesh(const RWMesh_FaceIterator& theFaceIter);

  Standard_EXPORT virtual void addFaceInfo(const RWMesh_FaceIterator& theFace,
                                           int&                       theNbNodes,
                                           int&                       theNbElems);

  Standard_EXPORT virtual bool writeShape(RWPly_PlyWriterContext&    theWriter,
                                          Message_LazyProgressScope& thePSentry,
                                          const int                  theWriteStep,
                                          const TDF_Label&           theLabel,
                                          const TopLoc_Location&     theParentTrsf,
                                          const XCAFPrs_Style&       theParentStyle);

  Standard_EXPORT virtual bool writeNodes(RWPly_PlyWriterContext&    theWriter,
                                          Message_LazyProgressScope& thePSentry,
                                          const RWMesh_FaceIterator& theFace);

  Standard_EXPORT virtual bool writeIndices(RWPly_PlyWriterContext&    theWriter,
                                            Message_LazyProgressScope& thePSentry,
                                            const RWMesh_FaceIterator& theFace);

protected:
  TCollection_AsciiString myFile;

  RWMesh_CoordinateSystemConverter myCSTrsf;
  XCAFPrs_Style                    myDefaultStyle;

  bool myIsDoublePrec;
  bool myHasNormals;
  bool myHasColors;
  bool myHasTexCoords;
  bool myHasPartId;
  bool myHasFaceId;
};
