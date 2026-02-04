#pragma once


#include <Aspect_VKeyFlags.hpp>
#include <NCollection_Vec2.hpp>

//! Parameters for mouse scroll action.
struct Aspect_ScrollDelta
{

  NCollection_Vec2<int> Point; //!< scale position
  double                Delta; //!< delta in pixels
  Aspect_VKeyFlags      Flags; //!< key flags

  //! Return true if action has point defined.
  bool HasPoint() const { return Point.x() >= 0 && Point.y() >= 0; }

  //! Reset at point.
  void ResetPoint() { Point.SetValues(-1, -1); }

  //! Empty constructor.
  Aspect_ScrollDelta()
      : Point(-1, -1),
        Delta(0.0),
        Flags(Aspect_VKeyFlags_NONE)
  {
  }

  //! Constructor.
  Aspect_ScrollDelta(const NCollection_Vec2<int>& thePnt,
                     double                       theValue,
                     Aspect_VKeyFlags             theFlags = Aspect_VKeyFlags_NONE)
      : Point(thePnt),
        Delta(theValue),
        Flags(theFlags)
  {
  }

  //! Constructor with undefined point.
  Aspect_ScrollDelta(double theValue, Aspect_VKeyFlags theFlags = Aspect_VKeyFlags_NONE)
      : Point(-1, -1),
        Delta(theValue),
        Flags(theFlags)
  {
  }
};

