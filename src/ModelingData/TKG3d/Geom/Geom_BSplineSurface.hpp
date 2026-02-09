#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Precision.hpp>
#include <GeomAbs_BSplKnotDistribution.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Geom_BoundedSurface.hpp>
class gp_Pnt;
class gp_Vec;
class Geom_Curve;
class gp_Trsf;
class Geom_Geometry;

class Geom_BSplineSurface : public Geom_BoundedSurface
{

public:
  Standard_EXPORT Geom_BSplineSurface(const NCollection_Array2<gp_Pnt>& Poles,
                                      const NCollection_Array1<double>& UKnots,
                                      const NCollection_Array1<double>& VKnots,
                                      const NCollection_Array1<int>&    UMults,
                                      const NCollection_Array1<int>&    VMults,
                                      const int                         UDegree,
                                      const int                         VDegree,
                                      const bool                        UPeriodic = false,
                                      const bool                        VPeriodic = false);

  Standard_EXPORT Geom_BSplineSurface(const NCollection_Array2<gp_Pnt>& Poles,
                                      const NCollection_Array2<double>& Weights,
                                      const NCollection_Array1<double>& UKnots,
                                      const NCollection_Array1<double>& VKnots,
                                      const NCollection_Array1<int>&    UMults,
                                      const NCollection_Array1<int>&    VMults,
                                      const int                         UDegree,
                                      const int                         VDegree,
                                      const bool                        UPeriodic = false,
                                      const bool                        VPeriodic = false);

  Standard_EXPORT Geom_BSplineSurface(const Geom_BSplineSurface& theOther);

  Standard_EXPORT void ExchangeUV();

  Standard_EXPORT void SetUPeriodic();

  Standard_EXPORT void SetVPeriodic();

  Standard_EXPORT void PeriodicNormalization(double& U, double& V) const;

  Standard_EXPORT void SetUOrigin(const int Index);

  Standard_EXPORT void SetVOrigin(const int Index);

  Standard_EXPORT void SetUNotPeriodic();

  Standard_EXPORT void SetVNotPeriodic();

  Standard_EXPORT void UReverse() override;

  Standard_EXPORT void VReverse() override;

  Standard_EXPORT double UReversedParameter(const double U) const override;

  Standard_EXPORT double VReversedParameter(const double V) const override;

  Standard_EXPORT void IncreaseDegree(const int UDegree, const int VDegree);

  Standard_EXPORT void InsertUKnots(const NCollection_Array1<double>& Knots,
                                    const NCollection_Array1<int>&    Mults,
                                    const double                      ParametricTolerance = 0.0,
                                    const bool                        Add                 = true);

  Standard_EXPORT void InsertVKnots(const NCollection_Array1<double>& Knots,
                                    const NCollection_Array1<int>&    Mults,
                                    const double                      ParametricTolerance = 0.0,
                                    const bool                        Add                 = true);

  Standard_EXPORT bool RemoveUKnot(const int Index, const int M, const double Tolerance);

  Standard_EXPORT bool RemoveVKnot(const int Index, const int M, const double Tolerance);

  Standard_EXPORT void IncreaseUMultiplicity(const int UIndex, const int M);

  Standard_EXPORT void IncreaseUMultiplicity(const int FromI1, const int ToI2, const int M);

  Standard_EXPORT void IncrementUMultiplicity(const int FromI1, const int ToI2, const int Step);

  Standard_EXPORT void IncreaseVMultiplicity(const int VIndex, const int M);

  Standard_EXPORT void IncreaseVMultiplicity(const int FromI1, const int ToI2, const int M);

  Standard_EXPORT void IncrementVMultiplicity(const int FromI1, const int ToI2, const int Step);

  Standard_EXPORT void InsertUKnot(const double U,
                                   const int    M,
                                   const double ParametricTolerance,
                                   const bool   Add = true);

  Standard_EXPORT void InsertVKnot(const double V,
                                   const int    M,
                                   const double ParametricTolerance,
                                   const bool   Add = true);

  Standard_EXPORT void Segment(const double U1,
                               const double U2,
                               const double V1,
                               const double V2,
                               const double theUTolerance = Precision::PConfusion(),
                               const double theVTolerance = Precision::PConfusion());

  Standard_EXPORT void CheckAndSegment(const double U1,
                                       const double U2,
                                       const double V1,
                                       const double V2,
                                       const double theUTolerance = Precision::PConfusion(),
                                       const double theVTolerance = Precision::PConfusion());

  Standard_EXPORT void SetUKnot(const int UIndex, const double K);

  Standard_EXPORT void SetUKnots(const NCollection_Array1<double>& UK);

  Standard_EXPORT void SetUKnot(const int UIndex, const double K, const int M);

  Standard_EXPORT void SetVKnot(const int VIndex, const double K);

  Standard_EXPORT void SetVKnots(const NCollection_Array1<double>& VK);

  Standard_EXPORT void SetVKnot(const int VIndex, const double K, const int M);

  Standard_EXPORT void LocateU(const double U,
                               const double ParametricTolerance,
                               int&         I1,
                               int&         I2,
                               const bool   WithKnotRepetition = false) const;

  Standard_EXPORT void LocateV(const double V,
                               const double ParametricTolerance,
                               int&         I1,
                               int&         I2,
                               const bool   WithKnotRepetition = false) const;

  Standard_EXPORT void SetPole(const int UIndex, const int VIndex, const gp_Pnt& P);

  Standard_EXPORT void SetPole(const int     UIndex,
                               const int     VIndex,
                               const gp_Pnt& P,
                               const double  Weight);

  Standard_EXPORT void SetPoleCol(const int VIndex, const NCollection_Array1<gp_Pnt>& CPoles);

  Standard_EXPORT void SetPoleCol(const int                         VIndex,
                                  const NCollection_Array1<gp_Pnt>& CPoles,
                                  const NCollection_Array1<double>& CPoleWeights);

  Standard_EXPORT void SetPoleRow(const int                         UIndex,
                                  const NCollection_Array1<gp_Pnt>& CPoles,
                                  const NCollection_Array1<double>& CPoleWeights);

  Standard_EXPORT void SetPoleRow(const int UIndex, const NCollection_Array1<gp_Pnt>& CPoles);

  Standard_EXPORT void SetWeight(const int UIndex, const int VIndex, const double Weight);

  Standard_EXPORT void SetWeightCol(const int                         VIndex,
                                    const NCollection_Array1<double>& CPoleWeights);

  Standard_EXPORT void SetWeightRow(const int                         UIndex,
                                    const NCollection_Array1<double>& CPoleWeights);

  Standard_EXPORT void MovePoint(const double  U,
                                 const double  V,
                                 const gp_Pnt& P,
                                 const int     UIndex1,
                                 const int     UIndex2,
                                 const int     VIndex1,
                                 const int     VIndex2,
                                 int&          UFirstIndex,
                                 int&          ULastIndex,
                                 int&          VFirstIndex,
                                 int&          VLastIndex);

  Standard_EXPORT bool IsUClosed() const override;

  Standard_EXPORT bool IsVClosed() const override;

  Standard_EXPORT bool IsCNu(const int N) const override;

  Standard_EXPORT bool IsCNv(const int N) const override;

  Standard_EXPORT bool IsUPeriodic() const override;

  Standard_EXPORT bool IsURational() const;

  Standard_EXPORT bool IsVPeriodic() const override;

  Standard_EXPORT bool IsVRational() const;

  Standard_EXPORT void Bounds(double& U1, double& U2, double& V1, double& V2) const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

  Standard_EXPORT int FirstUKnotIndex() const;

  Standard_EXPORT int FirstVKnotIndex() const;

  Standard_EXPORT int LastUKnotIndex() const;

  Standard_EXPORT int LastVKnotIndex() const;

  Standard_EXPORT int NbUKnots() const;

  Standard_EXPORT int NbUPoles() const;

  Standard_EXPORT int NbVKnots() const;

  Standard_EXPORT int NbVPoles() const;

  Standard_EXPORT const gp_Pnt& Pole(const int UIndex, const int VIndex) const;

  Standard_EXPORT void Poles(NCollection_Array2<gp_Pnt>& P) const;

  Standard_EXPORT const NCollection_Array2<gp_Pnt>& Poles() const;

  Standard_EXPORT int UDegree() const;

  Standard_EXPORT double UKnot(const int UIndex) const;

  Standard_EXPORT GeomAbs_BSplKnotDistribution UKnotDistribution() const;

  Standard_EXPORT void UKnots(NCollection_Array1<double>& Ku) const;

  Standard_EXPORT const NCollection_Array1<double>& UKnots() const;

  Standard_EXPORT void UKnotSequence(NCollection_Array1<double>& Ku) const;

  Standard_EXPORT const NCollection_Array1<double>& UKnotSequence() const;

  Standard_EXPORT int UMultiplicity(const int UIndex) const;

  Standard_EXPORT void UMultiplicities(NCollection_Array1<int>& Mu) const;

  Standard_EXPORT const NCollection_Array1<int>& UMultiplicities() const;

  Standard_EXPORT int VDegree() const;

  Standard_EXPORT double VKnot(const int VIndex) const;

  Standard_EXPORT GeomAbs_BSplKnotDistribution VKnotDistribution() const;

  Standard_EXPORT void VKnots(NCollection_Array1<double>& Kv) const;

  Standard_EXPORT const NCollection_Array1<double>& VKnots() const;

  Standard_EXPORT void VKnotSequence(NCollection_Array1<double>& Kv) const;

  Standard_EXPORT const NCollection_Array1<double>& VKnotSequence() const;

  Standard_EXPORT int VMultiplicity(const int VIndex) const;

  Standard_EXPORT void VMultiplicities(NCollection_Array1<int>& Mv) const;

  Standard_EXPORT const NCollection_Array1<int>& VMultiplicities() const;

  Standard_EXPORT double Weight(const int UIndex, const int VIndex) const;

  Standard_EXPORT void Weights(NCollection_Array2<double>& W) const;

  Standard_EXPORT const NCollection_Array2<double>* Weights() const;

  const occ::handle<NCollection_HArray2<gp_Pnt>>& HArrayPoles() const { return poles; }

  const occ::handle<NCollection_HArray2<double>>& HArrayWeights() const { return weights; }

  const occ::handle<NCollection_HArray1<double>>& HArrayUFlatKnots() const { return ufknots; }

  const occ::handle<NCollection_HArray1<double>>& HArrayVFlatKnots() const { return vfknots; }

  Standard_EXPORT void D0(const double U, const double V, gp_Pnt& P) const override;

  Standard_EXPORT void D1(const double U,
                          const double V,
                          gp_Pnt&      P,
                          gp_Vec&      D1U,
                          gp_Vec&      D1V) const override;

  Standard_EXPORT void D2(const double U,
                          const double V,
                          gp_Pnt&      P,
                          gp_Vec&      D1U,
                          gp_Vec&      D1V,
                          gp_Vec&      D2U,
                          gp_Vec&      D2V,
                          gp_Vec&      D2UV) const override;

  Standard_EXPORT void D3(const double U,
                          const double V,
                          gp_Pnt&      P,
                          gp_Vec&      D1U,
                          gp_Vec&      D1V,
                          gp_Vec&      D2U,
                          gp_Vec&      D2V,
                          gp_Vec&      D2UV,
                          gp_Vec&      D3U,
                          gp_Vec&      D3V,
                          gp_Vec&      D3UUV,
                          gp_Vec&      D3UVV) const override;

  Standard_EXPORT gp_Vec DN(const double U,
                            const double V,
                            const int    Nu,
                            const int    Nv) const override;

  Standard_EXPORT void LocalD0(const double U,
                               const double V,
                               const int    FromUK1,
                               const int    ToUK2,
                               const int    FromVK1,
                               const int    ToVK2,
                               gp_Pnt&      P) const;

  Standard_EXPORT void LocalD1(const double U,
                               const double V,
                               const int    FromUK1,
                               const int    ToUK2,
                               const int    FromVK1,
                               const int    ToVK2,
                               gp_Pnt&      P,
                               gp_Vec&      D1U,
                               gp_Vec&      D1V) const;

  Standard_EXPORT void LocalD2(const double U,
                               const double V,
                               const int    FromUK1,
                               const int    ToUK2,
                               const int    FromVK1,
                               const int    ToVK2,
                               gp_Pnt&      P,
                               gp_Vec&      D1U,
                               gp_Vec&      D1V,
                               gp_Vec&      D2U,
                               gp_Vec&      D2V,
                               gp_Vec&      D2UV) const;

  Standard_EXPORT void LocalD3(const double U,
                               const double V,
                               const int    FromUK1,
                               const int    ToUK2,
                               const int    FromVK1,
                               const int    ToVK2,
                               gp_Pnt&      P,
                               gp_Vec&      D1U,
                               gp_Vec&      D1V,
                               gp_Vec&      D2U,
                               gp_Vec&      D2V,
                               gp_Vec&      D2UV,
                               gp_Vec&      D3U,
                               gp_Vec&      D3V,
                               gp_Vec&      D3UUV,
                               gp_Vec&      D3UVV) const;

  Standard_EXPORT gp_Vec LocalDN(const double U,
                                 const double V,
                                 const int    FromUK1,
                                 const int    ToUK2,
                                 const int    FromVK1,
                                 const int    ToVK2,
                                 const int    Nu,
                                 const int    Nv) const;

  Standard_EXPORT gp_Pnt LocalValue(const double U,
                                    const double V,
                                    const int    FromUK1,
                                    const int    ToUK2,
                                    const int    FromVK1,
                                    const int    ToVK2) const;

  Standard_EXPORT occ::handle<Geom_Curve> UIso(const double U) const override;

  Standard_EXPORT occ::handle<Geom_Curve> VIso(const double V) const override;

  Standard_EXPORT occ::handle<Geom_Curve> UIso(const double U, const bool CheckRational) const;

  Standard_EXPORT occ::handle<Geom_Curve> VIso(const double V, const bool CheckRational) const;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT static int MaxDegree();

  Standard_EXPORT void Resolution(const double Tolerance3D, double& UTolerance, double& VTolerance);

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_BSplineSurface, Geom_BoundedSurface)

protected:
  void segment(const double U1,
               const double U2,
               const double V1,
               const double V2,
               const double EpsU,
               const double EpsV,
               const bool   SegmentInU,
               const bool   SegmentInV);

private:
  Standard_EXPORT void UpdateUKnots();

  Standard_EXPORT void UpdateVKnots();

  bool                                     urational;
  bool                                     vrational;
  bool                                     uperiodic;
  bool                                     vperiodic;
  GeomAbs_BSplKnotDistribution             uknotSet;
  GeomAbs_BSplKnotDistribution             vknotSet;
  GeomAbs_Shape                            Usmooth;
  GeomAbs_Shape                            Vsmooth;
  int                                      udeg;
  int                                      vdeg;
  occ::handle<NCollection_HArray2<gp_Pnt>> poles;
  occ::handle<NCollection_HArray2<double>> weights;
  occ::handle<NCollection_HArray1<double>> ufknots;
  occ::handle<NCollection_HArray1<double>> vfknots;
  occ::handle<NCollection_HArray1<double>> uknots;
  occ::handle<NCollection_HArray1<double>> vknots;
  occ::handle<NCollection_HArray1<int>>    umults;
  occ::handle<NCollection_HArray1<int>>    vmults;
  double                                   umaxderivinv;
  double                                   vmaxderivinv;
  bool                                     maxderivinvok;
};
