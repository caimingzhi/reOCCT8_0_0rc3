#pragma once

#include <GeomLib_CheckCurveOnSurface.hpp>

class BRepLib_CheckCurveOnSurface
{
public:
  DEFINE_STANDARD_ALLOC

  BRepLib_CheckCurveOnSurface()
      : myIsParallel(false)
  {
  }

  Standard_EXPORT BRepLib_CheckCurveOnSurface(const TopoDS_Edge& theEdge,
                                              const TopoDS_Face& theFace);

  Standard_EXPORT void Init(const TopoDS_Edge& theEdge, const TopoDS_Face& theFace);

  Standard_EXPORT void Perform();

  bool IsDone() const { return myCOnSurfGeom.ErrorStatus() == 0; }

  void SetParallel(const bool theIsParallel) { myIsParallel = theIsParallel; }

  bool IsParallel() { return myIsParallel; }

  int ErrorStatus() const { return myCOnSurfGeom.ErrorStatus(); }

  double MaxDistance() const { return myCOnSurfGeom.MaxDistance(); }

  double MaxParameter() const { return myCOnSurfGeom.MaxParameter(); }

protected:
  Standard_EXPORT void Compute(const occ::handle<Adaptor3d_CurveOnSurface>& theCurveOnSurface);

private:
  GeomLib_CheckCurveOnSurface           myCOnSurfGeom;
  occ::handle<Adaptor3d_CurveOnSurface> myAdaptorCurveOnSurface;
  occ::handle<Adaptor3d_CurveOnSurface> myAdaptorCurveOnSurface2;
  bool                                  myIsParallel;
};
