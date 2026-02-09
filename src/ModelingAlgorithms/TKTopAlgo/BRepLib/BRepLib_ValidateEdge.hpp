#pragma once

#include <Standard_TypeDef.hpp>
#include <Standard_Handle.hpp>

class Adaptor3d_Curve;
class Adaptor3d_CurveOnSurface;

class BRepLib_ValidateEdge
{
public:
  Standard_EXPORT BRepLib_ValidateEdge(const occ::handle<Adaptor3d_Curve> theReferenceCurve,
                                       const occ::handle<Adaptor3d_CurveOnSurface> theOtherCurve,
                                       bool theSameParameter);

  void SetExactMethod(bool theIsExact) { myIsExactMethod = theIsExact; }

  bool IsExactMethod() { return myIsExactMethod; }

  void SetParallel(bool theIsMultiThread) { myIsMultiThread = theIsMultiThread; }

  bool IsParallel() { return myIsMultiThread; }

  void SetControlPointsNumber(int theControlPointsNumber)
  {
    myControlPointsNumber = theControlPointsNumber;
  }

  void SetExitIfToleranceExceeded(double theToleranceForChecking);

  Standard_EXPORT void Process();

  bool IsDone() const { return myIsDone; }

  Standard_EXPORT bool CheckTolerance(double theToleranceToCheck);

  Standard_EXPORT double GetMaxDistance();

  Standard_EXPORT void UpdateTolerance(double& theToleranceToUpdate);

private:
  double correctTolerance(double theTolerance);

  void processApprox();

  void processExact();

private:
  occ::handle<Adaptor3d_Curve>          myReferenceCurve;
  occ::handle<Adaptor3d_CurveOnSurface> myOtherCurve;
  bool                                  mySameParameter;
  int                                   myControlPointsNumber;
  double                                myToleranceForChecking;
  double                                myCalculatedDistance;
  bool                                  myExitIfToleranceExceeded;
  bool                                  myIsDone;
  bool                                  myIsExactMethod;
  bool                                  myIsMultiThread;
};
