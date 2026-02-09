#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>
#include <Standard_Boolean.hpp>

class HatchGen_IntersectionPoint
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT void SetIndex(const int Index);

  Standard_EXPORT int Index() const;

  Standard_EXPORT void SetParameter(const double Parameter);

  Standard_EXPORT double Parameter() const;

  Standard_EXPORT void SetPosition(const TopAbs_Orientation Position);

  Standard_EXPORT TopAbs_Orientation Position() const;

  Standard_EXPORT void SetStateBefore(const TopAbs_State State);

  Standard_EXPORT TopAbs_State StateBefore() const;

  Standard_EXPORT void SetStateAfter(const TopAbs_State State);

  Standard_EXPORT TopAbs_State StateAfter() const;

  Standard_EXPORT void SetSegmentBeginning(const bool State = true);

  Standard_EXPORT bool SegmentBeginning() const;

  Standard_EXPORT void SetSegmentEnd(const bool State = true);

  Standard_EXPORT bool SegmentEnd() const;

  Standard_EXPORT virtual void Dump(const int Index = 0) const = 0;

protected:
  Standard_EXPORT HatchGen_IntersectionPoint();

  ~HatchGen_IntersectionPoint() = default;

protected:
  int                myIndex;
  double             myParam;
  TopAbs_Orientation myPosit;
  TopAbs_State       myBefore;
  TopAbs_State       myAfter;
  bool               mySegBeg;
  bool               mySegEnd;
};
