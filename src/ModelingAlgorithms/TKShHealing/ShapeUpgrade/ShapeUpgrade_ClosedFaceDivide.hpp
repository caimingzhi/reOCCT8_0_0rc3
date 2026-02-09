#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <ShapeUpgrade_FaceDivide.hpp>
class TopoDS_Face;

class ShapeUpgrade_ClosedFaceDivide : public ShapeUpgrade_FaceDivide
{

public:
  Standard_EXPORT ShapeUpgrade_ClosedFaceDivide();

  Standard_EXPORT ShapeUpgrade_ClosedFaceDivide(const TopoDS_Face& F);

  Standard_EXPORT bool SplitSurface(const double theArea = 0.) override;

  Standard_EXPORT void SetNbSplitPoints(const int num);

  Standard_EXPORT int GetNbSplitPoints() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_ClosedFaceDivide, ShapeUpgrade_FaceDivide)

private:
  int myNbSplit;
};
