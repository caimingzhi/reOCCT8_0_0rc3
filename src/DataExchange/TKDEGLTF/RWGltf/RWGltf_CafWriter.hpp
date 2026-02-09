#pragma once

#include <Message_ProgressScope.hpp>
#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_Map.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <TopTools_ShapeMapHasher.hpp>

#ifndef _RWGltf_DracoParameters_HeaderFile
  #define _RWGltf_DracoParameters_HeaderFile

struct RWGltf_DracoParameters
{
  RWGltf_DracoParameters()
      : DracoCompression(false),
        CompressionLevel(7),
        QuantizePositionBits(14),
        QuantizeNormalBits(10),
        QuantizeTexcoordBits(12),
        QuantizeColorBits(8),
        QuantizeGenericBits(12),
        UnifiedQuantization(false)
  {
  }

  bool DracoCompression;
  int  CompressionLevel;
  int  QuantizePositionBits;
  int  QuantizeNormalBits;
  int  QuantizeTexcoordBits;
  int  QuantizeColorBits;
  int  QuantizeGenericBits;
  bool UnifiedQuantization;
};

#endif

#include <RWGltf_GltfArrayType.hpp>
#include <RWGltf_GltfBufferView.hpp>

#include <NCollection_List.hpp>
#include <NCollection_Shared.hpp>
#include <RWGltf_GltfAccessor.hpp>
#include <TopoDS_Shape.hpp>
#include <XCAFPrs_Style.hpp>

class RWGltf_GltfFace : public Standard_Transient
{
public:
  RWGltf_GltfAccessor NodePos;
  RWGltf_GltfAccessor NodeNorm;
  RWGltf_GltfAccessor NodeUV;
  RWGltf_GltfAccessor Indices;
  TopoDS_Shape        Shape;
  XCAFPrs_Style       Style;

  int NbIndexedNodes;

  RWGltf_GltfFace()
      : NbIndexedNodes(0)
  {
  }
};

#include <RWGltf_WriterTrsfFormat.hpp>
#include <RWMesh_CoordinateSystemConverter.hpp>
#include <RWMesh_NameFormat.hpp>
#include <XCAFPrs_DocumentNode.hpp>
#include <XCAFPrs_Style.hpp>
#include <Poly_Triangle.hpp>

#include <memory>

class Message_ProgressRange;
class RWMesh_ShapeIterator;
class RWMesh_FaceIterator;
class RWMesh_EdgeIterator;
class RWMesh_VertexIterator;
class RWGltf_GltfOStreamWriter;
class RWGltf_GltfMaterialMap;
class RWGltf_GltfSceneNodeMap;
class TDataStd_NamedData;
class TDocStd_Document;

class RWGltf_CafWriter : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(RWGltf_CafWriter, Standard_Transient)
public:
  struct Mesh
  {
    std::vector<NCollection_Vec3<float>> NodesVec;
    std::vector<NCollection_Vec3<float>> NormalsVec;
    std::vector<NCollection_Vec2<float>> TexCoordsVec;
    std::vector<Poly_Triangle>           IndicesVec;
  };

  Standard_EXPORT RWGltf_CafWriter(const TCollection_AsciiString& theFile, bool theIsBinary);

  Standard_EXPORT ~RWGltf_CafWriter() override;

  const RWMesh_CoordinateSystemConverter& CoordinateSystemConverter() const { return myCSTrsf; }

  RWMesh_CoordinateSystemConverter& ChangeCoordinateSystemConverter() { return myCSTrsf; }

  void SetCoordinateSystemConverter(const RWMesh_CoordinateSystemConverter& theConverter)
  {
    myCSTrsf = theConverter;
  }

  bool IsBinary() const { return myIsBinary; }

  RWGltf_WriterTrsfFormat TransformationFormat() const { return myTrsfFormat; }

  void SetTransformationFormat(RWGltf_WriterTrsfFormat theFormat) { myTrsfFormat = theFormat; }

  RWMesh_NameFormat NodeNameFormat() const { return myNodeNameFormat; }

  void SetNodeNameFormat(RWMesh_NameFormat theFormat) { myNodeNameFormat = theFormat; }

  RWMesh_NameFormat MeshNameFormat() const { return myMeshNameFormat; }

  void SetMeshNameFormat(RWMesh_NameFormat theFormat) { myMeshNameFormat = theFormat; }

  bool IsForcedUVExport() const { return myIsForcedUVExport; }

  void SetForcedUVExport(bool theToForce) { myIsForcedUVExport = theToForce; }

  const XCAFPrs_Style& DefaultStyle() const { return myDefaultStyle; }

  void SetDefaultStyle(const XCAFPrs_Style& theStyle) { myDefaultStyle = theStyle; }

  bool ToEmbedTexturesInGlb() { return myToEmbedTexturesInGlb; }

  void SetToEmbedTexturesInGlb(bool theToEmbedTexturesInGlb)
  {
    myToEmbedTexturesInGlb = theToEmbedTexturesInGlb;
  }

  bool ToMergeFaces() const { return myToMergeFaces; }

  void SetMergeFaces(bool theToMerge) { myToMergeFaces = theToMerge; }

  bool ToSplitIndices16() const { return myToSplitIndices16; }

  void SetSplitIndices16(bool theToSplit) { myToSplitIndices16 = theToSplit; }

  bool ToParallel() const { return myToParallel; }

  void SetParallel(bool theToParallel) { myToParallel = theToParallel; }

  const RWGltf_DracoParameters& CompressionParameters() const { return myDracoParameters; }

  void SetCompressionParameters(const RWGltf_DracoParameters& theDracoParameters)
  {
    myDracoParameters = theDracoParameters;
  }

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
  Standard_EXPORT virtual bool writeBinData(
    const occ::handle<TDocStd_Document>&            theDocument,
    const NCollection_Sequence<TDF_Label>&          theRootLabels,
    const NCollection_Map<TCollection_AsciiString>* theLabelFilter,
    const Message_ProgressRange&                    theProgress);

  Standard_EXPORT virtual bool writeJson(
    const occ::handle<TDocStd_Document>&            theDocument,
    const NCollection_Sequence<TDF_Label>&          theRootLabels,
    const NCollection_Map<TCollection_AsciiString>* theLabelFilter,
    const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theFileInfo,
    const Message_ProgressRange& theProgress);

protected:
  Standard_EXPORT virtual TopAbs_ShapeEnum getShapeType(const TopoDS_Shape& theShape) const;

  Standard_EXPORT virtual bool toSkipShape(const RWMesh_ShapeIterator& theShapeIter) const;

  Standard_EXPORT virtual bool hasTriangulation(const RWGltf_GltfFace& theShape) const;

  Standard_EXPORT virtual TCollection_AsciiString formatName(RWMesh_NameFormat theFormat,
                                                             const TDF_Label&  theLabel,
                                                             const TDF_Label&  theRefLabel) const;

  Standard_EXPORT virtual void saveNodes(
    RWGltf_GltfFace&                               theGltfFace,
    std::ostream&                                  theBinFile,
    const RWMesh_ShapeIterator&                    theShapeIter,
    int&                                           theAccessorNb,
    const std::shared_ptr<RWGltf_CafWriter::Mesh>& theMesh) const;

  Standard_EXPORT virtual void saveNormals(
    RWGltf_GltfFace&                               theGltfFace,
    std::ostream&                                  theBinFile,
    const RWMesh_FaceIterator&                     theFaceIter,
    int&                                           theAccessorNb,
    const std::shared_ptr<RWGltf_CafWriter::Mesh>& theMesh) const;

  Standard_EXPORT virtual void saveTextCoords(
    RWGltf_GltfFace&                               theGltfFace,
    std::ostream&                                  theBinFile,
    const RWMesh_FaceIterator&                     theFaceIter,
    int&                                           theAccessorNb,
    const std::shared_ptr<RWGltf_CafWriter::Mesh>& theMesh) const;

  Standard_EXPORT virtual void saveIndices(RWGltf_GltfFace&            theGltfFace,
                                           std::ostream&               theBinFile,
                                           const RWMesh_ShapeIterator& theShapeIter,
                                           int&                        theAccessorNb,
                                           const std::shared_ptr<RWGltf_CafWriter::Mesh>& theMesh);

  Standard_EXPORT virtual void saveTriangleIndices(
    RWGltf_GltfFace&                               theGltfFace,
    std::ostream&                                  theBinFile,
    const RWMesh_FaceIterator&                     theFaceIter,
    const std::shared_ptr<RWGltf_CafWriter::Mesh>& theMesh);

  Standard_EXPORT virtual void saveEdgeIndices(RWGltf_GltfFace&           theGltfFace,
                                               std::ostream&              theBinFile,
                                               const RWMesh_EdgeIterator& theEdgeIter);

  Standard_EXPORT virtual void saveVertexIndices(RWGltf_GltfFace&             theGltfFace,
                                                 std::ostream&                theBinFile,
                                                 const RWMesh_VertexIterator& theVertexIter);

protected:
  Standard_EXPORT virtual void writePositions(const RWGltf_GltfFace& theGltfFace);

  Standard_EXPORT virtual void writeNormals(const RWGltf_GltfFace& theGltfFace);

  Standard_EXPORT virtual void writeTextCoords(const RWGltf_GltfFace& theGltfFace);

  Standard_EXPORT virtual void writeIndices(const RWGltf_GltfFace& theGltfFace);

protected:
  Standard_EXPORT virtual void writeAccessors(const RWGltf_GltfSceneNodeMap& theSceneNodeMap);

  Standard_EXPORT virtual void writeAnimations();

  Standard_EXPORT virtual void writeAsset(
    const NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>&
      theFileInfo);

  Standard_EXPORT virtual void writeBufferViews(const int theBinDataBufferId);

  Standard_EXPORT virtual void writeBuffers();

  Standard_EXPORT virtual void writeExtensions();

  Standard_EXPORT virtual void writeImages(const RWGltf_GltfSceneNodeMap& theSceneNodeMap);

  Standard_EXPORT virtual void writeMaterials(const RWGltf_GltfSceneNodeMap& theSceneNodeMap);

  Standard_EXPORT virtual void writeMaterial(RWMesh_ShapeIterator& theShapeIter,
                                             bool&                 theIsStarted);

  Standard_EXPORT virtual void writeMeshes(const RWGltf_GltfSceneNodeMap& theSceneNodeMap);

  Standard_EXPORT virtual void writePrimArray(const RWGltf_GltfFace&         theGltfFace,
                                              const TCollection_AsciiString& theName,
                                              const int                      theDracoBufInd,
                                              bool&                          theToStartPrims);

  Standard_EXPORT virtual void writeNodes(
    const occ::handle<TDocStd_Document>&            theDocument,
    const NCollection_Sequence<TDF_Label>&          theRootLabels,
    const NCollection_Map<TCollection_AsciiString>* theLabelFilter,
    const RWGltf_GltfSceneNodeMap&                  theSceneNodeMap,
    NCollection_Sequence<int>&                      theSceneRootNodeInds);

  Standard_EXPORT virtual void writeSamplers();

  Standard_EXPORT virtual void writeScene(const int theDefSceneId);

  Standard_EXPORT virtual void writeScenes(const NCollection_Sequence<int>& theSceneRootNodeInds);

  Standard_EXPORT virtual void writeSkins();

  Standard_EXPORT virtual void writeTextures(const RWGltf_GltfSceneNodeMap& theSceneNodeMap);

  Standard_EXPORT virtual void writeExtrasAttributes(
    const occ::handle<TDataStd_NamedData>& theNamedData);

  Standard_EXPORT virtual void dispatchShapes(
    const XCAFPrs_DocumentNode&                                       theDocNode,
    const Message_ProgressScope&                                      thePSentryBin,
    NCollection_DataMap<XCAFPrs_Style, occ::handle<RWGltf_GltfFace>>& theMergedFaces,
    RWMesh_ShapeIterator&                                             theShapeIter);

  Standard_EXPORT bool writeShapesToBin(RWGltf_GltfFace&      theGltfFace,
                                        std::ostream&         theBinFile,
                                        RWMesh_ShapeIterator& theShapeIter,
                                        int&                  theAccessorNb,
                                        const std::shared_ptr<RWGltf_CafWriter::Mesh>& theMesh,
                                        const RWGltf_GltfArrayType                     theArrType,
                                        const Message_ProgressScope& thePSentryBin);

  Standard_EXPORT virtual void writeShapes(
    RWMesh_ShapeIterator&          theShapeIter,
    int&                           theDracoBufInd,
    bool&                          theToStartPrims,
    const TCollection_AsciiString& theNodeName,
    NCollection_Map<
      occ::handle<NCollection_Shared<NCollection_List<occ::handle<RWGltf_GltfFace>>>>>&
                                          theWrittenShapes,
    NCollection_IndexedDataMap<int, int>& theDracoBufIndMap);

protected:
  struct RWGltf_StyledShape
  {
    TopoDS_Shape  Shape;
    XCAFPrs_Style Style;

    RWGltf_StyledShape() = default;

    explicit RWGltf_StyledShape(const TopoDS_Shape& theShape)
        : Shape(theShape)
    {
    }

    explicit RWGltf_StyledShape(const TopoDS_Shape& theShape, const XCAFPrs_Style& theStyle)
        : Shape(theShape),
          Style(theStyle)
    {
    }

    bool operator==(const RWGltf_StyledShape& theStyledShape) const
    {
      return Shape.IsSame(theStyledShape.Shape) && Style.IsEqual(theStyledShape.Style);
    }
  };

  struct Hasher
  {
    size_t operator()(const RWGltf_StyledShape& theShape) const noexcept
    {
      return std::hash<TopoDS_Shape>{}(theShape.Shape);
    }

    bool operator()(const RWGltf_StyledShape& theShape1,
                    const RWGltf_StyledShape& theShape2) const noexcept
    {
      return theShape1 == theShape2;
    }
  };

  typedef NCollection_IndexedDataMap<
    RWGltf_StyledShape,
    occ::handle<NCollection_Shared<NCollection_List<occ::handle<RWGltf_GltfFace>>>>,
    Hasher>
    ShapeToGltfFaceMap;

protected:
  TCollection_AsciiString myFile;

  TCollection_AsciiString          myBinFileNameFull;
  TCollection_AsciiString          myBinFileNameShort;
  RWGltf_WriterTrsfFormat          myTrsfFormat;
  RWMesh_NameFormat                myNodeNameFormat;
  RWMesh_NameFormat                myMeshNameFormat;
  bool                             myIsBinary;
  bool                             myIsForcedUVExport;
  bool                             myToEmbedTexturesInGlb;
  bool                             myToMergeFaces;
  bool                             myToSplitIndices16;
  RWMesh_CoordinateSystemConverter myCSTrsf;
  XCAFPrs_Style                    myDefaultStyle;

  std::shared_ptr<RWGltf_GltfOStreamWriter> myWriter;
  occ::handle<RWGltf_GltfMaterialMap>       myMaterialMap;
  RWGltf_GltfBufferView                     myBuffViewPos;
  RWGltf_GltfBufferView                     myBuffViewNorm;
  RWGltf_GltfBufferView                     myBuffViewTextCoord;
  RWGltf_GltfBufferView                     myBuffViewInd;
  ShapeToGltfFaceMap                        myBinDataMap;
  int64_t                                   myBinDataLen64;

  std::vector<RWGltf_GltfBufferView> myBuffViewsDraco;
  bool                               myToParallel;

  RWGltf_DracoParameters myDracoParameters;
};
