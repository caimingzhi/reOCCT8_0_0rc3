#pragma once


#include <Standard.hpp>

#include <Standard_Real.hpp>
#include <GeomFill_TrihedronLaw.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_Array1.hpp>

class GeomFill_DraftTrihedron : public GeomFill_TrihedronLaw
{

public:
  Standard_EXPORT GeomFill_DraftTrihedron(const gp_Vec& BiNormal, const double Angle);

  Standard_EXPORT void SetAngle(const double Angle);

  Standard_EXPORT occ::handle<GeomFill_TrihedronLaw> Copy() const override;

  //! compute Triedrhon and derivative Trihedron on curve at
  //! parameter <Param>
  //! Warning: It used only for C1 or C2 approximation
  Standard_EXPORT bool D0(const double Param,
                          gp_Vec&      Tangent,
                          gp_Vec&      Normal,
                          gp_Vec&      BiNormal) override;

  //! compute Trihedron on curve
  //! first and second derivatives.
  //! Warning: It used only for C2 approximation
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

  //! Returns the number of intervals for continuity <S>.
  //! May be one if Continuity(me) >= <S>
  Standard_EXPORT int NbIntervals(const GeomAbs_Shape S) const override;

  //! Stores in <T> the parameters bounding the intervals
  //! of continuity <S>.
  //!
  //! The array must provide enough room to accommodate
  //! for the parameters. i.e. T.Length() > NbIntervals()
  Standard_EXPORT void Intervals(NCollection_Array1<double>& T,
                                 const GeomAbs_Shape         S) const override;

  //! Get average value of Tangent(t) and Normal(t) it is useful to
  //! make fast approximation of rational surfaces.
  Standard_EXPORT void GetAverageLaw(gp_Vec& ATangent, gp_Vec& ANormal, gp_Vec& ABiNormal) override;

  //! Say if the law is Constant.
  Standard_EXPORT bool IsConstant() const override;

  //! Return True.
  Standard_EXPORT bool IsOnlyBy3dCurve() const override;

  DEFINE_STANDARD_RTTIEXT(GeomFill_DraftTrihedron, GeomFill_TrihedronLaw)

private:
  gp_Vec B;
  double myAngle;
  double myCos;
};

