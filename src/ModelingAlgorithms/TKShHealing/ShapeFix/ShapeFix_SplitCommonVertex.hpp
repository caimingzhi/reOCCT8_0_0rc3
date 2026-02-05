#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <ShapeFix_Root.hpp>

//! Two wires have common vertex - this case is valid in BRep model
//! and isn't valid in STEP => before writing into STEP it is necessary
//! to split this vertex (each wire must has one vertex)
class ShapeFix_SplitCommonVertex : public ShapeFix_Root
{

public:
  Standard_EXPORT ShapeFix_SplitCommonVertex();

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT void Perform();

  Standard_EXPORT TopoDS_Shape Shape();

  DEFINE_STANDARD_RTTIEXT(ShapeFix_SplitCommonVertex, ShapeFix_Root)

private:
  TopoDS_Shape myShape;
  TopoDS_Shape myResult;
  int          myStatus;
};
