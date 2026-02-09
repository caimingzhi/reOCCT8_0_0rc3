#pragma once

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

class gp_Pnt;

class IMeshTools_CurveTessellator : public Standard_Transient
{
public:
  ~IMeshTools_CurveTessellator() override = default;

  Standard_EXPORT virtual int PointsNb() const = 0;

  Standard_EXPORT virtual bool Value(const int theIndex,
                                     gp_Pnt&   thePoint,
                                     double&   theParameter) const = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshTools_CurveTessellator, Standard_Transient)

protected:
  IMeshTools_CurveTessellator() {}
};
