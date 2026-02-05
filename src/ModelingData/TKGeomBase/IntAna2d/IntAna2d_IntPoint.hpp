#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <Standard_Boolean.hpp>

//! Geometrical intersection between two 2d elements.
class IntAna2d_IntPoint
{
public:
  DEFINE_STANDARD_ALLOC

  //! Create an intersection point between 2 parametric 2d lines.
  //! X,Y are the coordinate of the point. U1 is the parameter
  //! on the first element, U2 the parameter on the second one.
  Standard_EXPORT IntAna2d_IntPoint(const double X,
                                    const double Y,
                                    const double U1,
                                    const double U2);

  //! Create an intersection point between a parametric 2d line,
  //! and a line given by an implicit equation (ImplicitCurve).
  //! X,Y are the coordinate of the point. U1 is the parameter
  //! on the parametric element.
  //! Empty constructor. It's necessary to use one of
  //! the SetValue method after this one.
  Standard_EXPORT IntAna2d_IntPoint(const double X, const double Y, const double U1);

  Standard_EXPORT IntAna2d_IntPoint();

  //! Set the values for a "non-implicit" point.
  Standard_EXPORT virtual void SetValue(const double X,
                                        const double Y,
                                        const double U1,
                                        const double U2);

  //! Set the values for an "implicit" point.
  Standard_EXPORT virtual void SetValue(const double X, const double Y, const double U1);

  //! Returns the geometric point.
  const gp_Pnt2d& Value() const;

  //! Returns True if the second curve is implicit.
  bool SecondIsImplicit() const;

  //! Returns the parameter on the first element.
  double ParamOnFirst() const;

  //! Returns the parameter on the second element.
  //! If the second element is an implicit curve, an exception
  //! is raised.
  double ParamOnSecond() const;

private:
  double   myu1;
  double   myu2;
  gp_Pnt2d myp;
  bool     myimplicit;
};

#include <Standard_DomainError.hpp>

inline const gp_Pnt2d& IntAna2d_IntPoint::Value() const
{
  return myp;
}

inline double IntAna2d_IntPoint::ParamOnFirst() const
{
  return myu1;
}

inline double IntAna2d_IntPoint::ParamOnSecond() const
{

  if (myimplicit)
  {
    throw Standard_DomainError();
  }
  return myu2;
}

inline bool IntAna2d_IntPoint::SecondIsImplicit() const
{
  return (myimplicit);
}
