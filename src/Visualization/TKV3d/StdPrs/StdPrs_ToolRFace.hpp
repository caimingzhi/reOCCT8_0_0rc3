#pragma once


#include <BRepAdaptor_Surface.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Face.hpp>

class TopoDS_Edge;

//! Iterator over 2D curves restricting a face (skipping internal/external edges).
//! In addition, the algorithm skips NULL curves - IsInvalidGeometry() can be checked if this should
//! be handled within algorithm.
class StdPrs_ToolRFace
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  Standard_EXPORT StdPrs_ToolRFace();

  //! Constructor with initialization.
  Standard_EXPORT StdPrs_ToolRFace(const occ::handle<BRepAdaptor_Surface>& aSurface);

  //! Return TRUE indicating that iterator looks only for oriented edges.
  bool IsOriented() const { return true; }

  //! Move iterator to the first element.
  void Init()
  {
    myExplorer.Init(myFace, TopAbs_EDGE);
    next();
  }

  //! Return TRUE if iterator points to the curve.
  bool More() const { return myExplorer.More(); }

  //! Go to the next curve in the face.
  void Next()
  {
    myExplorer.Next();
    next();
  }

  //! Return current curve.
  const Adaptor2d_Curve2d& Value() const { return myCurve; }

  //! Return current edge.
  Standard_EXPORT const TopoDS_Edge& Edge() const;

  //! Return current edge orientation.
  TopAbs_Orientation Orientation() const { return myExplorer.Current().Orientation(); }

  //! Return TRUE if NULL curves have been skipped.
  bool IsInvalidGeometry() const { return myHasNullCurves; }

private:
  //! Find nearest valid item for the iterator.
  Standard_EXPORT void next();

private:
  TopoDS_Face         myFace;
  TopExp_Explorer     myExplorer;
  Geom2dAdaptor_Curve myCurve;
  bool                myHasNullCurves;
};

