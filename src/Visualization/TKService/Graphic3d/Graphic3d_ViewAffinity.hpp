#pragma once


#include <Standard.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

//! Structure display state.
class Graphic3d_ViewAffinity : public Standard_Transient
{
public:
  //! Empty constructor.
  Graphic3d_ViewAffinity() { SetVisible(true); }

  //! Return visibility flag.
  bool IsVisible(const int theViewId) const
  {
    const unsigned int aBit = 1 << theViewId;
    return (myMask & aBit) != 0;
  }

  //! Setup visibility flag for all views.
  void SetVisible(const bool theIsVisible)
  {
    ::memset(&myMask, theIsVisible ? 0xFF : 0x00, sizeof(myMask));
  }

  //! Setup visibility flag.
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

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

private:
  unsigned int myMask; //!< affinity mask

public:
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ViewAffinity, Standard_Transient)
};

