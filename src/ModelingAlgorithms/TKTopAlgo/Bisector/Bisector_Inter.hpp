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

class Bisector_Inter : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Bisector_Inter();

  Standard_EXPORT Bisector_Inter(const Bisector_Bisec&  C1,
                                 const IntRes2d_Domain& D1,
                                 const Bisector_Bisec&  C2,
                                 const IntRes2d_Domain& D2,
                                 const double           TolConf,
                                 const double           Tol,
                                 const bool             ComunElement);

  Standard_EXPORT void Perform(const Bisector_Bisec&  C1,
                               const IntRes2d_Domain& D1,
                               const Bisector_Bisec&  C2,
                               const IntRes2d_Domain& D2,
                               const double           TolConf,
                               const double           Tol,
                               const bool             ComunElement);

private:
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
