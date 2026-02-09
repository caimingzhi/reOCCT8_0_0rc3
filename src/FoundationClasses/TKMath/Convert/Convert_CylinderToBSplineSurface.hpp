#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Convert_ElementarySurfaceToBSplineSurface.hpp>
class gp_Cylinder;

class Convert_CylinderToBSplineSurface : public Convert_ElementarySurfaceToBSplineSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Convert_CylinderToBSplineSurface(const gp_Cylinder& Cyl,
                                                   const double       U1,
                                                   const double       U2,
                                                   const double       V1,
                                                   const double       V2);

  Standard_EXPORT Convert_CylinderToBSplineSurface(const gp_Cylinder& Cyl,
                                                   const double       V1,
                                                   const double       V2);
};
