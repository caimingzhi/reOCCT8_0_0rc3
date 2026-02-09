#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepGProp_Face.hpp>
#include <BRepGProp_UFunction.hpp>
#include <GProp_ValueType.hpp>
#include <Standard_Boolean.hpp>
#include <math_Function.hpp>
class gp_Pnt;

class BRepGProp_TFunction : public math_Function
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepGProp_TFunction(const BRepGProp_Face& theSurface,
                                      const gp_Pnt&         theVertex,
                                      const bool            IsByPoint,
                                      const double*         theCoeffs,
                                      const double          theUMin,
                                      const double          theTolerance);

  Standard_EXPORT void Init();

  void SetNbKronrodPoints(const int theNbPoints);

  void SetValueType(const GProp_ValueType aType);

  void SetTolerance(const double aTol);

  double ErrorReached() const;

  double AbsolutError() const;

  Standard_EXPORT bool Value(const double X, double& F) override;

  Standard_EXPORT int GetStateNumber() override;

private:
  BRepGProp_Face      mySurface;
  BRepGProp_UFunction myUFunction;
  double              myUMin;
  double              myTolerance;
  double              myTolReached;
  double              myErrReached;
  double              myAbsError;
  GProp_ValueType     myValueType;
  bool                myIsByPoint;
  int                 myNbPntOuter;
};

inline void BRepGProp_TFunction::SetNbKronrodPoints(const int theNbPoints)
{
  myNbPntOuter = (theNbPoints % 2 == 0) ? theNbPoints + 1 : theNbPoints;
}

inline void BRepGProp_TFunction::SetValueType(const GProp_ValueType theType)
{
  myValueType = theType;
  myUFunction.SetValueType(myValueType);
}

inline void BRepGProp_TFunction::SetTolerance(const double theTolerance)
{
  myTolerance = theTolerance;
}

inline double BRepGProp_TFunction::ErrorReached() const
{
  return myErrReached;
}

inline double BRepGProp_TFunction::AbsolutError() const
{
  return myAbsError;
}
