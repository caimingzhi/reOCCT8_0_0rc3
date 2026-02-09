#pragma once

#include <Bnd_Range.hpp>
#include <Standard_TypeDef.hpp>
#include <Standard_OStream.hpp>
#include <Standard_Dump.hpp>

#include <vector>

class gp_Ax1;
class Graphic3d_SequenceOfHClipPlane;

class SelectMgr_ViewClipRange
{
public:
  SelectMgr_ViewClipRange() { SetVoid(); }

  bool IsClipped(const double theDepth) const
  {
    if (myUnclipRange.IsOut(theDepth))
    {
      return true;
    }
    for (size_t aRangeIter = 0; aRangeIter < myClipRanges.size(); ++aRangeIter)
    {
      if (!myClipRanges[aRangeIter].IsOut(theDepth))
      {
        return true;
      }
    }
    return false;
  }

  bool GetNearestDepth(const Bnd_Range& theRange, double& theDepth) const
  {
    if (!myUnclipRange.IsVoid() && myUnclipRange.IsOut(theRange))
    {
      return false;
    }

    Bnd_Range aCommonClipRange;
    theRange.GetMin(theDepth);

    if (!myUnclipRange.IsVoid() && myUnclipRange.IsOut(theDepth))
    {
      myUnclipRange.GetMin(theDepth);
    }

    for (size_t aRangeIter = 0; aRangeIter < myClipRanges.size(); ++aRangeIter)
    {
      if (!myClipRanges[aRangeIter].IsOut(theDepth))
      {
        aCommonClipRange = myClipRanges[aRangeIter];
        break;
      }
    }

    if (aCommonClipRange.IsVoid())
    {
      return true;
    }

    for (size_t aRangeIter = 0; aRangeIter < myClipRanges.size(); ++aRangeIter)
    {
      if (!aCommonClipRange.IsOut(myClipRanges[aRangeIter]))
      {
        aCommonClipRange.Add(myClipRanges[aRangeIter]);
      }
    }

    aCommonClipRange.GetMax(theDepth);

    return !theRange.IsOut(theDepth);
  }

public:
  void SetVoid()
  {
    myClipRanges.resize(0);
    myUnclipRange = Bnd_Range(RealFirst(), RealLast());
  }

  Standard_EXPORT void AddClippingPlanes(const Graphic3d_SequenceOfHClipPlane& thePlanes,
                                         const gp_Ax1&                         thePickRay);

  Bnd_Range& ChangeUnclipRange() { return myUnclipRange; }

  void AddClipSubRange(const Bnd_Range& theRange) { myClipRanges.push_back(theRange); }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  std::vector<Bnd_Range> myClipRanges;
  Bnd_Range              myUnclipRange;
};
