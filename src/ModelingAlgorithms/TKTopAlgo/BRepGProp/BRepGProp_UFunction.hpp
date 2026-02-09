#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepGProp_Face.hpp>
#include <gp_Pnt.hpp>
#include <GProp_ValueType.hpp>
#include <Standard_Boolean.hpp>
#include <math_Function.hpp>
class gp_XYZ;

class BRepGProp_UFunction : public math_Function
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepGProp_UFunction(const BRepGProp_Face& theSurface,
                                      const gp_Pnt&         theVertex,
                                      const bool            IsByPoint,
                                      const double*         theCoeffs);

  void SetValueType(const GProp_ValueType theType);

  void SetVParam(const double theVParam);

  Standard_EXPORT bool Value(const double X, double& F) override;

private:
  Standard_EXPORT double VolumeValue(const double X, gp_XYZ& thePMP0, double& theS, double& theD1);

  Standard_EXPORT bool CenterMassValue(const double X, double& F);

  Standard_EXPORT bool InertiaValue(const double X, double& F);

  BRepGProp_Face  mySurface;
  gp_Pnt          myVertex;
  const double*   myCoeffs;
  double          myVParam;
  GProp_ValueType myValueType;
  bool            myIsByPoint;
};

inline void BRepGProp_UFunction::SetValueType(const GProp_ValueType theType)
{
  myValueType = theType;
}

inline void BRepGProp_UFunction::SetVParam(const double theVParam)
{
  myVParam = theVParam;
}
