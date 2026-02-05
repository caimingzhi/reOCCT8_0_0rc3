#pragma once

#include <BRepAdaptor_Surface.hpp>
#include <TopoDS_Shape.hpp>
#include <BRepTopAdaptor_TopolTool.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopAbs_State.hpp>

class BRepTopAdaptor_TopolTool;
class TopoDS_Face;
class gp_Pnt2d;

class TopOpeBRep_PointClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_PointClassifier();

  Standard_EXPORT void Init();

  Standard_EXPORT void Load(const TopoDS_Face& F);

  //! compute position of point <P> regarding with the face <F>.
  Standard_EXPORT TopAbs_State Classify(const TopoDS_Face& F, const gp_Pnt2d& P, const double Tol);

  Standard_EXPORT TopAbs_State State() const;

private:
  occ::handle<BRepTopAdaptor_TopolTool> myTopolTool;
  occ::handle<BRepAdaptor_Surface>      myHSurface;
  NCollection_DataMap<TopoDS_Shape, occ::handle<BRepTopAdaptor_TopolTool>, TopTools_ShapeMapHasher>
               myTopolToolMap;
  TopAbs_State myState;
};
