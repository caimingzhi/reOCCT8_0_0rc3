#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_XY.hpp>
#include <Standard_Integer.hpp>
#include <Plate_LinearScalarConstraint.hpp>
class Plate_D1;
class Plate_D2;
class Plate_D3;

class Plate_FreeGtoCConstraint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_FreeGtoCConstraint(const gp_XY&    point2d,
                                           const Plate_D1& D1S,
                                           const Plate_D1& D1T,
                                           const double    IncrementalLoad = 1.0,
                                           const int       orientation     = 0);

  Standard_EXPORT Plate_FreeGtoCConstraint(const gp_XY&    point2d,
                                           const Plate_D1& D1S,
                                           const Plate_D1& D1T,
                                           const Plate_D2& D2S,
                                           const Plate_D2& D2T,
                                           const double    IncrementalLoad = 1.0,
                                           const int       orientation     = 0);

  Standard_EXPORT Plate_FreeGtoCConstraint(const gp_XY&    point2d,
                                           const Plate_D1& D1S,
                                           const Plate_D1& D1T,
                                           const Plate_D2& D2S,
                                           const Plate_D2& D2T,
                                           const Plate_D3& D3S,
                                           const Plate_D3& D3T,
                                           const double    IncrementalLoad = 1.0,
                                           const int       orientation     = 0);

  const int& nb_PPC() const;

  const Plate_PinpointConstraint& GetPPC(const int Index) const;

  const int& nb_LSC() const;

  const Plate_LinearScalarConstraint& LSC(const int Index) const;

private:
  gp_XY                        pnt2d;
  int                          nb_PPConstraints;
  int                          nb_LSConstraints;
  Plate_PinpointConstraint     myPPC[5];
  Plate_LinearScalarConstraint myLSC[4];
};

inline const int& Plate_FreeGtoCConstraint::nb_PPC() const
{
  return nb_PPConstraints;
}

inline const Plate_PinpointConstraint& Plate_FreeGtoCConstraint::GetPPC(const int Index) const
{
  return myPPC[Index];
}

inline const int& Plate_FreeGtoCConstraint::nb_LSC() const
{
  return nb_LSConstraints;
}

inline const Plate_LinearScalarConstraint& Plate_FreeGtoCConstraint::LSC(const int Index) const
{
  return myLSC[Index];
}
