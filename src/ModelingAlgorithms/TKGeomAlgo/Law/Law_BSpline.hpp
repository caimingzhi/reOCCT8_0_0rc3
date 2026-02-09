#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomAbs_BSplKnotDistribution.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>

class Law_BSpline : public Standard_Transient
{

public:
  Standard_EXPORT Law_BSpline(const NCollection_Array1<double>& Poles,
                              const NCollection_Array1<double>& Knots,
                              const NCollection_Array1<int>&    Multiplicities,
                              const int                         Degree,
                              const bool                        Periodic = false);

  Standard_EXPORT Law_BSpline(const NCollection_Array1<double>& Poles,
                              const NCollection_Array1<double>& Weights,
                              const NCollection_Array1<double>& Knots,
                              const NCollection_Array1<int>&    Multiplicities,
                              const int                         Degree,
                              const bool                        Periodic = false);

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

  Standard_EXPORT void Reverse();

  Standard_EXPORT double ReversedParameter(const double U) const;

  Standard_EXPORT void Segment(const double U1, const double U2);

  Standard_EXPORT void SetKnot(const int Index, const double K);

  Standard_EXPORT void SetKnots(const NCollection_Array1<double>& K);

  Standard_EXPORT void SetKnot(const int Index, const double K, const int M);

  Standard_EXPORT void PeriodicNormalization(double& U) const;

  Standard_EXPORT void SetPeriodic();

  Standard_EXPORT void SetOrigin(const int Index);

  Standard_EXPORT void SetNotPeriodic();

  Standard_EXPORT void SetPole(const int Index, const double P);

  Standard_EXPORT void SetPole(const int Index, const double P, const double Weight);

  Standard_EXPORT void SetWeight(const int Index, const double Weight);

  Standard_EXPORT bool IsCN(const int N) const;

  Standard_EXPORT bool IsClosed() const;

  Standard_EXPORT bool IsPeriodic() const;

  Standard_EXPORT bool IsRational() const;

  Standard_EXPORT GeomAbs_Shape Continuity() const;

  Standard_EXPORT int Degree() const;

  Standard_EXPORT double Value(const double U) const;

  Standard_EXPORT void D0(const double U, double& P) const;

  Standard_EXPORT void D1(const double U, double& P, double& V1) const;

  Standard_EXPORT void D2(const double U, double& P, double& V1, double& V2) const;

  Standard_EXPORT void D3(const double U, double& P, double& V1, double& V2, double& V3) const;

  Standard_EXPORT double DN(const double U, const int N) const;

  Standard_EXPORT double LocalValue(const double U, const int FromK1, const int ToK2) const;

  Standard_EXPORT void LocalD0(const double U, const int FromK1, const int ToK2, double& P) const;

  Standard_EXPORT void LocalD1(const double U,
                               const int    FromK1,
                               const int    ToK2,
                               double&      P,
                               double&      V1) const;

  Standard_EXPORT void LocalD2(const double U,
                               const int    FromK1,
                               const int    ToK2,
                               double&      P,
                               double&      V1,
                               double&      V2) const;

  Standard_EXPORT void LocalD3(const double U,
                               const int    FromK1,
                               const int    ToK2,
                               double&      P,
                               double&      V1,
                               double&      V2,
                               double&      V3) const;

  Standard_EXPORT double LocalDN(const double U,
                                 const int    FromK1,
                                 const int    ToK2,
                                 const int    N) const;

  Standard_EXPORT double EndPoint() const;

  Standard_EXPORT int FirstUKnotIndex() const;

  Standard_EXPORT double FirstParameter() const;

  Standard_EXPORT double Knot(const int Index) const;

  Standard_EXPORT void Knots(NCollection_Array1<double>& K) const;

  Standard_EXPORT void KnotSequence(NCollection_Array1<double>& K) const;

  Standard_EXPORT GeomAbs_BSplKnotDistribution KnotDistribution() const;

  Standard_EXPORT int LastUKnotIndex() const;

  Standard_EXPORT double LastParameter() const;

  Standard_EXPORT void LocateU(const double U,
                               const double ParametricTolerance,
                               int&         I1,
                               int&         I2,
                               const bool   WithKnotRepetition = false) const;

  Standard_EXPORT int Multiplicity(const int Index) const;

  Standard_EXPORT void Multiplicities(NCollection_Array1<int>& M) const;

  Standard_EXPORT int NbKnots() const;

  Standard_EXPORT int NbPoles() const;

  Standard_EXPORT double Pole(const int Index) const;

  Standard_EXPORT void Poles(NCollection_Array1<double>& P) const;

  Standard_EXPORT double StartPoint() const;

  Standard_EXPORT double Weight(const int Index) const;

  Standard_EXPORT void Weights(NCollection_Array1<double>& W) const;

  Standard_EXPORT static int MaxDegree();

  Standard_EXPORT void MovePointAndTangent(const double U,
                                           const double NewValue,
                                           const double Derivative,
                                           const double Tolerance,
                                           const int    StartingCondition,
                                           const int    EndingCondition,
                                           int&         ErrorStatus);

  Standard_EXPORT void Resolution(const double Tolerance3D, double& UTolerance) const;

  Standard_EXPORT occ::handle<Law_BSpline> Copy() const;

  DEFINE_STANDARD_RTTIEXT(Law_BSpline, Standard_Transient)

private:
  Standard_EXPORT bool IsCacheValid(const double Parameter) const;

  Standard_EXPORT void UpdateKnots();

  bool                                     rational;
  bool                                     periodic;
  GeomAbs_BSplKnotDistribution             knotSet;
  GeomAbs_Shape                            smooth;
  int                                      deg;
  occ::handle<NCollection_HArray1<double>> poles;
  occ::handle<NCollection_HArray1<double>> weights;
  occ::handle<NCollection_HArray1<double>> flatknots;
  occ::handle<NCollection_HArray1<double>> knots;
  occ::handle<NCollection_HArray1<int>>    mults;
};
