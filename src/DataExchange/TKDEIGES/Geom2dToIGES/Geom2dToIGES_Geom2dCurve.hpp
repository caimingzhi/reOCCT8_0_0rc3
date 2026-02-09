#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2dToIGES_Geom2dEntity.hpp>
class IGESData_IGESEntity;
class Geom2d_Curve;

class Geom2dToIGES_Geom2dCurve : public Geom2dToIGES_Geom2dEntity
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dToIGES_Geom2dCurve();

  Standard_EXPORT Geom2dToIGES_Geom2dCurve(const Geom2dToIGES_Geom2dEntity& G2dE);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Transfer2dCurve(
    const occ::handle<Geom2d_Curve>& start,
    const double                     Udeb,
    const double                     Ufin);
};
