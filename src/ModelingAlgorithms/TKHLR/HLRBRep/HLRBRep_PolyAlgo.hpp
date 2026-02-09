#pragma once

#include <BRepAdaptor_Surface.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <GeomAbs_Shape.hpp>
#include <HLRAlgo_TriangleData.hpp>
#include <NCollection_Array1.hpp>
#include <HLRAlgo_PolyInternalSegment.hpp>
#include <HLRAlgo_PolyInternalNode.hpp>
#include <HLRAlgo_BiPoint.hpp>
#include <NCollection_List.hpp>
#include <HLRAlgo_PolyAlgo.hpp>
#include <HLRAlgo_Projector.hpp>
#include <Standard_Integer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Sequence.hpp>

class Geom_Surface;
class TopoDS_Edge;
class HLRAlgo_PolyInternalData;
class HLRAlgo_EdgeStatus;
struct HLRAlgo_TriangleData;

class HLRBRep_PolyAlgo : public Standard_Transient
{

public:
  Standard_EXPORT HLRBRep_PolyAlgo();

  Standard_EXPORT HLRBRep_PolyAlgo(const occ::handle<HLRBRep_PolyAlgo>& A);

  Standard_EXPORT HLRBRep_PolyAlgo(const TopoDS_Shape& S);

  int NbShapes() const { return myShapes.Length(); }

  Standard_EXPORT TopoDS_Shape& Shape(const int I);

  Standard_EXPORT void Remove(const int I);

  Standard_EXPORT int Index(const TopoDS_Shape& S) const;

  void Load(const TopoDS_Shape& theShape) { myShapes.Append(theShape); }

  const occ::handle<HLRAlgo_PolyAlgo>& Algo() const { return myAlgo; }

  const HLRAlgo_Projector& Projector() const { return myProj; }

  void Projector(const HLRAlgo_Projector& theProj) { myProj = theProj; }

  double TolAngular() const { return myTolAngular; }

  void TolAngular(const double theTol) { myTolAngular = theTol; }

  double TolCoef() const { return myTolSta; }

  void TolCoef(const double theTol)
  {
    myTolSta = theTol;
    myTolEnd = 1.0 - theTol;
  }

  Standard_EXPORT void Update();

  void InitHide() { myAlgo->InitHide(); }

  bool MoreHide() const { return myAlgo->MoreHide(); }

  void NextHide() { myAlgo->NextHide(); }

  Standard_EXPORT HLRAlgo_BiPoint::PointsT& Hide(HLRAlgo_EdgeStatus& status,
                                                 TopoDS_Shape&       S,
                                                 bool&               reg1,
                                                 bool&               regn,
                                                 bool&               outl,
                                                 bool&               intl);

  void InitShow() { myAlgo->InitShow(); }

  bool MoreShow() const { return myAlgo->MoreShow(); }

  void NextShow() { myAlgo->NextShow(); }

  Standard_EXPORT HLRAlgo_BiPoint::PointsT& Show(TopoDS_Shape& S,
                                                 bool&         reg1,
                                                 bool&         regn,
                                                 bool&         outl,
                                                 bool&         intl);

  Standard_EXPORT TopoDS_Shape OutLinedShape(const TopoDS_Shape& S) const;

  bool Debug() const { return myDebug; }

  void Debug(const bool theDebug) { myDebug = theDebug; }

  DEFINE_STANDARD_RTTIEXT(HLRBRep_PolyAlgo, Standard_Transient)

private:
  Standard_EXPORT TopoDS_Shape MakeShape() const;

  Standard_EXPORT int InitShape(const TopoDS_Shape& Shape, bool& IsoledF, bool& IsoledE);

  Standard_EXPORT void StoreShell(
    const TopoDS_Shape&                                        theShape,
    int&                                                       theIShell,
    NCollection_Array1<occ::handle<HLRAlgo_PolyShellData>>&    theShell,
    const bool                                                 theIsoledF,
    const bool                                                 theIsoledE,
    NCollection_Array1<int>&                                   theES,
    NCollection_Array1<occ::handle<HLRAlgo_PolyData>>&         thePD,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalData>>& thePID,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&    theShapeMap1,
    NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&    theShapeMap2);

  Standard_EXPORT bool Normal(const int                                        theINode,
                              HLRAlgo_PolyInternalNode::NodeIndices&           theNodIndices,
                              HLRAlgo_PolyInternalNode::NodeData&              theNod1RValues,
                              NCollection_Array1<HLRAlgo_TriangleData>&        theTData,
                              NCollection_Array1<HLRAlgo_PolyInternalSegment>& thePISeg,
                              NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>& thePINod,
                              const bool orient) const;

  Standard_EXPORT bool AverageNormal(
    const int                                                  theINode,
    HLRAlgo_PolyInternalNode::NodeIndices&                     theNodeIndices,
    NCollection_Array1<HLRAlgo_TriangleData>&                  theTData,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>&           thePISeg,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>& thePINod,
    double&                                                    theX,
    double&                                                    theY,
    double&                                                    theZ) const;

  bool AverageNormal(const int                                                  theINode,
                     HLRAlgo_PolyInternalNode::NodeIndices&                     theNodeIndices,
                     NCollection_Array1<HLRAlgo_TriangleData>&                  theTData,
                     NCollection_Array1<HLRAlgo_PolyInternalSegment>&           thePISeg,
                     NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>& thePINod,
                     gp_XYZ&                                                    theNormal) const
  {
    return AverageNormal(theINode,
                         theNodeIndices,
                         theTData,
                         thePISeg,
                         thePINod,
                         theNormal.ChangeCoord(1),
                         theNormal.ChangeCoord(2),
                         theNormal.ChangeCoord(3));
  }

  Standard_EXPORT void AddNormalOnTriangle(
    const int                                                  theITri,
    const int                                                  theINode,
    int&                                                       theJNode,
    NCollection_Array1<HLRAlgo_TriangleData>&                  theTData,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>& thePINod,
    double&                                                    theX,
    double&                                                    theY,
    double&                                                    theZ,
    bool&                                                      theOK) const;

  Standard_EXPORT void InitBiPointsWithConnexity(
    const int                                                  theIEdge,
    TopoDS_Edge&                                               theEdge,
    NCollection_List<HLRAlgo_BiPoint>&                         theList,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalData>>& thePID,
    NCollection_List<TopoDS_Shape>&                            theLS,
    const bool                                                 theIsConnex);

  Standard_EXPORT void Interpolation(
    NCollection_List<HLRAlgo_BiPoint>&                          List,
    double&                                                     X1,
    double&                                                     Y1,
    double&                                                     Z1,
    double&                                                     X2,
    double&                                                     Y2,
    double&                                                     Z2,
    double&                                                     XTI1,
    double&                                                     YTI1,
    double&                                                     ZTI1,
    double&                                                     XTI2,
    double&                                                     YTI2,
    double&                                                     ZTI2,
    const int                                                   e,
    double&                                                     U1,
    double&                                                     U2,
    HLRAlgo_PolyInternalNode::NodeIndices&                      theNodeIndices1,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod11RValues,
    HLRAlgo_PolyInternalNode::NodeIndices&                      theNodeIndices2,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod12RValues,
    const int                                                   i1p1,
    const int                                                   i1p2,
    const int                                                   i1,
    const occ::handle<HLRAlgo_PolyInternalData>&                pid1,
    NCollection_Array1<HLRAlgo_TriangleData>*&                  TData1,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>*&           PISeg1,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& PINod1) const;

  Standard_EXPORT void Interpolation(
    NCollection_List<HLRAlgo_BiPoint>&                          List,
    double&                                                     X1,
    double&                                                     Y1,
    double&                                                     Z1,
    double&                                                     X2,
    double&                                                     Y2,
    double&                                                     Z2,
    double&                                                     XTI1,
    double&                                                     YTI1,
    double&                                                     ZTI1,
    double&                                                     XTI2,
    double&                                                     YTI2,
    double&                                                     ZTI2,
    const int                                                   e,
    double&                                                     U1,
    double&                                                     U2,
    const GeomAbs_Shape                                         rg,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod11Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod11RValues,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod12Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod12RValues,
    const int                                                   i1p1,
    const int                                                   i1p2,
    const int                                                   i1,
    const occ::handle<HLRAlgo_PolyInternalData>&                pid1,
    NCollection_Array1<HLRAlgo_TriangleData>*&                  TData1,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>*&           PISeg1,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& PINod1,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod21Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod21RValues,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod22Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod22RValues,
    const int                                                   i2p1,
    const int                                                   i2p2,
    const int                                                   i2,
    const occ::handle<HLRAlgo_PolyInternalData>&                pid2,
    NCollection_Array1<HLRAlgo_TriangleData>*&                  TData2,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>*&           PISeg2,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& PINod2) const;

  Standard_EXPORT bool Interpolation(const double                        U1,
                                     const double                        U2,
                                     HLRAlgo_PolyInternalNode::NodeData& Nod1RValues,
                                     HLRAlgo_PolyInternalNode::NodeData& Nod2RValues,
                                     double&                             X3,
                                     double&                             Y3,
                                     double&                             Z3,
                                     double&                             XT3,
                                     double&                             YT3,
                                     double&                             ZT3,
                                     double&                             coef3,
                                     double&                             U3,
                                     bool&                               mP3P1) const;

  Standard_EXPORT void MoveOrInsertPoint(
    NCollection_List<HLRAlgo_BiPoint>&                          List,
    double&                                                     X1,
    double&                                                     Y1,
    double&                                                     Z1,
    double&                                                     X2,
    double&                                                     Y2,
    double&                                                     Z2,
    double&                                                     XTI1,
    double&                                                     YTI1,
    double&                                                     ZTI1,
    double&                                                     XTI2,
    double&                                                     YTI2,
    double&                                                     ZTI2,
    const int                                                   e,
    double&                                                     U1,
    double&                                                     U2,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod11Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod11RValues,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod12Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod12RValues,
    const int                                                   i1p1,
    const int                                                   i1p2,
    const int                                                   i1,
    const occ::handle<HLRAlgo_PolyInternalData>&                pid1,
    NCollection_Array1<HLRAlgo_TriangleData>*&                  TData1,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>*&           PISeg1,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& PINod1,
    const double                                                X3,
    const double                                                Y3,
    const double                                                Z3,
    const double                                                XT3,
    const double                                                YT3,
    const double                                                ZT3,
    const double                                                coef3,
    const double                                                U3,
    const bool                                                  insP3,
    const bool                                                  mP3P1,
    const int                                                   flag) const;

  Standard_EXPORT void MoveOrInsertPoint(
    NCollection_List<HLRAlgo_BiPoint>&                          List,
    double&                                                     X1,
    double&                                                     Y1,
    double&                                                     Z1,
    double&                                                     X2,
    double&                                                     Y2,
    double&                                                     Z2,
    double&                                                     XTI1,
    double&                                                     YTI1,
    double&                                                     ZTI1,
    double&                                                     XTI2,
    double&                                                     YTI2,
    double&                                                     ZTI2,
    const int                                                   e,
    double&                                                     U1,
    double&                                                     U2,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod11Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod11RValues,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod12Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod12RValues,
    const int                                                   i1p1,
    const int                                                   i1p2,
    const int                                                   i1,
    const occ::handle<HLRAlgo_PolyInternalData>&                pid1,
    NCollection_Array1<HLRAlgo_TriangleData>*&                  TData1,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>*&           PISeg1,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& PINod1,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod21Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod21RValues,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod22Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod22RValues,
    const int                                                   i2p1,
    const int                                                   i2p2,
    const int                                                   i2,
    const occ::handle<HLRAlgo_PolyInternalData>&                pid2,
    NCollection_Array1<HLRAlgo_TriangleData>*&                  TData2,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>*&           PISeg2,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& PINod2,
    const double                                                X3,
    const double                                                Y3,
    const double                                                Z3,
    const double                                                XT3,
    const double                                                YT3,
    const double                                                ZT3,
    const double                                                coef3,
    const double                                                U3,
    const bool                                                  insP3,
    const bool                                                  mP3P1,
    const int                                                   flag) const;

  Standard_EXPORT void MoveOrInsertPoint(
    NCollection_List<HLRAlgo_BiPoint>&                          List,
    double&                                                     X1,
    double&                                                     Y1,
    double&                                                     Z1,
    double&                                                     X2,
    double&                                                     Y2,
    double&                                                     Z2,
    double&                                                     XTI1,
    double&                                                     YTI1,
    double&                                                     ZTI1,
    double&                                                     XTI2,
    double&                                                     YTI2,
    double&                                                     ZTI2,
    const int                                                   e,
    double&                                                     U1,
    double&                                                     U2,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod11Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod11RValues,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod12Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod12RValues,
    const int                                                   i1p1,
    const int                                                   i1p2,
    const int                                                   i1,
    const occ::handle<HLRAlgo_PolyInternalData>&                pid1,
    NCollection_Array1<HLRAlgo_TriangleData>*&                  TData1,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>*&           PISeg1,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& PINod1,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod21Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod21RValues,
    HLRAlgo_PolyInternalNode::NodeIndices&                      Nod22Indices,
    HLRAlgo_PolyInternalNode::NodeData&                         Nod22RValues,
    const int                                                   i2p1,
    const int                                                   i2p2,
    const int                                                   i2,
    const occ::handle<HLRAlgo_PolyInternalData>&                pid2,
    NCollection_Array1<HLRAlgo_TriangleData>*&                  TData2,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>*&           PISeg2,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& PINod2,
    const double                                                X3,
    const double                                                Y3,
    const double                                                Z3,
    const double                                                XT3,
    const double                                                YT3,
    const double                                                ZT3,
    const double                                                coef3,
    const double                                                U3,
    const bool                                                  insP3,
    const bool                                                  mP3P1,
    const double                                                X4,
    const double                                                Y4,
    const double                                                Z4,
    const double                                                XT4,
    const double                                                YT4,
    const double                                                ZT4,
    const double                                                coef4,
    const double                                                U4,
    const bool                                                  insP4,
    const bool                                                  mP4P1,
    const int                                                   flag) const;

  Standard_EXPORT void InsertOnOutLine(
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalData>>& thePID);

  Standard_EXPORT void CheckFrBackTriangles(
    NCollection_List<HLRAlgo_BiPoint>&                         theList,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalData>>& thePID);

  Standard_EXPORT void FindEdgeOnTriangle(const HLRAlgo_TriangleData& theTriangle,
                                          const int                   ip1,
                                          const int                   ip2,
                                          int&                        jtrouv,
                                          bool&                       isDirect) const;

  Standard_EXPORT void ChangeNode(
    const int                                                  theIp1,
    const int                                                  theIp2,
    HLRAlgo_PolyInternalNode::NodeIndices&                     theNod1Indices,
    HLRAlgo_PolyInternalNode::NodeData&                        theNod1RValues,
    HLRAlgo_PolyInternalNode::NodeIndices&                     theNod2Indices,
    HLRAlgo_PolyInternalNode::NodeData&                        theNod2RValues,
    const double                                               theCoef1,
    const double                                               theX3,
    const double                                               theY3,
    const double                                               theZ3,
    const bool                                                 theIsFirst,
    NCollection_Array1<HLRAlgo_TriangleData>&                  theTData,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>&           thePISeg,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>& thePINod) const;

  Standard_EXPORT void UpdateAroundNode(
    const int                                                  theINode,
    HLRAlgo_PolyInternalNode::NodeIndices&                     theNodeIndices,
    NCollection_Array1<HLRAlgo_TriangleData>&                  theTData,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>&           thePISeg,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>& thePINod) const;

  Standard_EXPORT void OrientTriangle(const int                              iTri,
                                      HLRAlgo_TriangleData&                  theTriangle,
                                      HLRAlgo_PolyInternalNode::NodeIndices& theNodeIndices1,
                                      HLRAlgo_PolyInternalNode::NodeData&    Nod1RValues,
                                      HLRAlgo_PolyInternalNode::NodeIndices& theNodeIndices2,
                                      HLRAlgo_PolyInternalNode::NodeData&    Nod2RValues,
                                      HLRAlgo_PolyInternalNode::NodeIndices& theNodeIndices3,
                                      HLRAlgo_PolyInternalNode::NodeData&    Nod3RValues) const;

  Standard_EXPORT bool Triangles(const int                                         ip1,
                                 const int                                         ip2,
                                 HLRAlgo_PolyInternalNode::NodeIndices&            Nod1Indices,
                                 NCollection_Array1<HLRAlgo_PolyInternalSegment>*& PISeg,
                                 int&                                              iTri1,
                                 int&                                              iTri2) const;

  Standard_EXPORT bool NewNode(HLRAlgo_PolyInternalNode::NodeData& Nod1RValues,
                               HLRAlgo_PolyInternalNode::NodeData& Nod2RValues,
                               double&                             coef1,
                               bool&                               moveP1) const;

  Standard_EXPORT void UVNode(HLRAlgo_PolyInternalNode::NodeData& Nod1RValues,
                              HLRAlgo_PolyInternalNode::NodeData& Nod2RValues,
                              const double                        coef1,
                              double&                             U3,
                              double&                             V3) const;

  Standard_EXPORT void CheckDegeneratedSegment(
    HLRAlgo_PolyInternalNode::NodeIndices& Nod1Indices,
    HLRAlgo_PolyInternalNode::NodeData&    Nod1RValues,
    HLRAlgo_PolyInternalNode::NodeIndices& Nod2Indices,
    HLRAlgo_PolyInternalNode::NodeData&    Nod2RValues) const;

  Standard_EXPORT void UpdateOutLines(
    NCollection_List<HLRAlgo_BiPoint>&                         theList,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalData>>& thePID);

  Standard_EXPORT void UpdateEdgesBiPoints(
    NCollection_List<HLRAlgo_BiPoint>&                               theList,
    const NCollection_Array1<occ::handle<HLRAlgo_PolyInternalData>>& thePID,
    const bool                                                       theIsClosed);

  Standard_EXPORT void UpdatePolyData(
    NCollection_Array1<occ::handle<HLRAlgo_PolyData>>&         thePD,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalData>>& thePID,
    const bool                                                 theClosed);

  Standard_EXPORT void TMultiply(double&    X,
                                 double&    Y,
                                 double&    Z,
                                 const bool VecPartOnly = false) const;

  void TMultiply(gp_XYZ& thePoint, const bool VecPartOnly = false) const
  {
    TMultiply(thePoint.ChangeCoord(1),
              thePoint.ChangeCoord(2),
              thePoint.ChangeCoord(3),
              VecPartOnly);
  }

  Standard_EXPORT void TTMultiply(double&    X,
                                  double&    Y,
                                  double&    Z,
                                  const bool VecPartOnly = false) const;

  void TTMultiply(gp_XYZ& thePoint, const bool VecPartOnly = false) const
  {
    TTMultiply(thePoint.ChangeCoord(1),
               thePoint.ChangeCoord(2),
               thePoint.ChangeCoord(3),
               VecPartOnly);
  }

  Standard_EXPORT void TIMultiply(double&    X,
                                  double&    Y,
                                  double&    Z,
                                  const bool VecPartOnly = false) const;

  void TIMultiply(gp_XYZ& thePoint, const bool VecPartOnly = false) const
  {
    TIMultiply(thePoint.ChangeCoord(1),
               thePoint.ChangeCoord(2),
               thePoint.ChangeCoord(3),
               VecPartOnly);
  }

private:
  HLRAlgo_Projector                                             myProj;
  double                                                        TMat[3][3];
  double                                                        TLoc[3];
  double                                                        TTMa[3][3];
  double                                                        TTLo[3];
  double                                                        TIMa[3][3];
  double                                                        TILo[3];
  NCollection_Sequence<TopoDS_Shape>                            myShapes;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myEMap;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myFMap;
  occ::handle<HLRAlgo_PolyAlgo>                                 myAlgo;
  bool                                                          myDebug;
  double                                                        myTolSta;
  double                                                        myTolEnd;
  double                                                        myTolAngular;
  occ::handle<Geom_Surface>                                     myGSurf;
  BRepAdaptor_Surface                                           myBSurf;
  BRepAdaptor_Curve                                             myBCurv;
  BRepAdaptor_Curve2d                                           myPC;
};
