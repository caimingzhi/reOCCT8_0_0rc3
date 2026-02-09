#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

class BRepClass3d_SolidClassifier;
typedef BRepClass3d_SolidClassifier* TopOpeBRepTool_PSoClassif;

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopAbs_State.hpp>
#include <BRep_Builder.hpp>
class gp_Pnt;

class TopOpeBRepTool_SolidClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepTool_SolidClassifier();

  Standard_EXPORT void Clear();

  Standard_EXPORT ~TopOpeBRepTool_SolidClassifier();

  Standard_EXPORT void LoadSolid(const TopoDS_Solid& S);

  Standard_EXPORT TopAbs_State Classify(const TopoDS_Solid& S, const gp_Pnt& P, const double Tol);

  Standard_EXPORT void LoadShell(const TopoDS_Shell& S);

  Standard_EXPORT TopAbs_State Classify(const TopoDS_Shell& S, const gp_Pnt& P, const double Tol);

  Standard_EXPORT TopAbs_State State() const;

private:
  TopOpeBRepTool_PSoClassif                                                myPClassifier;
  NCollection_IndexedDataMap<TopoDS_Shape, void*, TopTools_ShapeMapHasher> myShapeClassifierMap;
  TopAbs_State                                                             myState;
  TopoDS_Shell                                                             myShell;
  TopoDS_Solid                                                             mySolid;
  BRep_Builder                                                             myBuilder;
};
