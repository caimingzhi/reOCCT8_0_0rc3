#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IntRes2d_Intersection.hpp>
class Bisector_Bisec;
class IntRes2d_Domain;
class Geom2d_Curve;
class Bisector_BisecCC;
class Geom2d_Line;

//! Intersection between two <Bisec> from Bisector.
class Bisector_Inter : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Bisector_Inter();

  //! Intersection between 2 curves.
  //! C1 separates the element A and B.
  //! C2 separates the elements C et D.
  //! If B an C have the same geometry. <ComunElement>
  //! Has to be True.
  //! It Permits an optimization of the computation.
  Standard_EXPORT Bisector_Inter(const Bisector_Bisec&  C1,
                                 const IntRes2d_Domain& D1,
                                 const Bisector_Bisec&  C2,
                                 const IntRes2d_Domain& D2,
                                 const double           TolConf,
                                 const double           Tol,
                                 const bool             ComunElement);

  //! Intersection between 2 curves.
  //! C1 separates the element A and B.
  //! C2 separates the elements C et D.
  //! If B an C have the same geometry. <ComunElement>
  //! Has to be True.
  //! It Permits an optimization of the computation.
  Standard_EXPORT void Perform(const Bisector_Bisec&  C1,
                               const IntRes2d_Domain& D1,
                               const Bisector_Bisec&  C2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol,
                               const bool             ComunElement);

private:
  //! Intersection between 2 curves.
  Standard_EXPORT void SinglePerform(const occ::handle<Geom2d_Curve>& C1,
                                     const IntRes2d_Domain&           D1,
                                     const occ::handle<Geom2d_Curve>& C2,
                                     const IntRes2d_Domain&           D2,
                                     const double                     TolConf,
                                     const double                     Tol,
                                     const bool                       ComunElement);

  Standard_EXPORT void NeighbourPerform(const occ::handle<Bisector_BisecCC>& C1,
                                        const IntRes2d_Domain&               D1,
                                        const occ::handle<Bisector_BisecCC>& C2,
                                        const IntRes2d_Domain&               D2,
                                        const double                         Tol);

  Standard_EXPORT void TestBound(const occ::handle<Geom2d_Line>&  C1,
                                 const IntRes2d_Domain&           D1,
                                 const occ::handle<Geom2d_Curve>& C2,
                                 const IntRes2d_Domain&           D2,
                                 const double                     Tol,
                                 const bool                       Reverse);
};
