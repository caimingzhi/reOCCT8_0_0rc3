#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Transient.hpp>

class MAT2d_Connexion : public Standard_Transient
{

public:
  Standard_EXPORT MAT2d_Connexion();

  Standard_EXPORT MAT2d_Connexion(const int       LineA,
                                  const int       LineB,
                                  const int       ItemA,
                                  const int       ItemB,
                                  const double    Distance,
                                  const double    ParameterOnA,
                                  const double    ParameterOnB,
                                  const gp_Pnt2d& PointA,
                                  const gp_Pnt2d& PointB);

  Standard_EXPORT int IndexFirstLine() const;

  Standard_EXPORT int IndexSecondLine() const;

  Standard_EXPORT int IndexItemOnFirst() const;

  Standard_EXPORT int IndexItemOnSecond() const;

  Standard_EXPORT double ParameterOnFirst() const;

  Standard_EXPORT double ParameterOnSecond() const;

  Standard_EXPORT gp_Pnt2d PointOnFirst() const;

  Standard_EXPORT gp_Pnt2d PointOnSecond() const;

  Standard_EXPORT double Distance() const;

  Standard_EXPORT void IndexFirstLine(const int anIndex);

  Standard_EXPORT void IndexSecondLine(const int anIndex);

  Standard_EXPORT void IndexItemOnFirst(const int anIndex);

  Standard_EXPORT void IndexItemOnSecond(const int anIndex);

  Standard_EXPORT void ParameterOnFirst(const double aParameter);

  Standard_EXPORT void ParameterOnSecond(const double aParameter);

  Standard_EXPORT void PointOnFirst(const gp_Pnt2d& aPoint);

  Standard_EXPORT void PointOnSecond(const gp_Pnt2d& aPoint);

  Standard_EXPORT void Distance(const double aDistance);

  Standard_EXPORT occ::handle<MAT2d_Connexion> Reverse() const;

  Standard_EXPORT bool IsAfter(const occ::handle<MAT2d_Connexion>& aConnexion,
                               const double                        aSense) const;

  Standard_EXPORT void Dump(const int Deep = 0, const int Offset = 0) const;

  DEFINE_STANDARD_RTTIEXT(MAT2d_Connexion, Standard_Transient)

private:
  int      lineA;
  int      lineB;
  int      itemA;
  int      itemB;
  double   distance;
  double   parameterOnA;
  double   parameterOnB;
  gp_Pnt2d pointA;
  gp_Pnt2d pointB;
};
