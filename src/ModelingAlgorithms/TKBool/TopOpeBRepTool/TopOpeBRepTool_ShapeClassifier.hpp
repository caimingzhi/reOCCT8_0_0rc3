#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <TopOpeBRepTool_Plos.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopAbs_State.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <TopOpeBRepTool_SolidClassifier.hpp>
#include <NCollection_List.hpp>

class TopOpeBRepTool_ShapeClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_ShapeClassifier();

  Standard_EXPORT TopOpeBRepTool_ShapeClassifier(const TopoDS_Shape& SRef);

  Standard_EXPORT void ClearAll();

  Standard_EXPORT void ClearCurrent();

  Standard_EXPORT void SetReference(const TopoDS_Shape& SRef);

  Standard_EXPORT TopAbs_State StateShapeShape(const TopoDS_Shape& S,
                                               const TopoDS_Shape& SRef,
                                               const int           samedomain = 0);

  Standard_EXPORT int SameDomain() const;

  Standard_EXPORT void SameDomain(const int samedomain);

  Standard_EXPORT TopAbs_State StateShapeShape(const TopoDS_Shape& S,
                                               const TopoDS_Shape& AvoidS,
                                               const TopoDS_Shape& SRef);

  Standard_EXPORT TopAbs_State StateShapeShape(const TopoDS_Shape&                   S,
                                               const NCollection_List<TopoDS_Shape>& LAvoidS,
                                               const TopoDS_Shape&                   SRef);

  Standard_EXPORT TopAbs_State StateShapeReference(const TopoDS_Shape& S,
                                                   const TopoDS_Shape& AvoidS);

  Standard_EXPORT TopAbs_State StateShapeReference(const TopoDS_Shape&                   S,
                                                   const NCollection_List<TopoDS_Shape>& LAvoidS);

  Standard_EXPORT TopOpeBRepTool_SolidClassifier& ChangeSolidClassifier();

  Standard_EXPORT void StateP2DReference(const gp_Pnt2d& P2D);

  Standard_EXPORT void StateP3DReference(const gp_Pnt& P3D);

  Standard_EXPORT TopAbs_State State() const;

  Standard_EXPORT const gp_Pnt2d& P2D() const;

  Standard_EXPORT const gp_Pnt& P3D() const;

private:
  Standard_EXPORT void MapRef();

  Standard_EXPORT void FindEdge();

  Standard_EXPORT void FindEdge(const TopoDS_Shape& S);

  Standard_EXPORT void FindFace(const TopoDS_Shape& S);

  Standard_EXPORT void Perform();

  Standard_EXPORT void StateEdgeReference();

  Standard_EXPORT bool HasAvLS() const;

  TopoDS_Shape                                                  myS;
  TopoDS_Shape                                                  myRef;
  TopoDS_Shape                                                  myAvS;
  TopOpeBRepTool_Plos                                           myPAvLS;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myMapAvS;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> mymre;
  int                                                           mymren;
  bool                                                          mymredone;
  TopAbs_State                                                  myState;
  TopoDS_Edge                                                   myEdge;
  TopoDS_Face                                                   myFace;
  bool                                                          myP3Ddef;
  gp_Pnt                                                        myP3D;
  bool                                                          myP2Ddef;
  gp_Pnt2d                                                      myP2D;
  TopOpeBRepTool_SolidClassifier                                mySolidClassifier;
  int                                                           mySameDomain;
};
