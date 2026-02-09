#pragma once

#include <Standard.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <Geom_BoundedCurve.hpp>
#include <GeomAbs_Shape.hpp>
#include <BSplCLib.hpp>

class gp_Pnt;
class gp_Vec;
class gp_Trsf;
class Geom_Geometry;

class Geom_BezierCurve : public Geom_BoundedCurve
{

public:
  Standard_EXPORT Geom_BezierCurve(const NCollection_Array1<gp_Pnt>& CurvePoles);

  Standard_EXPORT Geom_BezierCurve(const NCollection_Array1<gp_Pnt>& CurvePoles,
                                   const NCollection_Array1<double>& PoleWeights);

  Standard_EXPORT Geom_BezierCurve(const Geom_BezierCurve& theOther);

  Standard_EXPORT void Increase(const int Degree);

  Standard_EXPORT void InsertPoleAfter(const int Index, const gp_Pnt& P);

  Standard_EXPORT void InsertPoleAfter(const int Index, const gp_Pnt& P, const double Weight);

  Standard_EXPORT void InsertPoleBefore(const int Index, const gp_Pnt& P);

  Standard_EXPORT void InsertPoleBefore(const int Index, const gp_Pnt& P, const double Weight);

  Standard_EXPORT void RemovePole(const int Index);

  Standard_EXPORT void Reverse() override;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT void Segment(const double U1, const double U2);

  Standard_EXPORT void SetPole(const int Index, const gp_Pnt& P);

  Standard_EXPORT void SetPole(const int Index, const gp_Pnt& P, const double Weight);

  Standard_EXPORT void SetWeight(const int Index, const double Weight);

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsCN(const int N) const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT bool IsRational() const;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int Degree() const;

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V1) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt&      P,
                          gp_Vec&      V1,
                          gp_Vec&      V2,
                          gp_Vec&      V3) const override;

  Standard_EXPORT gp_Vec DN(const double U, const int N) const override;

  Standard_EXPORT gp_Pnt StartPoint() const override;

  Standard_EXPORT gp_Pnt EndPoint() const override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT int NbPoles() const;

  Standard_EXPORT const gp_Pnt& Pole(const int Index) const;

  Standard_EXPORT void Poles(NCollection_Array1<gp_Pnt>& P) const;

  Standard_EXPORT const NCollection_Array1<gp_Pnt>& Poles() const;

  Standard_EXPORT double Weight(const int Index) const;

  Standard_EXPORT void Weights(NCollection_Array1<double>& W) const;

  const NCollection_Array1<double>* Weights() const
  {
    if (!weights.IsNull())
      return &weights->Array1();
    return BSplCLib::NoWeights();
  }

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT static int MaxDegree();

  Standard_EXPORT void Resolution(const double Tolerance3D, double& UTolerance);

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_BezierCurve, Geom_BoundedCurve)

private:
  void Init(const occ::handle<NCollection_HArray1<gp_Pnt>>& Poles,
            const occ::handle<NCollection_HArray1<double>>& Weights);

  bool                                     rational;
  bool                                     closed;
  occ::handle<NCollection_HArray1<gp_Pnt>> poles;
  occ::handle<NCollection_HArray1<double>> weights;
  double                                   maxderivinv;
  bool                                     maxderivinvok;
};
