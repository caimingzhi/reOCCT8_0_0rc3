#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Ax22d.hpp>
#include <Standard_Integer.hpp>
#include <GeomAbs_CurveType.hpp>
class gp_Elips2d;
class gp_Circ2d;
class gp_Parab2d;
class gp_Hypr2d;
class gp_Lin2d;

class IntCurve_PConic
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntCurve_PConic(const IntCurve_PConic& PC);

  Standard_EXPORT IntCurve_PConic(const gp_Elips2d& E);

  Standard_EXPORT IntCurve_PConic(const gp_Circ2d& C);

  Standard_EXPORT IntCurve_PConic(const gp_Parab2d& P);

  Standard_EXPORT IntCurve_PConic(const gp_Hypr2d& H);

  Standard_EXPORT IntCurve_PConic(const gp_Lin2d& L);

  Standard_EXPORT void SetEpsX(const double EpsDist);

  Standard_EXPORT void SetAccuracy(const int Nb);

  int Accuracy() const;

  double EpsX() const;

  GeomAbs_CurveType TypeCurve() const;

  const gp_Ax22d& Axis2() const;

  double Param1() const;

  double Param2() const;

private:
  gp_Ax22d          axe;
  double            prm1;
  double            prm2;
  double            TheEpsX;
  int               TheAccuracy;
  GeomAbs_CurveType type;
};

inline double IntCurve_PConic::EpsX() const
{
  return (TheEpsX);
}

inline double IntCurve_PConic::Param1() const
{
  return (prm1);
}

inline double IntCurve_PConic::Param2() const
{
  return (prm2);
}

inline const gp_Ax22d& IntCurve_PConic::Axis2() const
{
  return (axe);
}

inline GeomAbs_CurveType IntCurve_PConic::TypeCurve() const
{
  return (type);
}

inline int IntCurve_PConic::Accuracy() const
{
  return (TheAccuracy);
}
