#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
class gp_Pnt;
class gp_XYZ;

class Intf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void PlaneEquation(const gp_Pnt& P1,
                                            const gp_Pnt& P2,
                                            const gp_Pnt& P3,
                                            gp_XYZ&       NormalVector,
                                            double&       PolarDistance);

  Standard_EXPORT static bool Contain(const gp_Pnt& P1,
                                      const gp_Pnt& P2,
                                      const gp_Pnt& P3,
                                      const gp_Pnt& ThePnt);
};
