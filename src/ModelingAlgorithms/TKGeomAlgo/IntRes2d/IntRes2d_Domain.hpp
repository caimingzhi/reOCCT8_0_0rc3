#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <Standard_Boolean.hpp>

class IntRes2d_Domain
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntRes2d_Domain();

  Standard_EXPORT IntRes2d_Domain(const gp_Pnt2d& Pnt1,
                                  const double    Par1,
                                  const double    Tol1,
                                  const gp_Pnt2d& Pnt2,
                                  const double    Par2,
                                  const double    Tol2);

  Standard_EXPORT IntRes2d_Domain(const gp_Pnt2d& Pnt,
                                  const double    Par,
                                  const double    Tol,
                                  const bool      First);

  Standard_EXPORT void SetValues(const gp_Pnt2d& Pnt1,
                                 const double    Par1,
                                 const double    Tol1,
                                 const gp_Pnt2d& Pnt2,
                                 const double    Par2,
                                 const double    Tol2);

  Standard_EXPORT void SetValues();

  Standard_EXPORT void SetValues(const gp_Pnt2d& Pnt,
                                 const double    Par,
                                 const double    Tol,
                                 const bool      First);

  void SetEquivalentParameters(const double zero, const double period);

  bool HasFirstPoint() const;

  double FirstParameter() const;

  const gp_Pnt2d& FirstPoint() const;

  double FirstTolerance() const;

  bool HasLastPoint() const;

  double LastParameter() const;

  const gp_Pnt2d& LastPoint() const;

  double LastTolerance() const;

  bool IsClosed() const;

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
