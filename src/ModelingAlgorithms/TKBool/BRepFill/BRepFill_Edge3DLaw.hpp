#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRepFill_LocationLaw.hpp>
class TopoDS_Wire;
class GeomFill_LocationLaw;

//! Build Location Law, with a Wire.
class BRepFill_Edge3DLaw : public BRepFill_LocationLaw
{

public:
  Standard_EXPORT BRepFill_Edge3DLaw(const TopoDS_Wire&                       Path,
                                     const occ::handle<GeomFill_LocationLaw>& Law);

  DEFINE_STANDARD_RTTIEXT(BRepFill_Edge3DLaw, BRepFill_LocationLaw)
};

