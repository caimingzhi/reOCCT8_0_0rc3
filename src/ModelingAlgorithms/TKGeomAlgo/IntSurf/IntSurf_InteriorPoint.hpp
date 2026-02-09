#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>

class IntSurf_InteriorPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntSurf_InteriorPoint();

  Standard_EXPORT IntSurf_InteriorPoint(const gp_Pnt&   P,
                                        const double    U,
                                        const double    V,
                                        const gp_Vec&   Direc,
                                        const gp_Vec2d& Direc2d);

  Standard_EXPORT void SetValue(const gp_Pnt&   P,
                                const double    U,
                                const double    V,
                                const gp_Vec&   Direc,
                                const gp_Vec2d& Direc2d);

  const gp_Pnt& Value() const;

  void Parameters(double& U, double& V) const;

  double UParameter() const;

  double VParameter() const;

  const gp_Vec& Direction() const;

  const gp_Vec2d& Direction2d() const;

private:
  gp_Pnt   point;
  double   paramu;
  double   paramv;
  gp_Vec   direc;
  gp_Vec2d direc2d;
};

inline const gp_Pnt& IntSurf_InteriorPoint::Value() const
{

  return point;
}

inline void IntSurf_InteriorPoint::Parameters(double& U, double& V) const
{
  U = paramu;
  V = paramv;
}

inline double IntSurf_InteriorPoint::UParameter() const
{

  return paramu;
}

inline double IntSurf_InteriorPoint::VParameter() const
{

  return paramv;
}

inline const gp_Vec& IntSurf_InteriorPoint::Direction() const
{

  return direc;
}

inline const gp_Vec2d& IntSurf_InteriorPoint::Direction2d() const
{

  return direc2d;
}
