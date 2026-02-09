#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ElementarySurfaceToBSplineSurface.hpp>
class gp_Cone;

class Convert_ConeToBSplineSurface : public Convert_ElementarySurfaceToBSplineSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Convert_ConeToBSplineSurface(const gp_Cone& C,
                                               const double   U1,
                                               const double   U2,
                                               const double   V1,
                                               const double   V2);

  Standard_EXPORT Convert_ConeToBSplineSurface(const gp_Cone& C, const double V1, const double V2);
};
