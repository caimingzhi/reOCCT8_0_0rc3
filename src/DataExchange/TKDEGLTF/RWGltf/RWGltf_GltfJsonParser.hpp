#pragma once

#include <Message_Gravity.hpp>
#include <Message_ProgressScope.hpp>
#include <RWGltf_GltfPrimArrayData.hpp>
#include <RWGltf_GltfLatePrimitiveArray.hpp>
#include <RWGltf_GltfBufferView.hpp>
#include <RWGltf_GltfRootElement.hpp>
#include <RWGltf_MaterialCommon.hpp>
#include <RWGltf_MaterialMetallicRoughness.hpp>
#include <RWMesh_CoordinateSystemConverter.hpp>
#include <RWMesh_NodeAttributes.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>

#ifdef None
  #undef None
#endif
#ifdef Bool
  #undef Bool
#endif

#ifdef HAVE_RAPIDJSON

  #include <Standard_WarningsDisable.hpp>
  #include <rapidjson/document.h>
  #include <rapidjson/prettywriter.h>
  #include <rapidjson/stringbuffer.h>
  #include <rapidjson/istreamwrapper.h>
  #include <rapidjson/ostreamwrapper.h>
  #include <Standard_WarningsRestore.hpp>

typedef rapidjson::Document::ValueType RWGltf_JsonValue;
#endif

class RWGltf_GltfJsonParser
#ifdef HAVE_RAPIDJSON
    : public rapidjson::Document
#endif
{
public:
#ifdef HAVE_RAPIDJSON

  Standard_EXPORT static const char* FormatParseError(rapidjson::ParseErrorCode theCode);
#endif

public:
  Standard_EXPORT RWGltf_GltfJsonParser(NCollection_Sequence<TopoDS_Shape>& theRootShapes);

  Standard_EXPORT void SetFilePath(const TCollection_AsciiString& theFilePath);

  void SetProbeHeader(bool theToProbe) { myToProbeHeader = theToProbe; }

  const TCollection_AsciiString& ErrorPrefix() const { return myErrorPrefix; }

  void SetErrorPrefix(const TCollection_AsciiString& theErrPrefix) { myErrorPrefix = theErrPrefix; }

  void SetAttributeMap(
    NCollection_DataMap<TopoDS_Shape, RWMesh_NodeAttributes, TopTools_ShapeMapHasher>& theAttribMap)
  {
    myAttribMap = &theAttribMap;
  }

  void SetScaleMap(NCollection_DataMap<TopoDS_Shape, gp_XYZ, TopTools_ShapeMapHasher>& theScaleMap)
  {
    myShapeScaleMap = &theScaleMap;
  }

  void SetExternalFiles(NCollection_IndexedMap<TCollection_AsciiString>& theExternalFiles)
  {
    myExternalFiles = &theExternalFiles;
  }

  void SetMetadata(
    NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>& theMetadata)
  {
    myMetadata = &theMetadata;
  }

  void SetReadAssetExtras(bool theToRead) { myToReadAssetExtras = theToRead; }

  const RWMesh_CoordinateSystemConverter& CoordinateSystemConverter() const { return myCSTrsf; }

  void SetCoordinateSystemConverter(const RWMesh_CoordinateSystemConverter& theConverter)
  {
    myCSTrsf = theConverter;
  }

  void SetBinaryFormat(int64_t theBinBodyOffset, int64_t theBinBodyLen)
  {
    myIsBinary      = true;
    myBinBodyOffset = theBinBodyOffset;
    myBinBodyLen    = theBinBodyLen;
  }

  void SetSkipEmptyNodes(bool theToSkip) { myToSkipEmptyNodes = theToSkip; }

  void SetLoadAllScenes(bool theToLoadAll) { myToLoadAllScenes = theToLoadAll; }

  void SetMeshNameAsFallback(bool theToFallback) { myUseMeshNameAsFallback = theToFallback; }

  void SetToApplyScale(bool theToApplyScale) { myToApplyScale = theToApplyScale; }

  Standard_EXPORT bool Parse(const Message_ProgressRange& theProgress);

  NCollection_Vector<TopoDS_Face>& FaceList() { return myFaceList; }

  void SetStream(std::shared_ptr<std::istream>& theStream) { myStream = theStream; }

protected:
#ifdef HAVE_RAPIDJSON

  Standard_EXPORT bool gltfParseRoots();

  Standard_EXPORT bool gltfParseScene(const Message_ProgressRange& theProgress);

  Standard_EXPORT void gltfParseAsset();

protected:
  Standard_EXPORT void gltfParseMaterials();

  Standard_EXPORT bool gltfParseStdMaterial(occ::handle<RWGltf_MaterialCommon>& theMat,
                                            const RWGltf_JsonValue&             theMatNode);

  Standard_EXPORT bool gltfParsePbrMaterial(occ::handle<RWGltf_MaterialMetallicRoughness>& theMat,
                                            const RWGltf_JsonValue& theMatNode);

  Standard_EXPORT bool gltfParseCommonMaterial(occ::handle<RWGltf_MaterialCommon>& theMat,
                                               const RWGltf_JsonValue&             theMatNode);

  Standard_EXPORT bool gltfParseTexture(occ::handle<Image_Texture>& theTexture,
                                        const RWGltf_JsonValue*     theTextureId);

  Standard_EXPORT bool gltfParseTexturInGlbBuffer(occ::handle<Image_Texture>&    theTexture,
                                                  const RWGltf_JsonValue&        theBinVal,
                                                  const TCollection_AsciiString& theBufferViewId,
                                                  const RWGltf_JsonValue&        theBufferViewName);

  Standard_EXPORT bool gltfParseTextureInBufferView(occ::handle<Image_Texture>&    theTexture,
                                                    const TCollection_AsciiString& theSourceId,
                                                    const TCollection_AsciiString& theBufferViewhId,
                                                    const RWGltf_JsonValue&        theBufferView);

  Standard_EXPORT void gltfBindMaterial(
    const occ::handle<RWGltf_MaterialMetallicRoughness>& theMatPbr,
    const occ::handle<RWGltf_MaterialCommon>&            theMatCommon);

protected:
  Standard_EXPORT bool gltfParseSceneNodes(NCollection_Sequence<TopoDS_Shape>& theShapeSeq,
                                           const RWGltf_JsonValue&             theSceneNodes,
                                           const Message_ProgressRange&        theProgress);

  Standard_EXPORT bool gltfParseSceneNode(TopoDS_Shape&                  theNodeShape,
                                          const TCollection_AsciiString& theSceneNodeId,
                                          const RWGltf_JsonValue&        theSceneNode,
                                          const Message_ProgressRange&   theProgress);

  Standard_EXPORT bool gltfParseMesh(TopoDS_Shape&                  theMeshShape,
                                     const TCollection_AsciiString& theMeshId,
                                     const RWGltf_JsonValue&        theMesh);

  Standard_EXPORT bool gltfParsePrimArray(TopoDS_Shape&                  thePrimArrayShape,
                                          const TCollection_AsciiString& theMeshId,
                                          const TCollection_AsciiString& theMeshName,
                                          const RWGltf_JsonValue&        thePrimArray);

  Standard_EXPORT bool gltfParseAccessor(
    const occ::handle<RWGltf_GltfLatePrimitiveArray>& theMeshData,
    const TCollection_AsciiString&                    theName,
    const RWGltf_JsonValue&                           theAccessor,
    const RWGltf_GltfArrayType                        theType,
    const RWGltf_JsonValue*                           theCompBuffView);

  Standard_EXPORT bool gltfParseBufferView(
    const occ::handle<RWGltf_GltfLatePrimitiveArray>& theMeshData,
    const TCollection_AsciiString&                    theName,
    const RWGltf_JsonValue&                           theBufferView,
    const RWGltf_GltfAccessor&                        theAccessor,
    const RWGltf_GltfArrayType                        theType);

  Standard_EXPORT bool gltfParseBuffer(
    const occ::handle<RWGltf_GltfLatePrimitiveArray>& theMeshData,
    const TCollection_AsciiString&                    theName,
    const RWGltf_JsonValue&                           theBuffer,
    const RWGltf_GltfAccessor&                        theAccessor,
    const RWGltf_GltfBufferView&                      theView,
    const RWGltf_GltfArrayType                        theType);

protected:
  static bool gltfReadVec4(NCollection_Vec4<double>& theVec4, const RWGltf_JsonValue* theVal)
  {
    if (theVal == nullptr || !theVal->IsArray() || theVal->Size() != 4)
    {
      return false;
    }

    for (int aCompIter = 0; aCompIter < 4; ++aCompIter)
    {
      const RWGltf_JsonValue& aGenVal = (*theVal)[aCompIter];
      if (!aGenVal.IsNumber())
      {
        return false;
      }
      theVec4[aCompIter] = aGenVal.GetDouble();
    }
    return true;
  }

  static bool validateColor4(const NCollection_Vec4<double>& theVec)
  {
    return theVec.r() >= 0.0 && theVec.r() <= 1.0 && theVec.g() >= 0.0 && theVec.g() <= 1.0
           && theVec.b() >= 0.0 && theVec.b() <= 1.0 && theVec.a() >= 0.0 && theVec.a() <= 1.0;
  }

  static bool gltfReadVec3(NCollection_Vec3<double>& theVec3, const RWGltf_JsonValue* theVal)
  {
    if (theVal == nullptr || !theVal->IsArray() || theVal->Size() != 3)
    {
      return false;
    }

    for (int aCompIter = 0; aCompIter < 3; ++aCompIter)
    {
      const RWGltf_JsonValue& aGenVal = (*theVal)[aCompIter];
      if (!aGenVal.IsNumber())
      {
        return false;
      }
      theVec3[aCompIter] = aGenVal.GetDouble();
    }
    return true;
  }

  static bool validateColor3(const NCollection_Vec3<double>& theVec)
  {
    return theVec.r() >= 0.0 && theVec.r() <= 1.0 && theVec.g() >= 0.0 && theVec.g() <= 1.0
           && theVec.b() >= 0.0 && theVec.b() <= 1.0;
  }

protected:
  enum ShapeMapGroup
  {
    ShapeMapGroup_Nodes,
    ShapeMapGroup_Meshes,
    ShapeMapGroup_PrimArray,
  };

  void bindNodeShape(TopoDS_Shape&                          theShape,
                     const TopLoc_Location&                 theLoc,
                     const bool                             theHasScale,
                     const gp_XYZ&                          theScale,
                     const TCollection_AsciiString&         theNodeId,
                     const RWGltf_JsonValue*                theUserName,
                     const occ::handle<TDataStd_NamedData>& theExtras)
  {
    bindNamedShape(theShape,
                   ShapeMapGroup_Nodes,
                   theLoc,
                   theHasScale,
                   theScale,
                   theNodeId,
                   theUserName,
                   theExtras);
  }

  void bindMeshShape(TopoDS_Shape&                          theShape,
                     const TCollection_AsciiString&         theMeshId,
                     const RWGltf_JsonValue*                theUserName,
                     const occ::handle<TDataStd_NamedData>& theExtras)
  {
    bindNamedShape(theShape,
                   ShapeMapGroup_Meshes,
                   TopLoc_Location(),
                   false,
                   gp_XYZ(),
                   theMeshId,
                   theUserName,
                   theExtras);
  }

  bool findNodeShape(TopoDS_Shape& theShape, const TCollection_AsciiString& theNodeId) const
  {
    return findNamedShape(theShape, ShapeMapGroup_Nodes, theNodeId);
  }

  bool findMeshShape(TopoDS_Shape& theShape, const TCollection_AsciiString& theMeshId) const
  {
    return findNamedShape(theShape, ShapeMapGroup_Meshes, theMeshId);
  }

  Standard_EXPORT void bindNamedShape(TopoDS_Shape&                          theShape,
                                      ShapeMapGroup                          theGroup,
                                      const TopLoc_Location&                 theLoc,
                                      const bool                             theHasScale,
                                      const gp_XYZ&                          theScale,
                                      const TCollection_AsciiString&         theId,
                                      const RWGltf_JsonValue*                theUserName,
                                      const occ::handle<TDataStd_NamedData>& theExtras);

  bool findNamedShape(TopoDS_Shape&                  theShape,
                      ShapeMapGroup                  theGroup,
                      const TCollection_AsciiString& theId) const
  {
    return myShapeMap[theGroup].Find(theId, theShape);
  }

  static TCollection_AsciiString getKeyString(const RWGltf_JsonValue& theValue)
  {
    if (theValue.IsString())
    {
      return TCollection_AsciiString(theValue.GetString());
    }
    else if (theValue.IsInt())
    {
      return TCollection_AsciiString(theValue.GetInt());
    }
    return TCollection_AsciiString();
  }

protected:
  class GltfElementMap
  {
  public:
    GltfElementMap()
        : myRoot(nullptr)
    {
    }

    bool IsNull() const { return myRoot == nullptr; }

    const RWGltf_JsonValue* Root() const { return myRoot; }

    const RWGltf_JsonValue* FindChild(const TCollection_AsciiString& theKey)
    {
      const RWGltf_JsonValue* aNode = nullptr;
      return myChildren.Find(theKey, aNode) ? aNode : nullptr;
    }

    const RWGltf_JsonValue* FindChild(const RWGltf_JsonValue& theKey)
    {
      const TCollection_AsciiString aKey = getKeyString(theKey);
      if (aKey.IsEmpty())
      {
        return nullptr;
      }

      const RWGltf_JsonValue* aNode = nullptr;
      return myChildren.Find(aKey, aNode) ? aNode : nullptr;
    }

    void Init(const TCollection_AsciiString& theRootName, const RWGltf_JsonValue* theRoot);

  private:
    NCollection_DataMap<TCollection_AsciiString, const RWGltf_JsonValue*> myChildren;
    const RWGltf_JsonValue*                                               myRoot;
  };

private:
  bool parseTransformationMatrix(const TCollection_AsciiString& theSceneNodeId,
                                 const RWGltf_JsonValue&        theMatrixVal,
                                 TopLoc_Location&               theResult) const;

  bool parseTransformationComponents(const TCollection_AsciiString& theSceneNodeId,
                                     const RWGltf_JsonValue*        theRotationVal,
                                     const RWGltf_JsonValue*        theScaleVal,
                                     const RWGltf_JsonValue*        theTranslationVal,
                                     TopLoc_Location&               theResult,
                                     bool&                          theHasScale,
                                     gp_XYZ&                        theScale) const;

  Standard_EXPORT bool fillMeshData(
    const occ::handle<RWGltf_GltfLatePrimitiveArray>& theMeshData) const;

#endif
protected:
  void reportGltfSyntaxProblem(const TCollection_AsciiString& theMsg,
                               Message_Gravity                theGravity) const;

protected:
  NCollection_Sequence<TopoDS_Shape>*                                                myRootShapes;
  NCollection_DataMap<TopoDS_Shape, RWMesh_NodeAttributes, TopTools_ShapeMapHasher>* myAttribMap;
  NCollection_IndexedMap<TCollection_AsciiString>*                    myExternalFiles;
  NCollection_DataMap<TopoDS_Shape, gp_XYZ, TopTools_ShapeMapHasher>* myShapeScaleMap;

  RWMesh_CoordinateSystemConverter myCSTrsf;

  NCollection_IndexedDataMap<TCollection_AsciiString, TCollection_AsciiString>* myMetadata;

  mutable std::shared_ptr<std::istream> myStream;

  NCollection_DataMap<TCollection_AsciiString, occ::handle<RWGltf_MaterialMetallicRoughness>>
    myMaterialsPbr;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<RWGltf_MaterialCommon>>
                                                                                 myMaterialsCommon;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<XCAFDoc_VisMaterial>> myMaterials;
  NCollection_DataMap<TCollection_AsciiString, TopoDS_Shape>                     myShapeMap[3];

  NCollection_DataMap<TCollection_AsciiString, bool>                            myProbedFiles;
  NCollection_DataMap<TCollection_AsciiString, occ::handle<NCollection_Buffer>> myDecodedBuffers;
  NCollection_Vector<TopoDS_Face>                                               myFaceList;

  TCollection_AsciiString myFilePath;
  TCollection_AsciiString myFolder;
  TCollection_AsciiString myErrorPrefix;
  int64_t                 myBinBodyOffset;
  int64_t                 myBinBodyLen;
  bool                    myIsBinary;
  bool                    myIsGltf1;
  bool                    myToSkipEmptyNodes;

  bool myToLoadAllScenes;
  bool myUseMeshNameAsFallback;
  bool myToProbeHeader;
  bool myToReadAssetExtras;
  bool myToApplyScale;

#ifdef HAVE_RAPIDJSON
  GltfElementMap myGltfRoots[RWGltf_GltfRootElement_NB];
#endif
};
