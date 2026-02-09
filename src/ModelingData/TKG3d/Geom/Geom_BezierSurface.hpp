#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <Standard_Integer.hpp>
#include <Geom_BoundedSurface.hpp>
#include <NCollection_Array1.hpp>
#include <GeomAbs_Shape.hpp>
#include <BSplSLib.hpp>

class gp_Pnt;
class gp_Vec;
class Geom_Curve;
class gp_Trsf;
class Geom_Geometry;

class Geom_BezierSurface : public Geom_BoundedSurface
{

public:
  Standard_EXPORT Geom_BezierSurface(const NCollection_Array2<gp_Pnt>& SurfacePoles);

  Standard_EXPORT Geom_BezierSurface(const Geom_BezierSurface& theOther);

  Standard_EXPORT Geom_BezierSurface(const NCollection_Array2<gp_Pnt>& SurfacePoles,
                                     const NCollection_Array2<double>& PoleWeights);

  Standard_EXPORT void ExchangeUV();

  Standard_EXPORT void Increase(const int UDeg, const int VDeg);

  Standard_EXPORT void InsertPoleColAfter(const int                         VIndex,
                                          const NCollection_Array1<gp_Pnt>& CPoles);

  Standard_EXPORT void InsertPoleColAfter(const int                         VIndex,
                                          const NCollection_Array1<gp_Pnt>& CPoles,
                                          const NCollection_Array1<double>& CPoleWeights);

  Standard_EXPORT void InsertPoleColBefore(const int                         VIndex,
                                           const NCollection_Array1<gp_Pnt>& CPoles);

  Standard_EXPORT void InsertPoleColBefore(const int                         VIndex,
                                           const NCollection_Array1<gp_Pnt>& CPoles,
                                           const NCollection_Array1<double>& CPoleWeights);

  Standard_EXPORT void InsertPoleRowAfter(const int                         UIndex,
                                          const NCollection_Array1<gp_Pnt>& CPoles);

  Standard_EXPORT void InsertPoleRowAfter(const int                         UIndex,
                                          const NCollection_Array1<gp_Pnt>& CPoles,
                                          const NCollection_Array1<double>& CPoleWeights);

  Standard_EXPORT void InsertPoleRowBefore(const int                         UIndex,
                                           const NCollection_Array1<gp_Pnt>& CPoles);

  Standard_EXPORT void InsertPoleRowBefore(const int                         UIndex,
                                           const NCollection_Array1<gp_Pnt>& CPoles,
                                           const NCollection_Array1<double>& CPoleWeights);

  Standard_EXPORT void RemovePoleCol(const int VIndex);

  Standard_EXPORT void RemovePoleRow(const int UIndex);

  Standard_EXPORT void Segment(const double U1, const double U2, const double V1, const double V2);

  Standard_EXPORT void SetPole(const int UIndex, const int VIndex, const gp_Pnt& P);

  Standard_EXPORT void SetPole(const int     UIndex,
                               const int     VIndex,
                               const gp_Pnt& P,
                               const double  Weight);

  Standard_EXPORT void SetPoleCol(const int VIndex, const NCollection_Array1<gp_Pnt>& CPoles);

  Standard_EXPORT void SetPoleCol(const int                         VIndex,
                                  const NCollection_Array1<gp_Pnt>& CPoles,
                                  const NCollection_Array1<double>& CPoleWeights);

  Standard_EXPORT void SetPoleRow(const int UIndex, const NCollection_Array1<gp_Pnt>& CPoles);

  Standard_EXPORT void SetPoleRow(const int                         UIndex,
                                  const NCollection_Array1<gp_Pnt>& CPoles,
                                  const NCollection_Array1<double>& CPoleWeights);

  Standard_EXPORT void SetWeight(const int UIndex, const int VIndex, const double Weight);

  Standard_EXPORT void SetWeightCol(const int                         VIndex,
                                    const NCollection_Array1<double>& CPoleWeights);

  Standard_EXPORT void SetWeightRow(const int                         UIndex,
                                    const NCollection_Array1<double>& CPoleWeights);

  Standard_EXPORT void UReverse() override;

  Standard_EXPORT double UReversedParameter(const double U) const override;

  Standard_EXPORT void VReverse() override;

  Standard_EXPORT double VReversedParameter(const double V) const override;

  Standard_EXPORT void Bounds(double& U1, double& U2, double& V1, double& V2) const override;

  Standard_EXPORT GeomAbs_Shape Continuity() const override;

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

  Standard_EXPORT int NbUPoles() const;

  Standard_EXPORT int NbVPoles() const;

  Standard_EXPORT const gp_Pnt& Pole(const int UIndex, const int VIndex) const;

  Standard_EXPORT void Poles(NCollection_Array2<gp_Pnt>& P) const;

  const NCollection_Array2<gp_Pnt>& Poles() const { return poles->Array2(); }

  Standard_EXPORT int UDegree() const;

  Standard_EXPORT occ::handle<Geom_Curve> UIso(const double U) const override;

  Standard_EXPORT int VDegree() const;

  Standard_EXPORT occ::handle<Geom_Curve> VIso(const double V) const override;

  Standard_EXPORT double Weight(const int UIndex, const int VIndex) const;

  Standard_EXPORT void Weights(NCollection_Array2<double>& W) const;

  const NCollection_Array2<double>* Weights() const
  {
    if (!weights.IsNull())
      return &weights->Array2();
    return BSplSLib::NoWeights();
  }

  Standard_EXPORT bool IsUClosed() const override;

  Standard_EXPORT bool IsVClosed() const override;

  Standard_EXPORT bool IsCNu(const int N) const override;

  Standard_EXPORT bool IsCNv(const int N) const override;

  Standard_EXPORT bool IsUPeriodic() const override;

  Standard_EXPORT bool IsVPeriodic() const override;

  Standard_EXPORT bool IsURational() const;

  Standard_EXPORT bool IsVRational() const;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT static int MaxDegree();

  Standard_EXPORT void Resolution(const double Tolerance3D, double& UTolerance, double& VTolerance);

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_BezierSurface, Geom_BoundedSurface)

private:
  Geom_BezierSurface(const occ::handle<NCollection_HArray2<gp_Pnt>>& SurfacePoles,
                     const occ::handle<NCollection_HArray2<double>>& PoleWeights,
                     const bool                                      IsURational,
                     const bool                                      IsVRational);

  void Init(const occ::handle<NCollection_HArray2<gp_Pnt>>& Poles,
            const occ::handle<NCollection_HArray2<double>>& Weights);

  bool                                     urational;
  bool                                     vrational;
  occ::handle<NCollection_HArray2<gp_Pnt>> poles;
  occ::handle<NCollection_HArray2<double>> weights;
  double                                   umaxderivinv;
  double                                   vmaxderivinv;
  bool                                     maxderivinvok;
};
