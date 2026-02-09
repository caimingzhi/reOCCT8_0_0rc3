#pragma once

#include <Standard.hpp>

#if defined(_WIN32) && !defined(OCCT_UWP)

  #include <Aspect_Handle.hpp>
  #include <Standard_Integer.hpp>
  #include <Standard_Transient.hpp>
  #include <NCollection_DefineAlloc.hpp>
  #include <TCollection_AsciiString.hpp>

class WNT_WClass : public Standard_Transient
{
  friend class WNT_Window;
  DEFINE_STANDARD_RTTIEXT(WNT_WClass, Standard_Transient)
public:
  Standard_EXPORT WNT_WClass(
    const TCollection_AsciiString& theClassName,
    void* const                    theWndProc,
    const unsigned int             theStyle,
    const int                      theClassExtra  = 0,
    const int                      theWindowExtra = 0,
    const Aspect_Handle            theCursor      = NULL,
    const Aspect_Handle            theIcon        = NULL,
    const TCollection_AsciiString& theMenuName    = TCollection_AsciiString::EmptyString());

  Standard_EXPORT ~WNT_WClass();

  void* WndProc() const { return myWndProc; }

  const TCollection_AsciiString& Name() const { return myClassName; }

  Aspect_Handle Instance() const { return myAppInstance; }

protected:
  TCollection_AsciiString myClassName;
  Aspect_Handle           myAppInstance;
  void*                   myWndProc;
};

#endif
