#pragma once

#include <BRepAdaptor_Surface.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Face.hpp>

class TopoDS_Edge;

class StdPrs_ToolRFace
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StdPrs_ToolRFace();

  Standard_EXPORT StdPrs_ToolRFace(const occ::handle<BRepAdaptor_Surface>& aSurface);

  bool IsOriented() const { return true; }

  void Init()
  {
    myExplorer.Init(myFace, TopAbs_EDGE);
    next();
  }

  bool More() const { return myExplorer.More(); }

  void Next()
  {
    myExplorer.Next();
    next();
  }

  const Adaptor2d_Curve2d& Value() const { return myCurve; }

  Standard_EXPORT const TopoDS_Edge& Edge() const;

  TopAbs_Orientation Orientation() const { return myExplorer.Current().Orientation(); }

  bool IsInvalidGeometry() const { return myHasNullCurves; }

private:
  Standard_EXPORT void next();

private:
  TopoDS_Face         myFace;
  TopExp_Explorer     myExplorer;
  Geom2dAdaptor_Curve myCurve;
  bool                myHasNullCurves;
};
