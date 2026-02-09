#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <Standard_Boolean.hpp>
class gp_Pnt2d;

class IntSurf_PntOn2S
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntSurf_PntOn2S();

  void SetValue(const gp_Pnt& Pt);

  Standard_EXPORT void SetValue(const gp_Pnt& Pt,
                                const bool    OnFirst,
                                const double  U,
                                const double  V);

  void SetValue(const gp_Pnt& Pt,
                const double  U1,
                const double  V1,
                const double  U2,
                const double  V2);

  Standard_EXPORT void SetValue(const bool OnFirst, const double U, const double V);

  void SetValue(const double U1, const double V1, const double U2, const double V2);

  const gp_Pnt& Value() const;

  Standard_EXPORT gp_Pnt2d ValueOnSurface(const bool OnFirst) const;

  void ParametersOnS1(double& U1, double& V1) const;

  void ParametersOnS2(double& U2, double& V2) const;

  Standard_EXPORT void ParametersOnSurface(const bool OnFirst, double& U, double& V) const;

  void Parameters(double& U1, double& V1, double& U2, double& V2) const;

  Standard_EXPORT bool IsSame(const IntSurf_PntOn2S& theOtherPoint,
                              const double           theTol3D = 0.0,
                              const double           theTol2D = -1.0) const;

private:
  gp_Pnt pt;
  double u1;
  double v1;
  double u2;
  double v2;
};

inline void IntSurf_PntOn2S::SetValue(const gp_Pnt& Pt)
{

  pt = Pt;
}

inline void IntSurf_PntOn2S::SetValue(const gp_Pnt& Pt,
                                      const double  U1,
                                      const double  V1,
                                      const double  U2,
                                      const double  V2)
{

  pt = Pt;
  u1 = U1;
  v1 = V1;
  u2 = U2;
  v2 = V2;
}

inline void IntSurf_PntOn2S::SetValue(const double U1,
                                      const double V1,
                                      const double U2,
                                      const double V2)
{
  u1 = U1;
  v1 = V1;
  u2 = U2;
  v2 = V2;
}

inline const gp_Pnt& IntSurf_PntOn2S::Value() const
{

  return pt;
}

inline void IntSurf_PntOn2S::ParametersOnS1(double& U1, double& V1) const
{
  U1 = u1;
  V1 = v1;
}

inline void IntSurf_PntOn2S::ParametersOnS2(double& U2, double& V2) const
{
  U2 = u2;
  V2 = v2;
}

inline void IntSurf_PntOn2S::Parameters(double& U1, double& V1, double& U2, double& V2) const
{
  U1 = u1;
  V1 = v1;
  U2 = u2;
  V2 = v2;
}
