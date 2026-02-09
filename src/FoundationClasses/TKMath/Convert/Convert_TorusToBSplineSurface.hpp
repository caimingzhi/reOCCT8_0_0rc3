#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ElementarySurfaceToBSplineSurface.hpp>
#include <Standard_Boolean.hpp>
class gp_Torus;

class Convert_TorusToBSplineSurface : public Convert_ElementarySurfaceToBSplineSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Convert_TorusToBSplineSurface(const gp_Torus& T,
                                                const double    U1,
                                                const double    U2,
                                                const double    V1,
                                                const double    V2);

  Standard_EXPORT Convert_TorusToBSplineSurface(const gp_Torus& T,
                                                const double    Param1,
                                                const double    Param2,
                                                const bool      UTrim = true);

  Standard_EXPORT Convert_TorusToBSplineSurface(const gp_Torus& T);
};
