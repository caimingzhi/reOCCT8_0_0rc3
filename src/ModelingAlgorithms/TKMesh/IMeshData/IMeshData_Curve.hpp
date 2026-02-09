#pragma once

#include <IMeshData_ParametersList.hpp>
#include <Standard_Type.hpp>

class gp_Pnt;

class IMeshData_Curve : public IMeshData_ParametersList
{
public:
  ~IMeshData_Curve() override = default;

  Standard_EXPORT virtual void InsertPoint(const int     thePosition,
                                           const gp_Pnt& thePoint,
                                           const double  theParamOnPCurve) = 0;

  Standard_EXPORT virtual void AddPoint(const gp_Pnt& thePoint, const double theParamOnCurve) = 0;

  Standard_EXPORT virtual gp_Pnt& GetPoint(const int theIndex) = 0;

  Standard_EXPORT virtual void RemovePoint(const int theIndex) = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshData_Curve, IMeshData_ParametersList)

protected:
  IMeshData_Curve() {}
};
