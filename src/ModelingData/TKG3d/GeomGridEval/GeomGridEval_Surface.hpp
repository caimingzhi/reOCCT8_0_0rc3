#pragma once

#include <Adaptor3d_Surface.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <Geom_Surface.hpp>
#include <GeomGridEval_BSplineSurface.hpp>
#include <GeomGridEval_BezierSurface.hpp>
#include <GeomGridEval_Cone.hpp>
#include <GeomGridEval_Cylinder.hpp>
#include <GeomGridEval_OffsetSurface.hpp>
#include <GeomGridEval_OtherSurface.hpp>
#include <GeomGridEval_Plane.hpp>
#include <GeomGridEval_Sphere.hpp>
#include <GeomGridEval_SurfaceOfExtrusion.hpp>
#include <GeomGridEval_SurfaceOfRevolution.hpp>
#include <GeomGridEval_Torus.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <optional>
#include <variant>

class GeomGridEval_Surface
{
public:
  DEFINE_STANDARD_ALLOC

  using EvaluatorVariant = std::variant<std::monostate,
                                        GeomGridEval_Plane,
                                        GeomGridEval_Cylinder,
                                        GeomGridEval_Sphere,
                                        GeomGridEval_Cone,
                                        GeomGridEval_Torus,
                                        GeomGridEval_BezierSurface,
                                        GeomGridEval_BSplineSurface,
                                        GeomGridEval_OffsetSurface,
                                        GeomGridEval_SurfaceOfRevolution,
                                        GeomGridEval_SurfaceOfExtrusion,
                                        GeomGridEval_OtherSurface>;

  GeomGridEval_Surface()
      : myEvaluator(std::monostate{}),
        mySurfaceType(GeomAbs_OtherSurface)
  {
  }

  GeomGridEval_Surface(const GeomGridEval_Surface&)            = delete;
  GeomGridEval_Surface& operator=(const GeomGridEval_Surface&) = delete;
  GeomGridEval_Surface(GeomGridEval_Surface&&)                 = delete;
  GeomGridEval_Surface& operator=(GeomGridEval_Surface&&)      = delete;

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& theSurface);

  Standard_EXPORT void Initialize(const occ::handle<Geom_Surface>& theSurface);

  Standard_EXPORT bool IsInitialized() const;

  Standard_EXPORT NCollection_Array2<gp_Pnt> EvaluateGrid(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD1> EvaluateGridD1(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD2> EvaluateGridD2(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  Standard_EXPORT NCollection_Array2<GeomGridEval::SurfD3> EvaluateGridD3(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams) const;

  Standard_EXPORT NCollection_Array2<gp_Vec> EvaluateGridDN(
    const NCollection_Array1<double>& theUParams,
    const NCollection_Array1<double>& theVParams,
    int                               theNU,
    int                               theNV) const;

  Standard_EXPORT NCollection_Array1<gp_Pnt> EvaluatePoints(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  Standard_EXPORT NCollection_Array1<GeomGridEval::SurfD1> EvaluatePointsD1(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  Standard_EXPORT NCollection_Array1<GeomGridEval::SurfD2> EvaluatePointsD2(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  Standard_EXPORT NCollection_Array1<GeomGridEval::SurfD3> EvaluatePointsD3(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs) const;

  Standard_EXPORT NCollection_Array1<gp_Vec> EvaluatePointsDN(
    const NCollection_Array1<gp_Pnt2d>& theUVPairs,
    int                                 theNU,
    int                                 theNV) const;

  GeomAbs_SurfaceType GetType() const { return mySurfaceType; }

  bool HasTransformation() const { return myTrsf.has_value(); }

  const std::optional<gp_Trsf>& GetTransformation() const { return myTrsf; }

private:
  void applyTransformation(NCollection_Array2<gp_Pnt>& theGrid) const;

  void applyTransformation(NCollection_Array2<GeomGridEval::SurfD1>& theGrid) const;

  void applyTransformation(NCollection_Array2<GeomGridEval::SurfD2>& theGrid) const;

  void applyTransformation(NCollection_Array2<GeomGridEval::SurfD3>& theGrid) const;

  void applyTransformation(NCollection_Array2<gp_Vec>& theGrid) const;

  void applyTransformation(NCollection_Array1<gp_Pnt>& thePoints) const;

  void applyTransformation(NCollection_Array1<GeomGridEval::SurfD1>& thePoints) const;

  void applyTransformation(NCollection_Array1<GeomGridEval::SurfD2>& thePoints) const;

  void applyTransformation(NCollection_Array1<GeomGridEval::SurfD3>& thePoints) const;

  void applyTransformation(NCollection_Array1<gp_Vec>& thePoints) const;

  EvaluatorVariant       myEvaluator;
  GeomAbs_SurfaceType    mySurfaceType;
  std::optional<gp_Trsf> myTrsf;
};
