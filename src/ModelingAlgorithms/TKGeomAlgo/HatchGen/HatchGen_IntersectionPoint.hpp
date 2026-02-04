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

  //! Sets the index of the supporting curve.
  Standard_EXPORT void SetIndex(const int Index);

  //! Returns the index of the supporting curve.
  Standard_EXPORT int Index() const;

  //! Sets the parameter on the curve.
  Standard_EXPORT void SetParameter(const double Parameter);

  //! Returns the parameter on the curve.
  Standard_EXPORT double Parameter() const;

  //! Sets the position of the point on the curve.
  Standard_EXPORT void SetPosition(const TopAbs_Orientation Position);

  //! Returns the position of the point on the curve.
  Standard_EXPORT TopAbs_Orientation Position() const;

  //! Sets the transition state before the intersection.
  Standard_EXPORT void SetStateBefore(const TopAbs_State State);

  //! Returns the transition state before the intersection.
  Standard_EXPORT TopAbs_State StateBefore() const;

  //! Sets the transition state after the intersection.
  Standard_EXPORT void SetStateAfter(const TopAbs_State State);

  //! Returns the transition state after of the intersection.
  Standard_EXPORT TopAbs_State StateAfter() const;

  //! Sets the flag that the point is the beginning of a segment.
  Standard_EXPORT void SetSegmentBeginning(const bool State = true);

  //! Returns the flag that the point is the beginning of a segment.
  Standard_EXPORT bool SegmentBeginning() const;

  //! Sets the flag that the point is the end of a segment.
  Standard_EXPORT void SetSegmentEnd(const bool State = true);

  //! Returns the flag that the point is the end of a segment.
  Standard_EXPORT bool SegmentEnd() const;

  //! Dump of the point on element.
  Standard_EXPORT virtual void Dump(const int Index = 0) const = 0;

protected:
  //! Creates an empty intersection point.
  Standard_EXPORT HatchGen_IntersectionPoint();

  //! Destructor is protected for safer inheritance
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

