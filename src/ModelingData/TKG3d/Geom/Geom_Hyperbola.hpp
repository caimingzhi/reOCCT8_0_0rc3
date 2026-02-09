#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Conic.hpp>
#include <Standard_Integer.hpp>
class gp_Hypr;
class gp_Ax2;
class gp_Ax1;
class gp_Pnt;
class gp_Vec;
class gp_Trsf;
class Geom_Geometry;

class Geom_Hyperbola : public Geom_Conic
{

public:
  Standard_EXPORT Geom_Hyperbola(const gp_Hypr& H);

  Standard_EXPORT Geom_Hyperbola(const gp_Ax2& A2,
                                 const double  MajorRadius,
                                 const double  MinorRadius);

  Standard_EXPORT void SetHypr(const gp_Hypr& H);

  Standard_EXPORT void SetMajorRadius(const double MajorRadius);

  Standard_EXPORT void SetMinorRadius(const double MinorRadius);

  Standard_EXPORT gp_Hypr Hypr() const;

  Standard_EXPORT double ReversedParameter(const double U) const override;

  Standard_EXPORT double FirstParameter() const override;

  Standard_EXPORT double LastParameter() const override;

  Standard_EXPORT bool IsClosed() const override;

  Standard_EXPORT bool IsPeriodic() const override;

  Standard_EXPORT gp_Ax1 Asymptote1() const;

  Standard_EXPORT gp_Ax1 Asymptote2() const;

  Standard_EXPORT gp_Hypr ConjugateBranch1() const;

  Standard_EXPORT gp_Hypr ConjugateBranch2() const;

  Standard_EXPORT gp_Ax1 Directrix1() const;

  Standard_EXPORT gp_Ax1 Directrix2() const;

  Standard_EXPORT double Eccentricity() const override;

  Standard_EXPORT double Focal() const;

  Standard_EXPORT gp_Pnt Focus1() const;

  Standard_EXPORT gp_Pnt Focus2() const;

  Standard_EXPORT double MajorRadius() const;

  Standard_EXPORT double MinorRadius() const;

  Standard_EXPORT gp_Hypr OtherBranch() const;

  Standard_EXPORT double Parameter() const;

  Standard_EXPORT void D0(const double U, gp_Pnt& P) const override;

  Standard_EXPORT void D1(const double U, gp_Pnt& P, gp_Vec& V1) const override;

  Standard_EXPORT void D2(const double U, gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const override;

  Standard_EXPORT void D3(const double U,
                          gp_Pnt&      P,
                          gp_Vec&      V1,
                          gp_Vec&      V2,
                          gp_Vec&      V3) const override;

  Standard_EXPORT gp_Vec DN(const double U, const int N) const override;

  Standard_EXPORT void Transform(const gp_Trsf& T) override;

  Standard_EXPORT occ::handle<Geom_Geometry> Copy() const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_Hyperbola, Geom_Conic)

private:
  double majorRadius;
  double minorRadius;
};
