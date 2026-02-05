#pragma once

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

class gp_Pnt;

//! Interface class providing API for edge tessellation tools.
class IMeshTools_CurveTessellator : public Standard_Transient
{
public:
  //! Destructor.
  ~IMeshTools_CurveTessellator() override = default;

  //! Returns number of tessellation points.
  Standard_EXPORT virtual int PointsNb() const = 0;

  //! Returns parameters of solution with the given index.
  //! @param theIndex index of tessellation point.
  //! @param thePoint tessellation point.
  //! @param theParameter parameters on PCurve corresponded to the solution.
  //! @return True in case of valid result, false elewhere.
  Standard_EXPORT virtual bool Value(const int theIndex,
                                     gp_Pnt&   thePoint,
                                     double&   theParameter) const = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshTools_CurveTessellator, Standard_Transient)

protected:
  //! Constructor.
  IMeshTools_CurveTessellator() {}
};
