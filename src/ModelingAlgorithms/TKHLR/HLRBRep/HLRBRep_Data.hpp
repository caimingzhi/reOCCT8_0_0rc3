#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <HLRBRep_EdgeData.hpp>
#include <NCollection_Array1.hpp>
#include <HLRBRep_FaceData.hpp>
#include <Standard_ShortReal.hpp>
#include <HLRAlgo_Projector.hpp>
#include <HLRBRep_CLProps.hpp>
#include <HLRBRep_SLProps.hpp>
#include <Standard_Real.hpp>
#include <HLRBRep_FaceIterator.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <Standard_Boolean.hpp>
#include <GeomAbs_CurveType.hpp>
#include <TopAbs_Orientation.hpp>
#include <HLRBRep_Intersector.hpp>
#include <HLRAlgo_Interference.hpp>
#include <Standard_Transient.hpp>
#include <TopoDS_Shape.hpp>
#include <BRepTopAdaptor_Tool.hpp>
#include <NCollection_DataMap.hpp>
#include <TopAbs_State.hpp>
#include <NCollection_List.hpp>
class BRepTopAdaptor_TopolTool;
class gp_Dir2d;
class HLRBRep_EdgeData;
class HLRBRep_FaceData;
class HLRBRep_Surface;
class IntRes2d_IntersectionPoint;
class TableauRejection;

class HLRBRep_Data : public Standard_Transient
{

public:
  Standard_EXPORT HLRBRep_Data(const int NV, const int NE, const int NF);

  Standard_EXPORT void Write(const occ::handle<HLRBRep_Data>& DS,
                             const int                        dv,
                             const int                        de,
                             const int                        df);

  NCollection_Array1<HLRBRep_EdgeData>& EDataArray();

  NCollection_Array1<HLRBRep_FaceData>& FDataArray();

  void Tolerance(const float tol);

  float Tolerance() const;

  Standard_EXPORT void Update(const HLRAlgo_Projector& P);

  HLRAlgo_Projector& Projector();

  int NbVertices() const;

  int NbEdges() const;

  int NbFaces() const;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& EdgeMap();

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& FaceMap();

  Standard_EXPORT void InitBoundSort(const HLRAlgo_EdgesBlock::MinMaxIndices& MinMaxTot,
                                     const int                                e1,
                                     const int                                e2);

  Standard_EXPORT void InitEdge(
    const int                                                                        FI,
    NCollection_DataMap<TopoDS_Shape, BRepTopAdaptor_Tool, TopTools_ShapeMapHasher>& MST);

  Standard_EXPORT bool MoreEdge();

  Standard_EXPORT void NextEdge(const bool skip = true);

  Standard_EXPORT int Edge() const;

  bool HidingTheFace() const;

  bool SimpleHidingFace() const;

  Standard_EXPORT void InitInterference();

  bool MoreInterference() const;

  Standard_EXPORT void NextInterference();

  Standard_EXPORT bool RejectedInterference();

  Standard_EXPORT bool AboveInterference();

  HLRAlgo_Interference& Interference();

  Standard_EXPORT void LocalLEGeometry2D(const double Param,
                                         gp_Dir2d&    Tg,
                                         gp_Dir2d&    Nm,
                                         double&      Cu);

  Standard_EXPORT void LocalFEGeometry2D(const int    FE,
                                         const double Param,
                                         gp_Dir2d&    Tg,
                                         gp_Dir2d&    Nm,
                                         double&      Cu);

  Standard_EXPORT void EdgeState(const double  p1,
                                 const double  p2,
                                 TopAbs_State& stbef,
                                 TopAbs_State& staf);

  bool EdgeOfTheHidingFace(const int E, const HLRBRep_EdgeData& ED) const;

  Standard_EXPORT int HidingStartLevel(const int                                     E,
                                       const HLRBRep_EdgeData&                       ED,
                                       const NCollection_List<HLRAlgo_Interference>& IL);

  Standard_EXPORT TopAbs_State Compare(const int E, const HLRBRep_EdgeData& ED);

  Standard_EXPORT TopAbs_State SimplClassify(const int               E,
                                             const HLRBRep_EdgeData& ED,
                                             const int               Nbp,
                                             const double            p1,
                                             const double            p2);

  Standard_EXPORT TopAbs_State Classify(const int               E,
                                        const HLRBRep_EdgeData& ED,
                                        const bool              LevelFlag,
                                        int&                    Level,
                                        const double            param);

  Standard_EXPORT bool IsBadFace() const;

  Standard_EXPORT void Destroy();

  ~HLRBRep_Data() override { Destroy(); }

  DEFINE_STANDARD_RTTIEXT(HLRBRep_Data, Standard_Transient)

private:
  Standard_EXPORT bool OrientOutLine(const int I, HLRBRep_FaceData& FD);

  Standard_EXPORT void OrientOthEdge(const int I, HLRBRep_FaceData& FD);

  Standard_EXPORT bool RejectedPoint(const IntRes2d_IntersectionPoint& PInter,
                                     const TopAbs_Orientation          BoundOri,
                                     const int                         NumSeg);

  Standard_EXPORT bool SameVertex(const bool head1, const bool head2);

private:
  int                                                           myNbVertices;
  int                                                           myNbEdges;
  int                                                           myNbFaces;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myEMap;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myFMap;
  NCollection_Array1<HLRBRep_EdgeData>                          myEData;
  NCollection_Array1<HLRBRep_FaceData>                          myFData;
  NCollection_Array1<int>                                       myEdgeIndices;
  float                                                         myToler;
  HLRAlgo_Projector                                             myProj;
  HLRBRep_CLProps                                               myLLProps;
  HLRBRep_CLProps                                               myFLProps;
  HLRBRep_SLProps                                               mySLProps;
  double                                                        myBigSize;
  HLRBRep_FaceIterator                                          myFaceItr1;
  HLRBRep_FaceIterator                                          myFaceItr2;
  int                                                           iFace;
  HLRBRep_FaceData*                                             iFaceData;
  HLRBRep_Surface*                                              iFaceGeom;
  HLRAlgo_EdgesBlock::MinMaxIndices*                            iFaceMinMax;
  GeomAbs_SurfaceType                                           iFaceType;
  bool                                                          iFaceBack;
  bool                                                          iFaceSimp;
  bool                                                          iFaceSmpl;
  bool                                                          iFaceTest;
  int                                                           myHideCount;
  double                                                        myDeca[16];
  double                                                        mySurD[16];
  int                                                           myCurSortEd;
  int                                                           myNbrSortEd;
  int                                                           myLE;
  bool                                                          myLEOutLine;
  bool                                                          myLEInternal;
  bool                                                          myLEDouble;
  bool                                                          myLEIsoLine;
  HLRBRep_EdgeData*                                             myLEData;
  const HLRBRep_Curve*                                          myLEGeom;
  HLRAlgo_EdgesBlock::MinMaxIndices*                            myLEMinMax;
  GeomAbs_CurveType                                             myLEType;
  float                                                         myLETol;
  int                                                           myFE;
  TopAbs_Orientation                                            myFEOri;
  bool                                                          myFEOutLine;
  bool                                                          myFEInternal;
  bool                                                          myFEDouble;
  HLRBRep_EdgeData*                                             myFEData;
  HLRBRep_Curve*                                                myFEGeom;
  GeomAbs_CurveType                                             myFEType;
  float                                                         myFETol;
  HLRBRep_Intersector                                           myIntersector;
  occ::handle<BRepTopAdaptor_TopolTool>                         myClassifier;
  bool                                                          mySameVertex;
  bool                                                          myIntersected;
  int                                                           myNbPoints;
  int                                                           myNbSegments;
  int                                                           iInterf;
  HLRAlgo_Interference                                          myIntf;
  bool                                                          myAboveIntf;
  TableauRejection*                                             myReject;
};

inline NCollection_Array1<HLRBRep_EdgeData>& HLRBRep_Data::EDataArray()
{
  return myEData;
}

inline NCollection_Array1<HLRBRep_FaceData>& HLRBRep_Data::FDataArray()
{
  return myFData;
}

inline void HLRBRep_Data::Tolerance(const float tol)
{
  myToler = tol;
}

inline float HLRBRep_Data::Tolerance() const
{
  return myToler;
}

inline HLRAlgo_Projector& HLRBRep_Data::Projector()
{
  return myProj;
}

inline int HLRBRep_Data::NbVertices() const
{
  return myNbVertices;
}

inline int HLRBRep_Data::NbEdges() const
{
  return myNbEdges;
}

inline int HLRBRep_Data::NbFaces() const
{
  return myNbFaces;
}

inline NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& HLRBRep_Data::EdgeMap()
{
  return myEMap;
}

inline NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& HLRBRep_Data::FaceMap()
{
  return myFMap;
}

inline bool HLRBRep_Data::SimpleHidingFace() const
{
  return iFaceSimp;
}

inline bool HLRBRep_Data::HidingTheFace() const
{
  return iFaceTest;
}

inline bool HLRBRep_Data::MoreInterference() const
{
  return (iInterf <= myNbPoints + 2 * myNbSegments);
}

inline HLRAlgo_Interference& HLRBRep_Data::Interference()
{
  return myIntf;
}

inline bool HLRBRep_Data::EdgeOfTheHidingFace(const int, const HLRBRep_EdgeData& ED) const
{
  return ED.HideCount() == myHideCount - 1;
}
