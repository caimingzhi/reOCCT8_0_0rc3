#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_Orientation.hpp>

class TopOpeBRep_FacesIntersector;
typedef TopOpeBRep_FacesIntersector* TopOpeBRep_PFacesIntersector;

#include <TopOpeBRepDS_PDataStructure.hpp>
#include <Standard_Integer.hpp>
#include <TopOpeBRep_PLineInter.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopOpeBRep_PointClassifier.hpp>
#include <TopOpeBRepTool_PShapeClassifier.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopAbs_State.hpp>
class TopOpeBRepDS_HDataStructure;
class TopOpeBRep_FFDumper;
class TopoDS_Shape;
class TopOpeBRep_VPointInter;
class TopOpeBRep_VPointInterClassifier;
class TopOpeBRep_VPointInterIterator;
class TopOpeBRepDS_Interference;
class TopOpeBRepDS_Point;
class gp_Pnt;

class TopOpeBRep_FacesFiller
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_FacesFiller();

  Standard_EXPORT void Insert(const TopoDS_Shape&                             F1,
                              const TopoDS_Shape&                             F2,
                              TopOpeBRep_FacesIntersector&                    FACINT,
                              const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT void ProcessSectionEdges();

  Standard_EXPORT TopOpeBRep_PointClassifier& ChangePointClassifier();

  Standard_EXPORT TopOpeBRepTool_PShapeClassifier PShapeClassifier() const;

  Standard_EXPORT void SetPShapeClassifier(const TopOpeBRepTool_PShapeClassifier& PSC);

  Standard_EXPORT void LoadLine(TopOpeBRep_LineInter& L);

  Standard_EXPORT bool CheckLine(TopOpeBRep_LineInter& L) const;

  Standard_EXPORT void VP_Position(TopOpeBRep_FacesIntersector& FACINT);

  Standard_EXPORT void VP_Position(TopOpeBRep_LineInter& L);

  Standard_EXPORT void VP_PositionOnL(TopOpeBRep_LineInter& L);

  Standard_EXPORT void VP_PositionOnR(TopOpeBRep_LineInter& L);

  Standard_EXPORT void VP_Position(TopOpeBRep_VPointInter&           VP,
                                   TopOpeBRep_VPointInterClassifier& VPC);

  Standard_EXPORT void ProcessLine();

  Standard_EXPORT void ResetDSC();

  Standard_EXPORT void ProcessRLine();

  Standard_EXPORT void FillLineVPonR();

  Standard_EXPORT void FillLine();

  Standard_EXPORT void AddShapesLine();

  Standard_EXPORT void GetESL(NCollection_List<TopoDS_Shape>& LES);

  Standard_EXPORT void ProcessVPR(TopOpeBRep_FacesFiller& FF, const TopOpeBRep_VPointInter& VP);

  Standard_EXPORT void ProcessVPIonR(TopOpeBRep_VPointInterIterator& VPI,
                                     const TopOpeBRepDS_Transition&  trans1,
                                     const TopoDS_Shape&             F1,
                                     const int                       ShapeIndex);

  Standard_EXPORT void ProcessVPonR(const TopOpeBRep_VPointInter&  VP,
                                    const TopOpeBRepDS_Transition& trans1,
                                    const TopoDS_Shape&            F1,
                                    const int                      ShapeIndex);

  Standard_EXPORT void ProcessVPonclosingR(const TopOpeBRep_VPointInter&                 VP,
                                           const TopoDS_Shape&                           F1,
                                           const int                                     ShapeIndex,
                                           const TopOpeBRepDS_Transition&                transEdge,
                                           const TopOpeBRepDS_Kind                       PVKind,
                                           const int                                     PVIndex,
                                           const bool                                    EPIfound,
                                           const occ::handle<TopOpeBRepDS_Interference>& IEPI);

  Standard_EXPORT bool ProcessVPondgE(const TopOpeBRep_VPointInter&           VP,
                                      const int                               ShapeIndex,
                                      TopOpeBRepDS_Kind&                      PVKind,
                                      int&                                    PVIndex,
                                      bool&                                   EPIfound,
                                      occ::handle<TopOpeBRepDS_Interference>& IEPI,
                                      bool&                                   CPIfound,
                                      occ::handle<TopOpeBRepDS_Interference>& ICPI);

  Standard_EXPORT void ProcessVPInotonR(TopOpeBRep_VPointInterIterator& VPI);

  Standard_EXPORT void ProcessVPnotonR(const TopOpeBRep_VPointInter& VP);

  Standard_EXPORT bool GetGeometry(
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator& IT,
    const TopOpeBRep_VPointInter&                                       VP,
    int&                                                                G,
    TopOpeBRepDS_Kind&                                                  K);

  Standard_EXPORT int MakeGeometry(const TopOpeBRep_VPointInter& VP,
                                   const int                     ShapeIndex,
                                   TopOpeBRepDS_Kind&            K);

  Standard_EXPORT void StoreCurveInterference(const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT bool GetFFGeometry(const TopOpeBRepDS_Point& DSP,
                                     TopOpeBRepDS_Kind&        K,
                                     int&                      G) const;

  Standard_EXPORT bool GetFFGeometry(const TopOpeBRep_VPointInter& VP,
                                     TopOpeBRepDS_Kind&            K,
                                     int&                          G) const;

  Standard_EXPORT TopOpeBRep_FacesIntersector& ChangeFacesIntersector();

  Standard_EXPORT occ::handle<TopOpeBRepDS_HDataStructure> HDataStructure();

  Standard_EXPORT TopOpeBRepDS_DataStructure& ChangeDataStructure();

  Standard_EXPORT const TopoDS_Face& Face(const int I) const;

  Standard_EXPORT const TopOpeBRepDS_Transition& FaceFaceTransition(const TopOpeBRep_LineInter& L,
                                                                    const int I) const;

  Standard_EXPORT const TopOpeBRepDS_Transition& FaceFaceTransition(const int I) const;

  Standard_EXPORT TopOpeBRep_PFacesIntersector PFacesIntersectorDummy() const;

  Standard_EXPORT TopOpeBRepDS_PDataStructure PDataStructureDummy() const;

  Standard_EXPORT TopOpeBRep_PLineInter PLineInterDummy() const;

  Standard_EXPORT void SetTraceIndex(const int exF1, const int exF2);

  Standard_EXPORT void GetTraceIndex(int& exF1, int& exF2) const;

  Standard_EXPORT static void Lminmax(const TopOpeBRep_LineInter& L, double& pmin, double& pmax);

  Standard_EXPORT static bool LSameDomainERL(const TopOpeBRep_LineInter&           L,
                                             const NCollection_List<TopoDS_Shape>& ERL);

  Standard_EXPORT static bool IsVPtransLok(const TopOpeBRep_LineInter& L,
                                           const int                   iVP,
                                           const int                   SI12,
                                           TopOpeBRepDS_Transition&    T);

  Standard_EXPORT static bool TransvpOK(const TopOpeBRep_LineInter& L,
                                        const int                   iVP,
                                        const int                   SI,
                                        const bool                  isINOUT);

  Standard_EXPORT static double VPParamOnER(const TopOpeBRep_VPointInter& vp,
                                            const TopOpeBRep_LineInter&   Lrest);

  Standard_EXPORT static bool EqualpPonR(const TopOpeBRep_LineInter&   Lrest,
                                         const TopOpeBRep_VPointInter& VP1,
                                         const TopOpeBRep_VPointInter& VP2);

private:
  Standard_EXPORT bool KeepRLine(const TopOpeBRep_LineInter& Lrest, const bool checkkeep) const;

  Standard_EXPORT TopOpeBRepDS_Transition GetEdgeTrans(const TopOpeBRep_VPointInter& VP,
                                                       const TopOpeBRepDS_Kind       PVKind,
                                                       const int                     PVIndex,
                                                       const int                     Sind,
                                                       const TopoDS_Face&            F);

  Standard_EXPORT TopAbs_State StateVPonFace(const TopOpeBRep_VPointInter& VP) const;

  Standard_EXPORT bool PequalVPonR(const gp_Pnt&           P3D,
                                   const int               VPshapeindex,
                                   TopOpeBRep_VPointInter& VP,
                                   TopOpeBRep_LineInter&   Lrest) const;

  Standard_EXPORT TopAbs_State StBipVPonF(const TopOpeBRep_VPointInter& IVPf,
                                          const TopOpeBRep_VPointInter& IVPl,
                                          const TopOpeBRep_LineInter&   Lrest,
                                          const bool                    isonedge1) const;

  TopoDS_Face                              myF1;
  TopoDS_Face                              myF2;
  TopAbs_Orientation                       myF1ori;
  TopAbs_Orientation                       myF2ori;
  TopOpeBRep_PFacesIntersector             myFacesIntersector;
  occ::handle<TopOpeBRepDS_HDataStructure> myHDS;
  TopOpeBRepDS_PDataStructure              myDS;
  int                                      myFFfirstDSP;
  TopOpeBRep_PLineInter                    myLine;
  bool                                     myLineOK;
  bool                                     myLineINL;
  TopOpeBRepDS_Transition                  myLineTonF1;
  TopOpeBRepDS_Transition                  myLineTonF2;
  bool                                     myLineIsonEdge;
  NCollection_List<TopoDS_Shape>           myERL;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
                                                           myDataforDegenEd;
  bool                                                     myLastVPison0;
  int                                                      mykeptVPnbr;
  int                                                      myDSCIndex;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> myDSCIL;
  TopOpeBRep_PointClassifier                               myPointClassifier;
  TopOpeBRepTool_PShapeClassifier                          myPShapeClassifier;
  int                                                      myexF1;
  int                                                      myexF2;
  occ::handle<TopOpeBRep_FFDumper>                         myHFFD;
};
