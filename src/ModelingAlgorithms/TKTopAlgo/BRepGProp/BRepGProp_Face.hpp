#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepAdaptor_Surface.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_IsoType.hpp>
#include <NCollection_HArray1.hpp>
class TopoDS_Face;
class gp_Pnt;
class gp_Vec;
class TopoDS_Edge;
class gp_Pnt2d;
class gp_Vec2d;

class BRepGProp_Face
{
public:
  DEFINE_STANDARD_ALLOC

  BRepGProp_Face(const bool IsUseSpan = false);

  BRepGProp_Face(const TopoDS_Face& F, const bool IsUseSpan = false);

  Standard_EXPORT void Load(const TopoDS_Face& F);

  Standard_EXPORT int VIntegrationOrder() const;

  bool NaturalRestriction() const;

  const TopoDS_Face& GetFace() const;

  gp_Pnt2d Value2d(const double U) const;

  Standard_EXPORT int SIntOrder(const double Eps) const;

  Standard_EXPORT int SVIntSubs() const;

  Standard_EXPORT int SUIntSubs() const;

  Standard_EXPORT void UKnots(NCollection_Array1<double>& Knots) const;

  Standard_EXPORT void VKnots(NCollection_Array1<double>& Knots) const;

  Standard_EXPORT int LIntOrder(const double Eps) const;

  Standard_EXPORT int LIntSubs() const;

  Standard_EXPORT void LKnots(NCollection_Array1<double>& Knots) const;

  Standard_EXPORT int UIntegrationOrder() const;

  Standard_EXPORT void Bounds(double& U1, double& U2, double& V1, double& V2) const;

  Standard_EXPORT void Normal(const double U, const double V, gp_Pnt& P, gp_Vec& VNor) const;

  Standard_EXPORT bool Load(const TopoDS_Edge& E);

  double FirstParameter() const;

  double LastParameter() const;

  Standard_EXPORT int IntegrationOrder() const;

  void D12d(const double U, gp_Pnt2d& P, gp_Vec2d& V1) const;

  Standard_EXPORT void Load(const bool IsFirstParam, const GeomAbs_IsoType theIsoType);

  Standard_EXPORT void GetUKnots(const double                              theUMin,
                                 const double                              theUMax,
                                 occ::handle<NCollection_HArray1<double>>& theUKnots) const;

  Standard_EXPORT void GetTKnots(const double                              theTMin,
                                 const double                              theTMax,
                                 occ::handle<NCollection_HArray1<double>>& theTKnots) const;

private:
  BRepAdaptor_Surface mySurface;
  Geom2dAdaptor_Curve myCurve;
  bool                mySReverse;
  bool                myIsUseSpan;
};

#include <BRep_Tool.hpp>

inline BRepGProp_Face::BRepGProp_Face(const bool IsUseSpan)
    : mySReverse(false),
      myIsUseSpan(IsUseSpan)
{
}

inline BRepGProp_Face::BRepGProp_Face(const TopoDS_Face& F, const bool IsUseSpan)
    : myIsUseSpan(IsUseSpan)
{
  Load(F);
}

inline bool BRepGProp_Face::NaturalRestriction() const
{
  return BRep_Tool::NaturalRestriction(mySurface.Face());
}

inline const TopoDS_Face& BRepGProp_Face::GetFace() const
{
  return mySurface.Face();
}

inline gp_Pnt2d BRepGProp_Face::Value2d(const double U) const
{
  return myCurve.Value(U);
}

inline void BRepGProp_Face::D12d(const double U, gp_Pnt2d& P, gp_Vec2d& V1) const
{
  myCurve.D1(U, P, V1);
}

inline double BRepGProp_Face::FirstParameter() const
{
  return myCurve.FirstParameter();
}

inline double BRepGProp_Face::LastParameter() const
{
  return myCurve.LastParameter();
}
