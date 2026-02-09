#pragma once

#include <NCollection_Vector.hpp>
#include <RWMesh_CafReader.hpp>
#include <TopoDS_Face.hpp>

class RWMesh_TriangulationReader;

class RWGltf_CafReader : public RWMesh_CafReader
{
  DEFINE_STANDARD_RTTIEXT(RWGltf_CafReader, RWMesh_CafReader)
public:
  Standard_EXPORT RWGltf_CafReader();

  bool ToParallel() const { return myToParallel; }

  void SetParallel(bool theToParallel) { myToParallel = theToParallel; }

  bool ToSkipEmptyNodes() { return myToSkipEmptyNodes; }

  void SetSkipEmptyNodes(bool theToSkip) { myToSkipEmptyNodes = theToSkip; }

  bool ToLoadAllScenes() const { return myToLoadAllScenes; }

  bool ToApplyScale() const { return myToApplyScale; }

  void SetLoadAllScenes(bool theToLoadAll) { myToLoadAllScenes = theToLoadAll; }

  bool ToUseMeshNameAsFallback() { return myUseMeshNameAsFallback; }

  void SetMeshNameAsFallback(bool theToFallback) { myUseMeshNameAsFallback = theToFallback; }

  bool IsDoublePrecision() const { return myIsDoublePrecision; }

  void SetDoublePrecision(bool theIsDouble) { myIsDoublePrecision = theIsDouble; }

  bool ToSkipLateDataLoading() { return myToSkipLateDataLoading; }

  void SetToSkipLateDataLoading(bool theToSkip) { myToSkipLateDataLoading = theToSkip; }

  void SetToApplyScale(bool theToApplyScale) { myToApplyScale = theToApplyScale; }

  bool ToKeepLateData() { return myToKeepLateData; }

  void SetToKeepLateData(bool theToKeep) { myToKeepLateData = theToKeep; }

  bool ToPrintDebugMessages() const { return myToPrintDebugMessages; }

  void SetToPrintDebugMessages(const bool theToPrint) { myToPrintDebugMessages = theToPrint; }

protected:
  Standard_EXPORT bool performMesh(std::istream&                  theStream,
                                   const TCollection_AsciiString& theFile,
                                   const Message_ProgressRange&   theProgress,
                                   const bool                     theToProbe) override;

  Standard_EXPORT void fillDocument() override;

  Standard_EXPORT bool addShapeIntoDoc(CafDocumentTools&              theTools,
                                       const TopoDS_Shape&            theShape,
                                       const TDF_Label&               theLabel,
                                       const TCollection_AsciiString& theParentName,
                                       const bool                     theHasScale = false,
                                       const gp_XYZ& theScale = gp_XYZ(0., 0., 0.));

  Standard_EXPORT virtual occ::handle<RWMesh_TriangulationReader> createMeshReaderContext() const;

  Standard_EXPORT virtual bool readLateData(NCollection_Vector<TopoDS_Face>& theFaces,
                                            const TCollection_AsciiString&   theFile,
                                            const Message_ProgressRange&     theProgress);

  Standard_EXPORT void updateLateDataReader(
    NCollection_Vector<TopoDS_Face>&               theFaces,
    const occ::handle<RWMesh_TriangulationReader>& theReader) const;

protected:
  class CafReader_GltfBaseLoadingFunctor;
  class CafReader_GltfFullDataLoadingFunctor;
  class CafReader_GltfStreamDataLoadingFunctor;

protected:
  bool myToParallel;
  bool myToSkipEmptyNodes;

  bool myToLoadAllScenes;
  bool myUseMeshNameAsFallback;
  bool myIsDoublePrecision;
  bool myToSkipLateDataLoading;
  bool myToKeepLateData;

  bool                                                                myToPrintDebugMessages;
  bool                                                                myToApplyScale;
  NCollection_DataMap<TopoDS_Shape, gp_XYZ, TopTools_ShapeMapHasher>* myShapeScaleMap;
};
