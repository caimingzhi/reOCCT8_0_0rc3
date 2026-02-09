#pragma once

#include <Standard.hpp>

#include <BRepFill_LocationLaw.hpp>
class TopoDS_Wire;
class TopoDS_Shape;

class BRepFill_EdgeOnSurfLaw : public BRepFill_LocationLaw
{

public:
  Standard_EXPORT BRepFill_EdgeOnSurfLaw(const TopoDS_Wire& Path, const TopoDS_Shape& Surf);

  Standard_EXPORT bool HasResult() const;

  DEFINE_STANDARD_RTTIEXT(BRepFill_EdgeOnSurfLaw, BRepFill_LocationLaw)

private:
  bool hasresult;
};
