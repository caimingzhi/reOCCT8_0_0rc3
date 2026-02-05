#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Geom2dInt_GInter.hpp>
class Geom2dAdaptor_Curve;
class gp_Lin2d;
class gp_Dir2d;

class Geom2dHatch_Intersector : public Geom2dInt_GInter
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an intersector.
  Geom2dHatch_Intersector(const double Confusion, const double Tangency);

  //! Returns the confusion tolerance of the
  //! intersector.
  double ConfusionTolerance() const;

  //! Sets the confusion tolerance of the intersector.
  void SetConfusionTolerance(const double Confusion);

  //! Returns the tangency tolerance of the
  //! intersector.
  double TangencyTolerance() const;

  //! Sets the tangency tolerance of the intersector.
  void SetTangencyTolerance(const double Tangency);

  //! Intersects the curves C1 and C2.
  //! The results are retrieved by the usual methods
  //! described in IntRes2d_Intersection.
  //! Creates an intersector.
  void Intersect(const Geom2dAdaptor_Curve& C1, const Geom2dAdaptor_Curve& C2);

  Standard_EXPORT Geom2dHatch_Intersector();

  //! Performs the intersection between the 2d line
  //! segment (<L>, <P>) and the Curve <E>. The line
  //! segment is the part of the 2d line <L> of
  //! parameter range [0, <P>] (P is positive and can be
  //! RealLast()). Tol is the Tolerance on the segment.
  //! The order is relevant, the first argument is the
  //! segment, the second the Edge.
  Standard_EXPORT void Perform(const gp_Lin2d&            L,
                               const double               P,
                               const double               Tol,
                               const Geom2dAdaptor_Curve& E);

  //! Returns in <T>, <N> and <C> the tangent, normal
  //! and curvature of the edge <E> at parameter value
  //! <U>.
  Standard_EXPORT void LocalGeometry(const Geom2dAdaptor_Curve& E,
                                     const double               U,
                                     gp_Dir2d&                  T,
                                     gp_Dir2d&                  N,
                                     double&                    C) const;

private:
  double myConfusionTolerance;
  double myTangencyTolerance;
};

inline Geom2dHatch_Intersector::Geom2dHatch_Intersector(const double Confusion,
                                                        const double Tangency)
    : myConfusionTolerance(Confusion),
      myTangencyTolerance(Tangency)
{
}

//=======================================================================
// Function : ConfusionTolerance
// Purpose  : Returns the confusion tolerance of the intersector.
//=======================================================================

inline double Geom2dHatch_Intersector::ConfusionTolerance() const
{
  return myConfusionTolerance;
}

//=======================================================================
// Function : SetConfusionTolerance
// Purpose  : Sets the confusion tolerance of the intersector.
//=======================================================================

inline void Geom2dHatch_Intersector::SetConfusionTolerance(const double Confusion)
{
  myConfusionTolerance = Confusion;
}

//=======================================================================
// Function : TangencyTolerance
// Purpose  : Returns the tangency tolerance of the intersector.
//=======================================================================

inline double Geom2dHatch_Intersector::TangencyTolerance() const
{
  return myTangencyTolerance;
}

//=======================================================================
// Function : SetTangencyTolerance
// Purpose  : Sets the tangency tolerance of the intersector.
//=======================================================================

inline void Geom2dHatch_Intersector::SetTangencyTolerance(const double Tangency)
{
  myTangencyTolerance = Tangency;
}

//=======================================================================
// Function : Intersect
// Purpose  : Intersects the curves C1 and C2.
//=======================================================================
#include <Adaptor2d_Curve2d.hpp>
#include <Geom2dAdaptor_Curve.hpp>

inline void Geom2dHatch_Intersector::Intersect(const Geom2dAdaptor_Curve& C1,
                                               const Geom2dAdaptor_Curve& C2)
{
  Geom2dInt_GInter::Perform(C1, C2, myConfusionTolerance, myTangencyTolerance);
}
