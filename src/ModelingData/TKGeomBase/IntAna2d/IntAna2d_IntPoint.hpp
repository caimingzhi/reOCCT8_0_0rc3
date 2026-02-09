#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <Standard_Boolean.hpp>

class IntAna2d_IntPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntAna2d_IntPoint(const double X,
                                    const double Y,
                                    const double U1,
                                    const double U2);

  Standard_EXPORT IntAna2d_IntPoint(const double X, const double Y, const double U1);

  Standard_EXPORT IntAna2d_IntPoint();

  Standard_EXPORT virtual void SetValue(const double X,
                                        const double Y,
                                        const double U1,
                                        const double U2);

  Standard_EXPORT virtual void SetValue(const double X, const double Y, const double U1);

  const gp_Pnt2d& Value() const;

  bool SecondIsImplicit() const;

  double ParamOnFirst() const;

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
