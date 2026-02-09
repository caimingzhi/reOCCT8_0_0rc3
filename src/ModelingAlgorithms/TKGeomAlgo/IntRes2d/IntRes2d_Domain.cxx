#include <IntRes2d_Domain.hpp>
#include <Precision.hpp>

const double infVal = Precision::Infinite();

static inline double LimitInfinite(const double Val)
{
  return (std::abs(Val) > infVal ? (Val > 0 ? infVal : -infVal) : Val);
}

IntRes2d_Domain::IntRes2d_Domain()
    : status(0),
      first_param(0.0),
      last_param(0.0),
      first_tol(0.0),
      last_tol(0.0),
      first_point(0.0, 0.0),
      last_point(0.0, 0.0),
      periodfirst(0.0),
      periodlast(0.0)
{
}

void IntRes2d_Domain::SetValues()
{
  status      = 0;
  periodfirst = periodlast = 0.0;
}

IntRes2d_Domain::IntRes2d_Domain(const gp_Pnt2d& Pnt1,
                                 const double    Par1,
                                 const double    Tol1,
                                 const gp_Pnt2d& Pnt2,
                                 const double    Par2,
                                 const double    Tol2)
{

  SetValues(Pnt1, Par1, Tol1, Pnt2, Par2, Tol2);
}

void IntRes2d_Domain::SetValues(const gp_Pnt2d& Pnt1,
                                const double    Par1,
                                const double    Tol1,
                                const gp_Pnt2d& Pnt2,
                                const double    Par2,
                                const double    Tol2)
{

  status      = 3;
  periodfirst = periodlast = 0.0;

  first_param = LimitInfinite(Par1);
  first_point.SetCoord(LimitInfinite(Pnt1.X()), LimitInfinite(Pnt1.Y()));
  first_tol = Tol1;

  last_param = LimitInfinite(Par2);
  last_point.SetCoord(LimitInfinite(Pnt2.X()), LimitInfinite(Pnt2.Y()));
  last_tol = Tol2;
}

IntRes2d_Domain::IntRes2d_Domain(const gp_Pnt2d& Pnt,
                                 const double    Par,
                                 const double    Tol,
                                 const bool      First)
    : first_param(0.0),
      last_param(0.0),
      first_tol(0.0),
      last_tol(0.0),
      first_point(0.0, 0.0),
      last_point(0.0, 0.0)
{
  SetValues(Pnt, Par, Tol, First);
}

void IntRes2d_Domain::SetValues(const gp_Pnt2d& Pnt,
                                const double    Par,
                                const double    Tol,
                                const bool      First)
{

  periodfirst = periodlast = 0.0;
  if (First)
  {
    status      = 1;
    first_param = LimitInfinite(Par);
    first_point.SetCoord(LimitInfinite(Pnt.X()), LimitInfinite(Pnt.Y()));
    first_tol = Tol;
  }
  else
  {
    status     = 2;
    last_param = LimitInfinite(Par);
    last_point.SetCoord(LimitInfinite(Pnt.X()), LimitInfinite(Pnt.Y()));
    last_tol = Tol;
  }
}
