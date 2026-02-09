#pragma once

#include <Standard.hpp>

#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Geom2d_BoundedCurve.hpp>
#include <GeomAbs_Shape.hpp>
#include <BSplCLib.hpp>

class gp_Pnt2d;
class gp_Vec2d;
class gp_Trsf2d;
class Geom2d_Geometry;

class Geom2d_BezierCurve : public Geom2d_BoundedCurve
{

public:
  Standard_EXPORT Geom2d_BezierCurve(const NCollection_Array1<gp_Pnt2d>& CurvePoles);

  Standard_EXPORT Geom2d_BezierCurve(const NCollection_Array1<gp_Pnt2d>& CurvePoles,
                                     const NCollection_Array1<double>&   PoleWeights);

  Standard_EXPORT Geom2d_BezierCurve(const Geom2d_BezierCurve& theOther);

  Standard_EXPORT void Increase(const int Degree);

  Standard_EXPORT void InsertPoleAfter(const int       Index,
                                       const gp_Pnt2d& P,
                                       const double    Weight = 1.0);

  Standard_EXPORT void InsertPoleBefore(const int       Index,
                                        const gp_Pnt2d& P,
                                        const double    Weight = 1.0);

  Standard_EXPORT void RemovePole(const int Index);

  Standard_EXPORT void Reverse() override;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT void Segment(const double U1, const double U2);

  Standard_EXPORT void SetPole(const int Index, const gp_Pnt2d& P);

  Standard_EXPORT void SetPole(const int Index, const gp_Pnt2d& P, const double Weight);

  Standard_EXPORT void SetWeight(const int Index, const double Weight);

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsCN(const int N) const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT bool IsRational() const;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int Degree() const;

  Standard_EXPORT void D0(const double U, gp_Pnt2d& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt2d& P, gp_Vec2d& V1) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt2d&    P,
                          gp_Vec2d&    V1,
                          gp_Vec2d&    V2,
                          gp_Vec2d&    V3) const override;

  Standard_EXPORT gp_Vec2d DN(const double U, const int N) const override;

  Standard_EXPORT gp_Pnt2d EndPoint() const override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT int NbPoles() const;

  Standard_EXPORT const gp_Pnt2d& Pole(const int Index) const;

  Standard_EXPORT void Poles(NCollection_Array1<gp_Pnt2d>& P) const;

  const NCollection_Array1<gp_Pnt2d>& Poles() const { return poles->Array1(); }

  Standard_EXPORT gp_Pnt2d StartPoint() const override;

  Standard_EXPORT double Weight(const int Index) const;

  Standard_EXPORT void Weights(NCollection_Array1<double>& W) const;

  const NCollection_Array1<double>* Weights() const
  {
    if (!weights.IsNull())
      return &weights->Array1();
    return BSplCLib::NoWeights();
  }

  Standard_EXPORT void Transform(const gp_Trsf2d& T) override;

  Standard_EXPORT static int MaxDegree();

  Standard_EXPORT void Resolution(const double ToleranceUV, double& UTolerance);

  Standard_EXPORT occ::handle<Geom2d_Geometry> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_BezierCurve, Geom2d_BoundedCurve)

private:
  void Init(const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Poles,
            const occ::handle<NCollection_HArray1<double>>&   Weights);

  bool                                       rational;
  bool                                       closed;
  occ::handle<NCollection_HArray1<gp_Pnt2d>> poles;
  occ::handle<NCollection_HArray1<double>>   weights;
  double                                     maxderivinv;
  bool                                       maxderivinvok;
};
