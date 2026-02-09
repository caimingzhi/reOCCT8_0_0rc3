#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <IntRes2d_Transition.hpp>
#include <Standard_Boolean.hpp>

class IntRes2d_IntersectionPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntRes2d_IntersectionPoint();

  IntRes2d_IntersectionPoint(const gp_Pnt2d&            P,
                             const double               Uc1,
                             const double               Uc2,
                             const IntRes2d_Transition& Trans1,
                             const IntRes2d_Transition& Trans2,
                             const bool                 ReversedFlag);

  void SetValues(const gp_Pnt2d&            P,
                 const double               Uc1,
                 const double               Uc2,
                 const IntRes2d_Transition& Trans1,
                 const IntRes2d_Transition& Trans2,
                 const bool                 ReversedFlag);

  const gp_Pnt2d& Value() const;

  double ParamOnFirst() const;

  double ParamOnSecond() const;

  const IntRes2d_Transition& TransitionOfFirst() const;

  const IntRes2d_Transition& TransitionOfSecond() const;

private:
  gp_Pnt2d            pt;
  double              p1;
  double              p2;
  IntRes2d_Transition trans1;
  IntRes2d_Transition trans2;
};

inline IntRes2d_IntersectionPoint::IntRes2d_IntersectionPoint(const gp_Pnt2d&            P,
                                                              const double               Uc1,
                                                              const double               Uc2,
                                                              const IntRes2d_Transition& Trans1,
                                                              const IntRes2d_Transition& Trans2,
                                                              const bool ReversedFlag)
    : pt(P),
      p1(Uc1),
      p2(Uc2),
      trans1(Trans1),
      trans2(Trans2)
{
  if (ReversedFlag)
  {
    trans1 = Trans2;
    trans2 = Trans1;
    p1     = Uc2;
    p2     = Uc1;
  }
}

inline void IntRes2d_IntersectionPoint::SetValues(const gp_Pnt2d&            P,
                                                  const double               Uc1,
                                                  const double               Uc2,
                                                  const IntRes2d_Transition& Trans1,
                                                  const IntRes2d_Transition& Trans2,
                                                  const bool                 ReversedFlag)
{
  pt = P;
  if (!ReversedFlag)
  {
    trans1 = Trans1;
    trans2 = Trans2;
    p1     = Uc1;
    p2     = Uc2;
  }
  else
  {
    trans1 = Trans2;
    trans2 = Trans1;
    p1     = Uc2;
    p2     = Uc1;
  }
}

inline const gp_Pnt2d& IntRes2d_IntersectionPoint::Value() const
{
  return pt;
}

inline double IntRes2d_IntersectionPoint::ParamOnFirst() const
{
  return p1;
}

inline double IntRes2d_IntersectionPoint::ParamOnSecond() const
{
  return p2;
}

inline const IntRes2d_Transition& IntRes2d_IntersectionPoint::TransitionOfFirst() const
{
  return trans1;
}

inline const IntRes2d_Transition& IntRes2d_IntersectionPoint::TransitionOfSecond() const
{
  return trans2;
}
