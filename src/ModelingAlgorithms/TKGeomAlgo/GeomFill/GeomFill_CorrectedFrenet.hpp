#pragma once

#include <Standard.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Vec.hpp>
#include <GeomFill_TrihedronLaw.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomFill_Trihedron.hpp>
class GeomFill_Frenet;
class Law_Function;

class GeomFill_CorrectedFrenet : public GeomFill_TrihedronLaw
{

public:
  Standard_EXPORT GeomFill_CorrectedFrenet();

  Standard_EXPORT GeomFill_CorrectedFrenet(const bool ForEvaluation);

  Standard_EXPORT occ::handle<GeomFill_TrihedronLaw> Copy() const override;

  Standard_EXPORT bool SetCurve(const occ::handle<Adaptor3d_Curve>& C) override;

  Standard_EXPORT void SetInterval(const double First, const double Last) override;

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

  Standard_EXPORT GeomFill_Trihedron EvaluateBestMode();

  Standard_EXPORT void GetAverageLaw(gp_Vec& ATangent, gp_Vec& ANormal, gp_Vec& ABiNormal) override;

  Standard_EXPORT bool IsConstant() const override;

  Standard_EXPORT bool IsOnlyBy3dCurve() const override;

  DEFINE_STANDARD_RTTIEXT(GeomFill_CorrectedFrenet, GeomFill_TrihedronLaw)

private:
  Standard_EXPORT void Init();

  Standard_EXPORT bool InitInterval(const double                  First,
                                    const double                  Last,
                                    const double                  Step,
                                    double&                       startAng,
                                    gp_Vec&                       prevTangent,
                                    gp_Vec&                       prevNormal,
                                    gp_Vec&                       aT,
                                    gp_Vec&                       aN,
                                    occ::handle<Law_Function>&    FuncInt,
                                    NCollection_Sequence<double>& SeqPoles,
                                    NCollection_Sequence<double>& SeqAngle,
                                    NCollection_Sequence<gp_Vec>& SeqTangent,
                                    NCollection_Sequence<gp_Vec>& SeqNormal) const;

  Standard_EXPORT double CalcAngleAT(const gp_Vec& Tangent,
                                     const gp_Vec& Normal,
                                     const gp_Vec& prevTangent,
                                     const gp_Vec& prevNormal) const;

  Standard_EXPORT double GetAngleAT(const double P) const;

  occ::handle<GeomFill_Frenet>             frenet;
  occ::handle<Law_Function>                EvolAroundT;
  occ::handle<Law_Function>                TLaw;
  gp_Vec                                   AT;
  gp_Vec                                   AN;
  bool                                     isFrenet;
  bool                                     myForEvaluation;
  occ::handle<NCollection_HArray1<double>> HArrPoles;
  occ::handle<NCollection_HArray1<double>> HArrAngle;
  occ::handle<NCollection_HArray1<gp_Vec>> HArrTangent;
  occ::handle<NCollection_HArray1<gp_Vec>> HArrNormal;
};
