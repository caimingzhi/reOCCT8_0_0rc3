#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <IntRes2d_Transition.hpp>
#include <Standard_Boolean.hpp>

//! Definition of an intersection point between two
//! 2D curves.
class IntRes2d_IntersectionPoint
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  Standard_EXPORT IntRes2d_IntersectionPoint();

  //! Creates an IntersectionPoint.
  //! if ReversedFlag is False, the parameter Uc1(resp. Uc2)
  //! and the Transition Trans1 (resp. Trans2) refer to
  //! the first curve (resp. second curve) otherwise Uc1
  //! and Trans1 (resp. Uc2 and Trans2) refer to the
  //! second curve (resp. the first curve).
  IntRes2d_IntersectionPoint(const gp_Pnt2d&            P,
                             const double               Uc1,
                             const double               Uc2,
                             const IntRes2d_Transition& Trans1,
                             const IntRes2d_Transition& Trans2,
                             const bool                 ReversedFlag);

  //! Sets the values for an existing intersection
  //! point. The meaning of the parameters are the same
  //! as for the Create.
  void SetValues(const gp_Pnt2d&            P,
                 const double               Uc1,
                 const double               Uc2,
                 const IntRes2d_Transition& Trans1,
                 const IntRes2d_Transition& Trans2,
                 const bool                 ReversedFlag);

  //! Returns the value of the coordinates of the
  //! intersection point in the 2D space.
  const gp_Pnt2d& Value() const;

  //! Returns the parameter on the first curve.
  double ParamOnFirst() const;

  //! Returns the parameter on the second curve.
  double ParamOnSecond() const;

  //! Returns the transition of the 1st curve compared to
  //! the 2nd one.
  const IntRes2d_Transition& TransitionOfFirst() const;

  //! returns the transition of the 2nd curve compared to
  //! the 1st one.
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
