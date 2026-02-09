#pragma once

#include <Standard.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <GeomFill_TrihedronLaw.hpp>
#include <Standard_Real.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
class gp_Vec;

class GeomFill_Frenet : public GeomFill_TrihedronLaw
{

public:
  Standard_EXPORT GeomFill_Frenet();

  Standard_EXPORT occ::handle<GeomFill_TrihedronLaw> Copy() const override;

  Standard_EXPORT void Init();

  Standard_EXPORT bool SetCurve(const occ::handle<Adaptor3d_Curve>& C) override;

  Standard_EXPORT bool D0(const double Param,
                          gp_Vec&      Tangent,
                          gp_Vec&      Normal,
                          gp_Vec&      BiNormal) override;

  Standard_EXPORT bool D1(const double Param,
                          gp_Vec&      Tangent,
                          gp_Vec&      DTangent,
                          gp_Vec&      Normal,
                          gp_Vec&      DNormal,
                          gp_Vec&      BiNormal,
                          gp_Vec&      DBiNormal) override;

  Standard_EXPORT bool D2(const double Param,
                          gp_Vec&      Tangent,
                          gp_Vec&      DTangent,
                          gp_Vec&      D2Tangent,
                          gp_Vec&      Normal,
                          gp_Vec&      DNormal,
                          gp_Vec&      D2Normal,
                          gp_Vec&      BiNormal,
                          gp_Vec&      DBiNormal,
                          gp_Vec&      D2BiNormal) override;

  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  Standard_EXPORT void GetAverageLaw(gp_Vec& ATangent, gp_Vec& ANormal, gp_Vec& ABiNormal) override;

  Standard_EXPORT bool IsConstant() const override;

  Standard_EXPORT bool IsOnlyBy3dCurve() const override;

  DEFINE_STANDARD_RTTIEXT(GeomFill_Frenet, GeomFill_TrihedronLaw)

private:
  Standard_EXPORT bool IsSingular(const double U, int& Index) const;

  Standard_EXPORT bool DoSingular(const double U,
                                  const int    Index,
                                  gp_Vec&      Tangent,
                                  gp_Vec&      BiNormal,
                                  int&         n,
                                  int&         k,
                                  int&         TFlag,
                                  int&         BNFlag,
                                  double&      Delta);

  Standard_EXPORT bool SingularD0(const double Param,
                                  const int    Index,
                                  gp_Vec&      Tangent,
                                  gp_Vec&      Normal,
                                  gp_Vec&      BiNormal,
                                  double&      Delta);

  Standard_EXPORT bool SingularD1(const double Param,
                                  const int    Index,
                                  gp_Vec&      Tangent,
                                  gp_Vec&      DTangent,
                                  gp_Vec&      Normal,
                                  gp_Vec&      DNormal,
                                  gp_Vec&      BiNormal,
                                  gp_Vec&      DBiNormal,
                                  double&      Delta);

  Standard_EXPORT bool SingularD2(const double Param,
                                  const int    Index,
                                  gp_Vec&      Tangent,
                                  gp_Vec&      DTangent,
                                  gp_Vec&      D2Tangent,
                                  gp_Vec&      Normal,
                                  gp_Vec&      DNormal,
                                  gp_Vec&      D2Normal,
                                  gp_Vec&      BiNormal,
                                  gp_Vec&      DBiNormal,
                                  gp_Vec&      D2BiNormal,
                                  double&      Delta);

  Standard_EXPORT bool RotateTrihedron(gp_Vec&       Tangent,
                                       gp_Vec&       Normal,
                                       gp_Vec&       BiNormal,
                                       const gp_Vec& NewTangent) const;

  gp_Pnt                                   P;
  occ::handle<NCollection_HArray1<double>> mySngl;
  occ::handle<NCollection_HArray1<double>> mySnglLen;
  bool                                     isSngl;
};
