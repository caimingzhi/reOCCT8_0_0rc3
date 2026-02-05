#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <ShapeUpgrade_FaceDivide.hpp>
class TopoDS_Face;

//! Divides a Face with one or more seam edge to avoid closed faces.
//! Splitting is performed by U and V direction. The number of
//! resulting faces can be defined by user.
class ShapeUpgrade_ClosedFaceDivide : public ShapeUpgrade_FaceDivide
{

public:
  //! Creates empty constructor.
  Standard_EXPORT ShapeUpgrade_ClosedFaceDivide();

  //! Initialize by a Face.
  Standard_EXPORT ShapeUpgrade_ClosedFaceDivide(const TopoDS_Face& F);

  //! Performs splitting of surface and computes the shell
  //! from source face.
  Standard_EXPORT bool SplitSurface(const double theArea = 0.) override;

  //! Sets the number of cutting lines by which closed face will be split.
  //! The resulting faces will be num+1.
  Standard_EXPORT void SetNbSplitPoints(const int num);

  //! Returns the number of splitting points
  Standard_EXPORT int GetNbSplitPoints() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_ClosedFaceDivide, ShapeUpgrade_FaceDivide)

private:
  int myNbSplit;
};
