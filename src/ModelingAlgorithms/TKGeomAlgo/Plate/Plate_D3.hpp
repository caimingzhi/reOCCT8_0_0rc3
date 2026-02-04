#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_XYZ.hpp>

//! define an order 3 derivatives of a 3d valued
//! function of a 2d variable
class Plate_D3
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Plate_D3(const gp_XYZ& duuu,
                           const gp_XYZ& duuv,
                           const gp_XYZ& duvv,
                           const gp_XYZ& dvvv);

  Standard_EXPORT Plate_D3(const Plate_D3& ref);

  friend class Plate_GtoCConstraint;
  friend class Plate_FreeGtoCConstraint;

private:
  gp_XYZ Duuu;
  gp_XYZ Duuv;
  gp_XYZ Duvv;
  gp_XYZ Dvvv;
};

