#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <TopAbs_State.hpp>
#include <Standard_Boolean.hpp>

class IntTools_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_Root();

  Standard_EXPORT IntTools_Root(const double aRoot, const int aType);

  Standard_EXPORT void SetRoot(const double aRoot);

  Standard_EXPORT void SetType(const int aType);

  Standard_EXPORT void SetStateBefore(const TopAbs_State aState);

  Standard_EXPORT void SetStateAfter(const TopAbs_State aState);

  Standard_EXPORT void SetLayerHeight(const double aHeight);

  Standard_EXPORT void SetInterval(const double t1,
                                   const double t2,
                                   const double f1,
                                   const double f2);

  Standard_EXPORT double Root() const;

  Standard_EXPORT int Type() const;

  Standard_EXPORT TopAbs_State StateBefore() const;

  Standard_EXPORT TopAbs_State StateAfter() const;

  Standard_EXPORT double LayerHeight() const;

  Standard_EXPORT bool IsValid() const;

  Standard_EXPORT void Interval(double& t1, double& t2, double& f1, double& f2) const;

private:
  double       myRoot;
  int          myType;
  double       myLayerHeight;
  TopAbs_State myStateBefore;
  TopAbs_State myStateAfter;
  double       myt1;
  double       myt2;
  double       myf1;
  double       myf2;
};
