#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_Pnt2d.hpp>
#include <Standard_Transient.hpp>

//! A Connexion links two lines of items in a set
//! of lines. It contains two points and their paramatric
//! definitions on the lines.
//! The items can be points or curves.
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

  //! Returns the Index on the first line.
  Standard_EXPORT int IndexFirstLine() const;

  //! Returns the Index on the Second line.
  Standard_EXPORT int IndexSecondLine() const;

  //! Returns the Index of the item on the first line.
  Standard_EXPORT int IndexItemOnFirst() const;

  //! Returns the Index of the item on the second line.
  Standard_EXPORT int IndexItemOnSecond() const;

  //! Returns the parameter of the point on the firstline.
  Standard_EXPORT double ParameterOnFirst() const;

  //! Returns the parameter of the point on the secondline.
  Standard_EXPORT double ParameterOnSecond() const;

  //! Returns the point on the firstline.
  Standard_EXPORT gp_Pnt2d PointOnFirst() const;

  //! Returns the point on the secondline.
  Standard_EXPORT gp_Pnt2d PointOnSecond() const;

  //! Returns the distance between the two points.
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

  //! Returns the reverse connexion of <me>.
  //! the firstpoint is the secondpoint.
  //! the secondpoint is the firstpoint.
  Standard_EXPORT occ::handle<MAT2d_Connexion> Reverse() const;

  //! Returns <True> if my firstPoint is on the same line
  //! than the firstpoint of <aConnexion> and my firstpoint
  //! is after the firstpoint of <aConnexion> on the line.
  //! <aSense> = 1 if <aConnexion> is on the Left of its
  //! firstline, else <aSense> = -1.
  Standard_EXPORT bool IsAfter(const occ::handle<MAT2d_Connexion>& aConnexion,
                               const double                        aSense) const;

  //! Print <me>.
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
