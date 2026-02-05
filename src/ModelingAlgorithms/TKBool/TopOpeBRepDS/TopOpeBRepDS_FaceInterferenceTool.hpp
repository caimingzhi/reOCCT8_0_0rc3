#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepDS_PDataStructure.hpp>
#include <TopAbs_Orientation.hpp>
#include <Standard_Integer.hpp>
#include <TopTrans_SurfaceTransition.hpp>
#include <TopoDS_Shape.hpp>
#include <gp_Pnt.hpp>
class TopOpeBRepDS_Interference;
class TopOpeBRepDS_Curve;

//! a tool computing complex transition on Face.
class TopOpeBRepDS_FaceInterferenceTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_FaceInterferenceTool(const TopOpeBRepDS_PDataStructure& P);

  //! Eisnew = true if E is a new edge built on edge I->Geometry()
  //! false if E is shape <=> I->Geometry()
  Standard_EXPORT void Init(const TopoDS_Shape&                           FI,
                            const TopoDS_Shape&                           E,
                            const bool                                    Eisnew,
                            const occ::handle<TopOpeBRepDS_Interference>& I);

  //! Eisnew = true if E is a new edge built on edge I->Geometry()
  //! false if E is shape <=> I->Geometry()
  Standard_EXPORT void Add(const TopoDS_Shape&                           FI,
                           const TopoDS_Shape&                           F,
                           const TopoDS_Shape&                           E,
                           const bool                                    Eisnew,
                           const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT void Add(const TopoDS_Shape&                           E,
                           const TopOpeBRepDS_Curve&                     C,
                           const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT void SetEdgePntPar(const gp_Pnt& P, const double par);

  Standard_EXPORT void GetEdgePntPar(gp_Pnt& P, double& par) const;

  Standard_EXPORT bool IsEdgePntParDef() const;

  Standard_EXPORT void Transition(const occ::handle<TopOpeBRepDS_Interference>& I) const;

private:
  TopOpeBRepDS_PDataStructure myPBDS;
  bool                        myrefdef;
  TopAbs_Orientation          myFaceOrientation;
  int                         myFaceOriented;
  TopTrans_SurfaceTransition  myTool;
  TopoDS_Shape                myEdge;
  bool                        isLine;
  gp_Pnt                      myPntOnEd;
  double                      myParOnEd;
  bool                        myOnEdDef;
  double                      myTole;
};
