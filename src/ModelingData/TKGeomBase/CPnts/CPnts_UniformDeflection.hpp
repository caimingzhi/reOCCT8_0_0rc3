#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
class Adaptor3d_Curve;
class Adaptor2d_Curve2d;

class CPnts_UniformDeflection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT CPnts_UniformDeflection();

  Standard_EXPORT CPnts_UniformDeflection(const Adaptor3d_Curve& C,
                                          const double           Deflection,
                                          const double           Resolution,
                                          const bool             WithControl);

  Standard_EXPORT CPnts_UniformDeflection(const Adaptor2d_Curve2d& C,
                                          const double             Deflection,
                                          const double             Resolution,
                                          const bool               WithControl);

  Standard_EXPORT CPnts_UniformDeflection(const Adaptor3d_Curve& C,
                                          const double           Deflection,
                                          const double           U1,
                                          const double           U2,
                                          const double           Resolution,
                                          const bool             WithControl);

  Standard_EXPORT CPnts_UniformDeflection(const Adaptor2d_Curve2d& C,
                                          const double             Deflection,
                                          const double             U1,
                                          const double             U2,
                                          const double             Resolution,
                                          const bool               WithControl);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& C,
                                  const double           Deflection,
                                  const double           Resolution,
                                  const bool             WithControl);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& C,
                                  const double             Deflection,
                                  const double             Resolution,
                                  const bool               WithControl);

  Standard_EXPORT void Initialize(const Adaptor3d_Curve& C,
                                  const double           Deflection,
                                  const double           U1,
                                  const double           U2,
                                  const double           Resolution,
                                  const bool             WithControl);

  Standard_EXPORT void Initialize(const Adaptor2d_Curve2d& C,
                                  const double             Deflection,
                                  const double             U1,
                                  const double             U2,
                                  const double             Resolution,
                                  const bool               WithControl);

  bool IsAllDone() const;

  void Next();

  Standard_EXPORT bool More();

  double Value() const;

  gp_Pnt Point() const;

private:
  Standard_EXPORT void Perform();

  bool   myDone;
  bool   my3d;
  void*  myCurve;
  bool   myFinish;
  double myTolCur;
  bool   myControl;
  int    myIPoint;
  int    myNbPoints;
  double myParams[3];
  gp_Pnt myPoints[3];
  double myDwmax;
  double myDeflection;
  double myFirstParam;
  double myLastParam;
  double myDu;
};

#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>

inline bool CPnts_UniformDeflection::IsAllDone() const
{
  return myDone;
}

inline void CPnts_UniformDeflection::Next()
{
  Standard_OutOfRange_Raise_if(myIPoint >= myNbPoints,
                               "CPnts_UniformDeflection::Next() - no more points available");
  myIPoint++;
}

inline double CPnts_UniformDeflection::Value() const
{
  StdFail_NotDone_Raise_if(!myDone, "CPnts_UniformDeflection::Value() - no result");
  return myParams[myIPoint + 1];
}

inline gp_Pnt CPnts_UniformDeflection::Point() const
{
  StdFail_NotDone_Raise_if(!myDone, "CPnts_UniformDeflection::Point() - no result");
  return myPoints[myIPoint + 1];
}
