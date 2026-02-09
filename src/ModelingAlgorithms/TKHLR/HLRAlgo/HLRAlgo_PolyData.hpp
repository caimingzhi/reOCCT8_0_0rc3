#pragma once

#include <Bnd_Box.hpp>
#include <HLRAlgo_BiPoint.hpp>
#include <HLRAlgo_PolyHidingData.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <HLRAlgo_TriangleData.hpp>
#include <Standard.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <gp_XYZ.hpp>

class HLRAlgo_EdgeStatus;

class HLRAlgo_PolyData : public Standard_Transient
{

public:
  struct FaceIndices
  {

    FaceIndices()
        : Index(0),
          Min(0),
          Max(0)
    {
    }

    int Index, Min, Max;
  };

  struct Triangle
  {
    gp_XY  V1, V2, V3;
    double Param, TolParam, TolAng, Tolerance;
  };

  Standard_EXPORT HLRAlgo_PolyData();

  Standard_EXPORT void HNodes(const occ::handle<NCollection_HArray1<gp_XYZ>>& HNodes);

  Standard_EXPORT void HTData(const occ::handle<NCollection_HArray1<HLRAlgo_TriangleData>>& HTData);

  Standard_EXPORT void HPHDat(
    const occ::handle<NCollection_HArray1<HLRAlgo_PolyHidingData>>& HPHDat);

  void FaceIndex(const int I);

  int FaceIndex() const;

  NCollection_Array1<gp_XYZ>& Nodes() const;

  NCollection_Array1<HLRAlgo_TriangleData>& TData() const;

  NCollection_Array1<HLRAlgo_PolyHidingData>& PHDat() const;

  Standard_EXPORT void UpdateGlobalMinMax(Bnd_Box& theBox);

  bool Hiding() const;

  Standard_EXPORT void HideByPolyData(const HLRAlgo_BiPoint::PointsT& thePoints,
                                      Triangle&                       theTriangle,
                                      HLRAlgo_BiPoint::IndicesT&      theIndices,
                                      const bool                      HidingShell,
                                      HLRAlgo_EdgeStatus&             status);

  FaceIndices& Indices() { return myFaceIndices; }

  DEFINE_STANDARD_RTTIEXT(HLRAlgo_PolyData, Standard_Transient)

private:
  void hideByOneTriangle(const HLRAlgo_BiPoint::PointsT& thePoints,
                         Triangle&                       theTriangle,
                         const bool                      Crossing,
                         const bool                      HideBefore,
                         const int                       TrFlags,
                         HLRAlgo_EdgeStatus&             status);

  FaceIndices                                              myFaceIndices;
  occ::handle<NCollection_HArray1<gp_XYZ>>                 myHNodes;
  occ::handle<NCollection_HArray1<HLRAlgo_TriangleData>>   myHTData;
  occ::handle<NCollection_HArray1<HLRAlgo_PolyHidingData>> myHPHDat;
};

#include <gp_XYZ.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <HLRAlgo_TriangleData.hpp>
#include <HLRAlgo_PolyHidingData.hpp>

inline void HLRAlgo_PolyData::FaceIndex(const int I)
{
  myFaceIndices.Index = I;
}

inline int HLRAlgo_PolyData::FaceIndex() const
{
  return myFaceIndices.Index;
}

inline NCollection_Array1<gp_XYZ>& HLRAlgo_PolyData::Nodes() const
{
  return myHNodes->ChangeArray1();
}

inline NCollection_Array1<HLRAlgo_TriangleData>& HLRAlgo_PolyData::TData() const
{
  return myHTData->ChangeArray1();
}

inline NCollection_Array1<HLRAlgo_PolyHidingData>& HLRAlgo_PolyData::PHDat() const
{
  return myHPHDat->ChangeArray1();
}

inline bool HLRAlgo_PolyData::Hiding() const
{
  return !myHPHDat.IsNull();
}
