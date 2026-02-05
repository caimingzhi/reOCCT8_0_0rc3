#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Vec;

//! defines IGESOffsetSurface, Type <140> Form <0>
//! in package IGESGeom
//! An offset surface is a surface defined in terms of an
//! already existing surface.If S(u, v) is a parametrised
//! regular surface and N(u, v) is a differential field of
//! unit normal vectors defined on the whole surface, and
//! "d" a fixed non zero real number, then offset surface
//! to S is a parametrised surface S(u, v) given by
//! O(u, v) = S(u, v) + d * N(u, v);
//! u1 <= u <= u2; v1 <= v <= v2;
class IGESGeom_OffsetSurface : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESGeom_OffsetSurface();

  //! This method is used to set the fields of the class
  //! OffsetSurface
  //! - anIndicator : Offset indicator
  //! - aDistance   : Offset distance
  //! - aSurface    : Surface that is offset
  Standard_EXPORT void Init(const gp_XYZ&                           anIndicatoR,
                            const double                            aDistance,
                            const occ::handle<IGESData_IGESEntity>& aSurface);

  //! returns the offset indicator
  Standard_EXPORT gp_Vec OffsetIndicator() const;

  //! returns the offset indicator after applying Transf. Matrix
  Standard_EXPORT gp_Vec TransformedOffsetIndicator() const;

  //! returns the distance by which surface is offset
  Standard_EXPORT double Distance() const;

  //! returns the surface that has been offset
  Standard_EXPORT occ::handle<IGESData_IGESEntity> Surface() const;

  DEFINE_STANDARD_RTTIEXT(IGESGeom_OffsetSurface, IGESData_IGESEntity)

private:
  gp_XYZ                           theIndicator;
  double                           theDistance;
  occ::handle<IGESData_IGESEntity> theSurface;
};
