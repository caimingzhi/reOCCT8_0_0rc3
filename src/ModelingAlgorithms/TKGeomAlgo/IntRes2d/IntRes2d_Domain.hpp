#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <Standard_Boolean.hpp>

//! Definition of the domain of parameter on a 2d-curve.
//! Most of the time, a domain is defined by two extremities.
//! An extremity is made of :
//! - a point in 2d-space (Pnt2d from gp),
//! - a parameter on the curve,
//! - a tolerance in the 2d-space.
//! Sometimes, it can be made of 0 or 1 point ( for an infinite
//! or semi-infinite line for example).
//!
//! For Intersection algorithms, Ellipses and Circles
//! Domains must be closed.
//! So, SetEquivalentParameters(.,.) method must be called
//! after initializing the first and the last bounds.
class IntRes2d_Domain
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an infinite Domain (HasFirstPoint = False
  //! and HasLastPoint = False).
  Standard_EXPORT IntRes2d_Domain();

  //! Creates a bounded Domain.
  Standard_EXPORT IntRes2d_Domain(const gp_Pnt2d& Pnt1,
                                  const double    Par1,
                                  const double    Tol1,
                                  const gp_Pnt2d& Pnt2,
                                  const double    Par2,
                                  const double    Tol2);

  //! Creates a semi-infinite Domain. If First is set to
  //! True, the given point is the first point of the domain,
  //! otherwise it is the last point.
  Standard_EXPORT IntRes2d_Domain(const gp_Pnt2d& Pnt,
                                  const double    Par,
                                  const double    Tol,
                                  const bool      First);

  //! Sets the values for a bounded domain.
  Standard_EXPORT void SetValues(const gp_Pnt2d& Pnt1,
                                 const double    Par1,
                                 const double    Tol1,
                                 const gp_Pnt2d& Pnt2,
                                 const double    Par2,
                                 const double    Tol2);

  //! Sets the values for an infinite domain.
  Standard_EXPORT void SetValues();

  //! Sets the values for a semi-infinite domain.
  Standard_EXPORT void SetValues(const gp_Pnt2d& Pnt,
                                 const double    Par,
                                 const double    Tol,
                                 const bool      First);

  //! Defines a closed domain.
  void SetEquivalentParameters(const double zero, const double period);

  //! Returns True if the domain has a first point, i-e
  //! a point defining the lowest admitted parameter on the
  //! curve.
  bool HasFirstPoint() const;

  //! Returns the parameter of the first point of the domain
  //! The exception DomainError is raised if HasFirstPoint
  //! returns False.
  double FirstParameter() const;

  //! Returns the first point of the domain.
  //! The exception DomainError is raised if HasFirstPoint
  //! returns False.
  const gp_Pnt2d& FirstPoint() const;

  //! Returns the tolerance of the first (left) bound.
  //! The exception DomainError is raised if HasFirstPoint
  //! returns False.
  double FirstTolerance() const;

  //! Returns True if the domain has a last point, i-e
  //! a point defining the highest admitted parameter on the
  //! curve.
  bool HasLastPoint() const;

  //! Returns the parameter of the last point of the domain.
  //! The exception DomainError is raised if HasLastPoint
  //! returns False.
  double LastParameter() const;

  //! Returns the last point of the domain.
  //! The exception DomainError is raised if HasLastPoint
  //! returns False.
  const gp_Pnt2d& LastPoint() const;

  //! Returns the tolerance of the last (right) bound.
  //! The exception DomainError is raised if HasLastPoint
  //! returns False.
  double LastTolerance() const;

  //! Returns True if the domain is closed.
  bool IsClosed() const;

  //! Returns Equivalent parameters if the domain is closed.
  //! Otherwise, the exception DomainError is raised.
  void EquivalentParameters(double& zero, double& zeroplusperiod) const;

private:
  int      status;
  double   first_param;
  double   last_param;
  double   first_tol;
  double   last_tol;
  gp_Pnt2d first_point;
  gp_Pnt2d last_point;
  double   periodfirst;
  double   periodlast;
};

#include <Standard_DomainError.hpp>

//-------------------------------------------------
//-- hasfirst <--> status & 1
//-- haslast  <--> status & 2
//-- closed   <--> status & 4
//-------------------------------------------------

inline void IntRes2d_Domain::SetEquivalentParameters(const double p_first, const double p_last)
{
  if ((status & 3) != 3)
  {
    throw Standard_DomainError();
  }
  status |= 4;
  periodfirst = p_first;
  periodlast  = p_last;
}

inline bool IntRes2d_Domain::HasFirstPoint() const
{
  return (status & 1) != 0;
}

inline double IntRes2d_Domain::FirstParameter() const
{
  if (!(status & 1))
  {
    throw Standard_DomainError();
  }
  return (first_param);
}

inline const gp_Pnt2d& IntRes2d_Domain::FirstPoint() const
{
  if (!(status & 1))
  {
    throw Standard_DomainError();
  }
  return (first_point);
}

inline double IntRes2d_Domain::FirstTolerance() const
{
  if (!(status & 1))
  {
    throw Standard_DomainError();
  }
  return (first_tol);
}

inline bool IntRes2d_Domain::HasLastPoint() const
{
  return (status & 2) != 0;
}

inline double IntRes2d_Domain::LastParameter() const
{
  if (!(status & 2))
  {
    throw Standard_DomainError();
  }
  return (last_param);
}

inline const gp_Pnt2d& IntRes2d_Domain::LastPoint() const
{
  if (!(status & 2))
  {
    throw Standard_DomainError();
  }
  return (last_point);
}

inline double IntRes2d_Domain::LastTolerance() const
{
  if (!(status & 2))
  {
    throw Standard_DomainError();
  }
  return (last_tol);
}

inline bool IntRes2d_Domain::IsClosed() const
{
  return (status & 4) != 0;
}

inline void IntRes2d_Domain::EquivalentParameters(double& p_first, double& p_last) const
{
  p_first = periodfirst;
  p_last  = periodlast;
}
