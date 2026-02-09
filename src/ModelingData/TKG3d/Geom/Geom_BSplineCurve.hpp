#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Precision.hpp>
#include <GeomAbs_BSplKnotDistribution.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Geom_BoundedCurve.hpp>
class gp_Pnt;
class gp_Vec;
class gp_Trsf;
class Geom_Geometry;

class Geom_BSplineCurve : public Geom_BoundedCurve
{

public:
  Standard_EXPORT Geom_BSplineCurve(const NCollection_Array1<gp_Pnt>& Poles,
                                    const NCollection_Array1<double>& Knots,
                                    const NCollection_Array1<int>&    Multiplicities,
                                    const int                         Degree,
                                    const bool                        Periodic = false);

  Standard_EXPORT Geom_BSplineCurve(const NCollection_Array1<gp_Pnt>& Poles,
                                    const NCollection_Array1<double>& Weights,
                                    const NCollection_Array1<double>& Knots,
                                    const NCollection_Array1<int>&    Multiplicities,
                                    const int                         Degree,
                                    const bool                        Periodic      = false,
                                    const bool                        CheckRational = true);

  Standard_EXPORT Geom_BSplineCurve(const Geom_BSplineCurve& theOther);

  Standard_EXPORT void IncreaseDegree(const int Degree);

  Standard_EXPORT void IncreaseMultiplicity(const int Index, const int M);

  Standard_EXPORT void IncreaseMultiplicity(const int I1, const int I2, const int M);

  Standard_EXPORT void IncrementMultiplicity(const int I1, const int I2, const int M);

  Standard_EXPORT void InsertKnot(const double U,
                                  const int    M                   = 1,
                                  const double ParametricTolerance = 0.0,
                                  const bool   Add                 = true);

  Standard_EXPORT void InsertKnots(const NCollection_Array1<double>& Knots,
                                   const NCollection_Array1<int>&    Mults,
                                   const double                      ParametricTolerance = 0.0,
                                   const bool                        Add                 = false);

  Standard_EXPORT bool RemoveKnot(const int Index, const int M, const double Tolerance);

  Standard_EXPORT void Reverse() override;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT void Segment(const double U1,
                               const double U2,
                               const double theTolerance = Precision::PConfusion());

  Standard_EXPORT void SetKnot(const int Index, const double K);

  Standard_EXPORT void SetKnots(const NCollection_Array1<double>& K);

  Standard_EXPORT void SetKnot(const int Index, const double K, const int M);

  Standard_EXPORT void PeriodicNormalization(double& U) const;

  Standard_EXPORT void SetPeriodic();

  Standard_EXPORT void SetOrigin(const int Index);

  Standard_EXPORT void SetOrigin(const double U, const double Tol);

  Standard_EXPORT void SetNotPeriodic();

  Standard_EXPORT void SetPole(const int Index, const gp_Pnt& P);

  Standard_EXPORT void SetPole(const int Index, const gp_Pnt& P, const double Weight);

  Standard_EXPORT void SetWeight(const int Index, const double Weight);

  Standard_EXPORT void MovePoint(const double  U,
                                 const gp_Pnt& P,
                                 const int     Index1,
                                 const int     Index2,
                                 int&          FirstModifiedPole,
                                 int&          LastModifiedPole);

  Standard_EXPORT void MovePointAndTangent(const double  U,
                                           const gp_Pnt& P,
                                           const gp_Vec& Tangent,
                                           const double  Tolerance,
                                           const int     StartingCondition,
                                           const int     EndingCondition,
                                           int&          ErrorStatus);

  Standard_EXPORT bool IsCN(const int N) const override;

  Standard_EXPORT bool IsG1(const double theTf, const double theTl, const double theAngTol) const;

  Standard_EXPORT bool IsClosed() const override;

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

  Standard_EXPORT gp_Pnt LocalValue(const double U, const int FromK1, const int ToK2) const;

  Standard_EXPORT void LocalD0(const double U, const int FromK1, const int ToK2, gp_Pnt& P) const;

  Standard_EXPORT void LocalD1(const double U,
                               const int    FromK1,
                               const int    ToK2,
                               gp_Pnt&      P,
                               gp_Vec&      V1) const;

  Standard_EXPORT void LocalD2(const double U,
                               const int    FromK1,
                               const int    ToK2,
                               gp_Pnt&      P,
                               gp_Vec&      V1,
                               gp_Vec&      V2) const;

  Standard_EXPORT void LocalD3(const double U,
                               const int    FromK1,
                               const int    ToK2,
                               gp_Pnt&      P,
                               gp_Vec&      V1,
                               gp_Vec&      V2,
                               gp_Vec&      V3) const;

  Standard_EXPORT gp_Vec LocalDN(const double U,
                                 const int    FromK1,
                                 const int    ToK2,
                                 const int    N) const;

  Standard_EXPORT gp_Pnt EndPoint() const override;

  Standard_EXPORT int FirstUKnotIndex() const;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double Knot(const int Index) const;

  Standard_EXPORT void Knots(NCollection_Array1<double>& K) const;

  Standard_EXPORT const NCollection_Array1<double>& Knots() const;

  Standard_EXPORT void KnotSequence(NCollection_Array1<double>& K) const;

  Standard_EXPORT const NCollection_Array1<double>& KnotSequence() const;

  Standard_EXPORT GeomAbs_BSplKnotDistribution KnotDistribution() const;

  Standard_EXPORT int LastUKnotIndex() const;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT void LocateU(const double U,
                               const double ParametricTolerance,
                               int&         I1,
                               int&         I2,
                               const bool   WithKnotRepetition = false) const;

  Standard_EXPORT int Multiplicity(const int Index) const;

  Standard_EXPORT void Multiplicities(NCollection_Array1<int>& M) const;

  Standard_EXPORT const NCollection_Array1<int>& Multiplicities() const;

  Standard_EXPORT int NbKnots() const;

  Standard_EXPORT int NbPoles() const;

  Standard_EXPORT const gp_Pnt& Pole(const int Index) const;

  Standard_EXPORT void Poles(NCollection_Array1<gp_Pnt>& P) const;

  Standard_EXPORT const NCollection_Array1<gp_Pnt>& Poles() const;

  Standard_EXPORT gp_Pnt StartPoint() const override;

  Standard_EXPORT double Weight(const int Index) const;

  Standard_EXPORT void Weights(NCollection_Array1<double>& W) const;

  Standard_EXPORT const NCollection_Array1<double>* Weights() const;

  const occ::handle<NCollection_HArray1<gp_Pnt>>& HArrayPoles() const { return poles; }

  const occ::handle<NCollection_HArray1<double>>& HArrayWeights() const { return weights; }

  const occ::handle<NCollection_HArray1<double>>& HArrayFlatKnots() const { return flatknots; }

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT static int MaxDegree();

  Standard_EXPORT void Resolution(const double Tolerance3D, double& UTolerance);

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  Standard_EXPORT bool IsEqual(const occ::handle<Geom_BSplineCurve>& theOther,
                               const double                          thePreci) const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_BSplineCurve, Geom_BoundedCurve)

private:
  Standard_EXPORT void UpdateKnots();

  bool                                     rational;
  bool                                     periodic;
  GeomAbs_BSplKnotDistribution             knotSet;
  GeomAbs_Shape                            smooth;
  int                                      deg;
  occ::handle<NCollection_HArray1<gp_Pnt>> poles;
  occ::handle<NCollection_HArray1<double>> weights;
  occ::handle<NCollection_HArray1<double>> flatknots;
  occ::handle<NCollection_HArray1<double>> knots;
  occ::handle<NCollection_HArray1<int>>    mults;
  double                                   maxderivinv;
  bool                                     maxderivinvok;
};
