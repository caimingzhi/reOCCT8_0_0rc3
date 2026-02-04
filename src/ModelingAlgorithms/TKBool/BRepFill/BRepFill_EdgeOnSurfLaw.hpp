#pragma once


#include <Standard.hpp>

#include <BRepFill_LocationLaw.hpp>
class TopoDS_Wire;
class TopoDS_Shape;

//! Build Location Law, with a Wire and a Surface.
class BRepFill_EdgeOnSurfLaw : public BRepFill_LocationLaw
{

public:
  Standard_EXPORT BRepFill_EdgeOnSurfLaw(const TopoDS_Wire& Path, const TopoDS_Shape& Surf);

  //! returns <False> if one Edge of <Path> do not have
  //! representation on <Surf>. In this case it is
  //! impossible to use this object.
  Standard_EXPORT bool HasResult() const;

  DEFINE_STANDARD_RTTIEXT(BRepFill_EdgeOnSurfLaw, BRepFill_LocationLaw)

private:
  bool hasresult;
};

