#pragma once

#include <Graphic3d_IndexBuffer.hpp>
#include <Graphic3d_TypeOfPrimitiveArray.hpp>
#include <Select3D_SensitiveSet.hpp>

#ifndef _Select3D_BVHIndexBuffer_Header
  #define _Select3D_BVHIndexBuffer_Header

  #include <Graphic3d_Buffer.hpp>

class Select3D_BVHIndexBuffer : public Graphic3d_Buffer
{
public:
  Select3D_BVHIndexBuffer(const occ::handle<NCollection_BaseAllocator>& theAlloc)
      : Graphic3d_Buffer(theAlloc),
        myHasPatches(false)
  {
  }

  bool HasPatches() const { return myHasPatches; }

  bool Init(const int theNbElems, const bool theHasPatches)
  {
    release();
    Stride       = sizeof(unsigned int);
    myHasPatches = theHasPatches;
    if (theHasPatches)
    {
      Stride += sizeof(unsigned int);
    }

    NbElements   = theNbElems;
    NbAttributes = 0;
    if (NbElements != 0 && !Allocate(size_t(Stride) * size_t(NbElements)))
    {
      release();
      return false;
    }
    return true;
  }

  int Index(const int theIndex) const
  {
    return int(*reinterpret_cast<const unsigned int*>(value(theIndex)));
  }

  int PatchSize(const int theIndex) const
  {
    return myHasPatches
             ? int(*reinterpret_cast<const unsigned int*>(value(theIndex) + sizeof(unsigned int)))
             : 1;
  }

  void SetIndex(const int theIndex, const int theValue)
  {
    *reinterpret_cast<unsigned int*>(changeValue(theIndex)) = (unsigned int)theValue;
  }

  void SetIndex(const int theIndex, const int theValue, const int thePatchSize)
  {
    *reinterpret_cast<unsigned int*>(changeValue(theIndex)) = (unsigned int)theValue;
    *reinterpret_cast<unsigned int*>(changeValue(theIndex) + sizeof(unsigned int)) =
      (unsigned int)thePatchSize;
  }

private:
  bool myHasPatches;

public:
  DEFINE_STANDARD_RTTI_INLINE(Select3D_BVHIndexBuffer, Graphic3d_Buffer)
};

#endif

#include <TColStd_HPackedMapOfInteger.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Shared.hpp>

class Select3D_SensitivePrimitiveArray : public Select3D_SensitiveSet
{

public:
  Standard_EXPORT Select3D_SensitivePrimitiveArray(
    const occ::handle<SelectMgr_EntityOwner>& theOwnerId);

  int PatchSizeMax() const { return myPatchSizeMax; }

  void SetPatchSizeMax(const int thePatchSizeMax) { myPatchSizeMax = thePatchSizeMax; }

  float PatchDistance() const { return myPatchDistance; }

  void SetPatchDistance(const float thePatchDistMax) { myPatchDistance = thePatchDistMax; }

  Standard_EXPORT bool InitTriangulation(const occ::handle<Graphic3d_Buffer>&      theVerts,
                                         const occ::handle<Graphic3d_IndexBuffer>& theIndices,
                                         const TopLoc_Location&                    theInitLoc,
                                         const int                                 theIndexLower,
                                         const int                                 theIndexUpper,
                                         const bool theToEvalMinMax = true,
                                         const int  theNbGroups     = 1);

  bool InitTriangulation(const occ::handle<Graphic3d_Buffer>&      theVerts,
                         const occ::handle<Graphic3d_IndexBuffer>& theIndices,
                         const TopLoc_Location&                    theInitLoc,
                         const bool                                theToEvalMinMax = true,
                         const int                                 theNbGroups     = 1)
  {
    const int anUpper = !theIndices.IsNull()
                          ? (theIndices->NbElements - 1)
                          : (!theVerts.IsNull() ? (theVerts->NbElements - 1) : 0);
    return InitTriangulation(theVerts,
                             theIndices,
                             theInitLoc,
                             0,
                             anUpper,
                             theToEvalMinMax,
                             theNbGroups);
  }

  Standard_EXPORT bool InitPoints(const occ::handle<Graphic3d_Buffer>&      theVerts,
                                  const occ::handle<Graphic3d_IndexBuffer>& theIndices,
                                  const TopLoc_Location&                    theInitLoc,
                                  const int                                 theIndexLower,
                                  const int                                 theIndexUpper,
                                  const bool                                theToEvalMinMax = true,
                                  const int                                 theNbGroups     = 1);

  bool InitPoints(const occ::handle<Graphic3d_Buffer>&      theVerts,
                  const occ::handle<Graphic3d_IndexBuffer>& theIndices,
                  const TopLoc_Location&                    theInitLoc,
                  const bool                                theToEvalMinMax = true,
                  const int                                 theNbGroups     = 1)
  {
    const int anUpper = !theIndices.IsNull()
                          ? (theIndices->NbElements - 1)
                          : (!theVerts.IsNull() ? (theVerts->NbElements - 1) : 0);
    return InitPoints(theVerts, theIndices, theInitLoc, 0, anUpper, theToEvalMinMax, theNbGroups);
  }

  bool InitPoints(const occ::handle<Graphic3d_Buffer>& theVerts,
                  const TopLoc_Location&               theInitLoc,
                  const bool                           theToEvalMinMax = true,
                  const int                            theNbGroups     = 1)
  {
    const int anUpper = !theVerts.IsNull() ? (theVerts->NbElements - 1) : 0;
    return InitPoints(theVerts,
                      occ::handle<Graphic3d_IndexBuffer>(),
                      theInitLoc,
                      0,
                      anUpper,
                      theToEvalMinMax,
                      theNbGroups);
  }

  void SetMinMax(double theMinX,
                 double theMinY,
                 double theMinZ,
                 double theMaxX,
                 double theMaxY,
                 double theMaxZ)
  {
    myBndBox = Select3D_BndBox3d(NCollection_Vec3<double>(theMinX, theMinY, theMinZ),
                                 NCollection_Vec3<double>(theMaxX, theMaxY, theMaxZ));
    if (!myGroups.IsNull())
    {
      for (Select3D_PrimArraySubGroupArray::Iterator aGroupIter(*myGroups); aGroupIter.More();
           aGroupIter.Next())
      {
        aGroupIter.Value()->myBndBox = myBndBox;
      }
    }
  }

  bool ToDetectElements() const { return myToDetectElem; }

  void SetDetectElements(bool theToDetect) { myToDetectElem = theToDetect; }

  bool ToDetectElementMap() const { return !myDetectedElemMap.IsNull(); }

  Standard_EXPORT void SetDetectElementMap(bool theToDetect);

  bool ToDetectNodes() const { return myToDetectNode; }

  void SetDetectNodes(bool theToDetect) { myToDetectNode = theToDetect; }

  bool ToDetectNodeMap() const { return !myDetectedNodeMap.IsNull(); }

  Standard_EXPORT void SetDetectNodeMap(bool theToDetect);

  bool ToDetectEdges() const { return myToDetectEdge; }

  void SetDetectEdges(bool theToDetect) { myToDetectEdge = theToDetect; }

  int LastDetectedElement() const { return myDetectedElem; }

  const occ::handle<TColStd_HPackedMapOfInteger>& LastDetectedElementMap() const
  {
    return myDetectedElemMap;
  }

  int LastDetectedNode() const { return myDetectedNode; }

  const occ::handle<TColStd_HPackedMapOfInteger>& LastDetectedNodeMap() const
  {
    return myDetectedNodeMap;
  }

  int LastDetectedEdgeNode1() const { return myDetectedEdgeNode1; }

  int LastDetectedEdgeNode2() const { return myDetectedEdgeNode2; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

public:
  Standard_EXPORT bool Matches(SelectBasics_SelectingVolumeManager& theMgr,
                               SelectBasics_PickResult&             thePickResult) override;

  Standard_EXPORT occ::handle<Select3D_SensitiveEntity> GetConnected() override;

  Standard_EXPORT int Size() const override;

  int NbSubElements() const override
  {
    return !myGroups.IsNull() ? myGroups->Size() : myBvhIndices.NbElements;
  }

  Standard_EXPORT Select3D_BndBox3d Box(const int theIdx) const override;

  Standard_EXPORT double Center(const int theIdx, const int theAxis) const override;

  Standard_EXPORT void Swap(const int theIdx1, const int theIdx2) override;

  Standard_EXPORT Select3D_BndBox3d BoundingBox() override;

  gp_Pnt CenterOfGeometry() const override { return myCDG3D; }

  bool HasInitLocation() const override { return !myInitLocation.IsIdentity(); }

  gp_GTrsf InvInitLocation() const override { return myInvInitLocation; }

  Standard_EXPORT void Set(const occ::handle<SelectMgr_EntityOwner>& theOwnerId) override;

  Standard_EXPORT void BVH() override;

protected:
  Standard_EXPORT void computeBoundingBox();

  Standard_EXPORT Select3D_BndBox3d applyTransformation();

  const NCollection_Vec3<float>& getPosVec3(const int theIndex) const
  {
    return *reinterpret_cast<const NCollection_Vec3<float>*>(myPosData + myPosStride * theIndex);
  }

  const NCollection_Vec2<float>& getPosVec2(const int theIndex) const
  {
    return *reinterpret_cast<const NCollection_Vec2<float>*>(myPosData + myPosStride * theIndex);
  }

  Standard_EXPORT bool overlapsElement(SelectBasics_PickResult&             thePickResult,
                                       SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

  Standard_EXPORT double distanceToCOG(SelectBasics_SelectingVolumeManager& theMgr) override;

  Standard_EXPORT bool elementIsInside(SelectBasics_SelectingVolumeManager& theMgr,
                                       int                                  theElemIdx,
                                       bool theIsFullInside) override;

private:
  typedef NCollection_Shared<NCollection_Array1<occ::handle<Select3D_SensitivePrimitiveArray>>>
    Select3D_PrimArraySubGroupArray;
  struct Select3D_SensitivePrimitiveArray_InitFunctor;
  struct Select3D_SensitivePrimitiveArray_BVHFunctor;

private:
  occ::handle<Select3D_PrimArraySubGroupArray> myGroups;

  occ::handle<Graphic3d_Buffer>      myVerts;
  occ::handle<Graphic3d_IndexBuffer> myIndices;
  const uint8_t*                     myPosData;

  size_t                                   myPosStride;
  Graphic3d_TypeOfPrimitiveArray           myPrimType;
  int                                      myIndexLower;
  int                                      myIndexUpper;
  int                                      myPatchSizeMax;
  float                                    myPatchDistance;
  bool                                     myIs3d;
  TopLoc_Location                          myInitLocation;
  gp_Pnt                                   myCDG3D;
  Select3D_BVHIndexBuffer                  myBvhIndices;
  mutable Select3D_BndBox3d                myBndBox;
  gp_GTrsf                                 myInvInitLocation;
  occ::handle<TColStd_HPackedMapOfInteger> myDetectedElemMap;
  occ::handle<TColStd_HPackedMapOfInteger> myDetectedNodeMap;
  double                                   myMinDepthElem;
  double                                   myMinDepthNode;
  double                                   myMinDepthEdge;
  int                                      myDetectedElem;
  int                                      myDetectedNode;
  int                                      myDetectedEdgeNode1;
  int                                      myDetectedEdgeNode2;
  bool                                     myToDetectElem;
  bool                                     myToDetectNode;
  bool                                     myToDetectEdge;

public:
  DEFINE_STANDARD_RTTIEXT(Select3D_SensitivePrimitiveArray, Select3D_SensitiveSet)
};
