#pragma once

#include <Standard.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

class Graphic3d_ViewAffinity : public Standard_Transient
{
public:
  Graphic3d_ViewAffinity() { SetVisible(true); }

  bool IsVisible(const int theViewId) const
  {
    const unsigned int aBit = 1 << theViewId;
    return (myMask & aBit) != 0;
  }

  void SetVisible(const bool theIsVisible)
  {
    ::memset(&myMask, theIsVisible ? 0xFF : 0x00, sizeof(myMask));
  }

  void SetVisible(const int theViewId, const bool theIsVisible)
  {
    const unsigned int aBit = 1 << theViewId;
    if (theIsVisible)
    {
      myMask |= aBit;
    }
    else
    {
      myMask &= ~aBit;
    }
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  unsigned int myMask;

public:
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ViewAffinity, Standard_Transient)
};
