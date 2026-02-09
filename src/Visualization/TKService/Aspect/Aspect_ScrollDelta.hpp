#pragma once

#include <Aspect_VKeyFlags.hpp>
#include <NCollection_Vec2.hpp>

struct Aspect_ScrollDelta
{

  NCollection_Vec2<int> Point;
  double                Delta;
  Aspect_VKeyFlags      Flags;

  bool HasPoint() const { return Point.x() >= 0 && Point.y() >= 0; }

  void ResetPoint() { Point.SetValues(-1, -1); }

  Aspect_ScrollDelta()
      : Point(-1, -1),
        Delta(0.0),
        Flags(Aspect_VKeyFlags_NONE)
  {
  }

  Aspect_ScrollDelta(const NCollection_Vec2<int>& thePnt,
                     double                       theValue,
                     Aspect_VKeyFlags             theFlags = Aspect_VKeyFlags_NONE)
      : Point(thePnt),
        Delta(theValue),
        Flags(theFlags)
  {
  }

  Aspect_ScrollDelta(double theValue, Aspect_VKeyFlags theFlags = Aspect_VKeyFlags_NONE)
      : Point(-1, -1),
        Delta(theValue),
        Flags(theFlags)
  {
  }
};
