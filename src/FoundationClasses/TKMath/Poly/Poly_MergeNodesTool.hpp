#pragma once

#include <NCollection_Map.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard_HashUtils.hpp>

class Poly_MergeNodesTool : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Poly_MergeNodesTool, Standard_Transient)
public:
  Standard_EXPORT static occ::handle<Poly_Triangulation> MergeNodes(
    const occ::handle<Poly_Triangulation>& theTris,
    const gp_Trsf&                         theTrsf,
    const bool                             theToReverse,
    const double                           theSmoothAngle,
    const double                           theMergeTolerance = 0.0,
    const bool                             theToForce        = true);

public:
  Standard_EXPORT Poly_MergeNodesTool(const double theSmoothAngle,
                                      const double theMergeTolerance = 0.0,
                                      const int    theNbFacets       = -1);

  double MergeTolerance() const { return myNodeIndexMap.MergeTolerance(); }

  void SetMergeTolerance(double theTolerance) { myNodeIndexMap.SetMergeTolerance(theTolerance); }

  double MergeAngle() const { return myNodeIndexMap.MergeAngle(); }

  void SetMergeAngle(double theAngleRad) { myNodeIndexMap.SetMergeAngle(theAngleRad); }

  bool ToMergeOpposite() const { return myNodeIndexMap.ToMergeOpposite(); }

  void SetMergeOpposite(bool theToMerge) { myNodeIndexMap.SetMergeOpposite(theToMerge); }

  void SetUnitFactor(double theUnitFactor) { myUnitFactor = theUnitFactor; }

  bool ToDropDegenerative() const { return myToDropDegenerative; }

  void SetDropDegenerative(bool theToDrop) { myToDropDegenerative = theToDrop; }

  bool ToMergeElems() const { return myToMergeElems; }

  void SetMergeElems(bool theToMerge) { myToMergeElems = theToMerge; }

  NCollection_Vec3<float> computeTriNormal() const
  {
    const gp_XYZ            aVec01 = myPlaces[1] - myPlaces[0];
    const gp_XYZ            aVec02 = myPlaces[2] - myPlaces[0];
    const gp_XYZ            aCross = aVec01 ^ aVec02;
    NCollection_Vec3<float> aNorm((float)aCross.X(), (float)aCross.Y(), (float)aCross.Z());
    return aNorm.Normalized();
  }

public:
  Standard_EXPORT virtual void AddTriangulation(const occ::handle<Poly_Triangulation>& theTris,
                                                const gp_Trsf& theTrsf      = gp_Trsf(),
                                                const bool     theToReverse = false);

  Standard_EXPORT occ::handle<Poly_Triangulation> Result();

public:
  void AddTriangle(const gp_XYZ theElemNodes[3]) { AddElement(theElemNodes, 3); }

  void AddQuad(const gp_XYZ theElemNodes[4]) { AddElement(theElemNodes, 4); }

  Standard_EXPORT void AddElement(const gp_XYZ* theElemNodes, int theNbNodes);

  gp_XYZ& ChangeElementNode(int theIndex) { return myPlaces[theIndex]; }

  Standard_EXPORT void PushLastElement(int theNbNodes);

  void PushLastTriangle() { PushLastElement(3); }

  void PushLastQuad() { PushLastElement(4); }

  int ElementNodeIndex(int theIndex) const { return myNodeInds[theIndex]; }

  int NbNodes() const { return myNbNodes; }

  int NbElements() const { return myNbElems; }

  int NbDegenerativeElems() const { return myNbDegenElems; }

  int NbMergedElems() const { return myNbMergedElems; }

  occ::handle<Poly_Triangulation>& ChangeOutput() { return myPolyData; }

private:
  void pushNodeCheck(bool& theIsOpposite, const int theTriNode)
  {
    int                           aNodeIndex = myNbNodes;
    const gp_XYZ&                 aPlace     = myPlaces[theTriNode];
    const NCollection_Vec3<float> aVec3((float)aPlace.X(), (float)aPlace.Y(), (float)aPlace.Z());
    if (myNodeIndexMap.Bind(aNodeIndex, theIsOpposite, aVec3, myTriNormal))
    {
      ++myNbNodes;
      if (!myPolyData.IsNull())
      {
        if (myPolyData->NbNodes() < myNbNodes)
        {
          myPolyData->ResizeNodes(myNbNodes * 2, true);
        }
        myPolyData->SetNode(myNbNodes, aPlace * myUnitFactor);
      }
    }
    myNodeInds[theTriNode] = aNodeIndex;
  }

  inline void pushNodeNoMerge(const int theTriNode)
  {
    int          aNodeIndex = myNbNodes;
    const gp_XYZ aPlace     = myPlaces[theTriNode] * myUnitFactor;

    ++myNbNodes;
    if (!myPolyData.IsNull())
    {
      if (myPolyData->NbNodes() < myNbNodes)
      {
        myPolyData->ResizeNodes(myNbNodes * 2, true);
      }
      myPolyData->SetNode(myNbNodes, aPlace);
    }

    myNodeInds[theTriNode] = aNodeIndex;
  }

private:
  struct Vec3AndNormal
  {
    NCollection_Vec3<float> Pos;
    NCollection_Vec3<float> Norm;

    Vec3AndNormal(const NCollection_Vec3<float>& thePos, const NCollection_Vec3<float>& theNorm)
        : Pos(thePos),
          Norm(theNorm)
    {
    }
  };

  class MergedNodesMap : public NCollection_BaseMap
  {
  public:
    typedef NCollection_Vec3<int64_t> CellVec3i;

  public:
    Standard_EXPORT MergedNodesMap(const int theNbBuckets);

    double MergeAngle() const { return myAngle; }

    void SetMergeAngle(double theAngleRad)
    {
      myAngle    = (float)theAngleRad;
      myAngleCos = (float)std::cos(theAngleRad);
    }

    bool HasMergeAngle() const { return myAngle > 0.0f; }

    bool ToMergeAnyAngle() const { return myAngleCos <= 0.01f; }

    bool ToMergeOpposite() const { return myToMergeOpposite; }

    void SetMergeOpposite(bool theToMerge) { myToMergeOpposite = theToMerge; }

    double MergeTolerance() const { return myTolerance; }

    Standard_EXPORT void SetMergeTolerance(double theTolerance);

    bool HasMergeTolerance() const { return myTolerance > 0.0f; }

    Standard_EXPORT bool Bind(int&                           theIndex,
                              bool&                          theIsOpposite,
                              const NCollection_Vec3<float>& thePos,
                              const NCollection_Vec3<float>& theNorm);

    Standard_EXPORT void ReSize(const int theSize);

  private:
    CellVec3i vec3ToCell(const NCollection_Vec3<float>& thePnt) const
    {
      return CellVec3i(thePnt * myInvTol);
    }

    Standard_EXPORT static size_t vec3iHashCode(
      const Poly_MergeNodesTool::MergedNodesMap::CellVec3i& theVec,
      const int                                             theUpper);

    Standard_EXPORT size_t hashCode(const NCollection_Vec3<float>& thePos,
                                    const NCollection_Vec3<float>& theNorm,
                                    const int                      theUpper) const;

    size_t hashCode(const Vec3AndNormal& theKey, const int theUpper) const
    {
      return hashCode(theKey.Pos, theKey.Norm, theUpper);
    }

    Standard_EXPORT bool vec3AreEqual(const NCollection_Vec3<float>& theKey1,
                                      const NCollection_Vec3<float>& theKey2) const;

    Standard_EXPORT bool isEqual(const Vec3AndNormal&           theKey1,
                                 const NCollection_Vec3<float>& thePos2,
                                 const NCollection_Vec3<float>& theNorm2,
                                 bool&                          theIsOpposite) const;

  private:
    class DataMapNode;

  private:
    float myTolerance;
    float myInvTol;
    float myAngle;
    float myAngleCos;
    bool  myToMergeOpposite;
  };

  struct MergedElemHasher
  {
    size_t operator()(const NCollection_Vec4<int>& theVec) const
    {
      return opencascade::hashBytes(&theVec[0], 4 * sizeof(int));
    }

    bool operator()(const NCollection_Vec4<int>& theKey1,
                    const NCollection_Vec4<int>& theKey2) const
    {
      return theKey1.IsEqual(theKey2);
    }
  };

private:
  occ::handle<Poly_Triangulation>                          myPolyData;
  MergedNodesMap                                           myNodeIndexMap;
  NCollection_Map<NCollection_Vec4<int>, MergedElemHasher> myElemMap;
  NCollection_Vec4<int>                                    myNodeInds;
  NCollection_Vec3<float>                                  myTriNormal;
  gp_XYZ                                                   myPlaces[4];

  double myUnitFactor;
  int    myNbNodes;
  int    myNbElems;
  int    myNbDegenElems;
  int    myNbMergedElems;
  bool   myToDropDegenerative;
  bool   myToMergeElems;
};
