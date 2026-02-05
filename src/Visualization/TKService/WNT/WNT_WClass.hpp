#pragma once

#include <Standard.hpp>

#if defined(_WIN32) && !defined(OCCT_UWP)

  #include <Aspect_Handle.hpp>
  #include <Standard_Integer.hpp>
  #include <Standard_Transient.hpp>
  #include <NCollection_DefineAlloc.hpp>
  #include <TCollection_AsciiString.hpp>

//! This class defines a Windows NT window class.
//! A window in Windows NT is always created based on a
//! window class. The window class identifies the window
//! procedure that processes messages to the window. Each
//! window class has unique name ( character string ). More
//! than one window can be created based on a single window
//! class. For example, all button windows in Windows NT
//! are created based on the same window class. The window
//! class defines the window procedure and some other
//! characteristics ( background, mouse cursor shape etc. )
//! of the windows that are created based on that class.
//! When we create a window, we define additional
//! characteristics of the window that are unique to that
//! window. So, we have to create and register window
//! class before creation of any window. Of course, it's possible
//! to create a new window class for each window inside
//! the Window class and do not use the WClass at all.
//! We implemented this class for sake of flexibility of
//! event processing.
class WNT_WClass : public Standard_Transient
{
  friend class WNT_Window;
  DEFINE_STANDARD_RTTIEXT(WNT_WClass, Standard_Transient)
public:
  //! Creates a Windows NT window class and registers it.
  Standard_EXPORT WNT_WClass(
    const TCollection_AsciiString& theClassName,
    void* const                    theWndProc,
    const unsigned int             theStyle,
    const int                      theClassExtra  = 0,
    const int                      theWindowExtra = 0,
    const Aspect_Handle            theCursor      = NULL,
    const Aspect_Handle            theIcon        = NULL,
    const TCollection_AsciiString& theMenuName    = TCollection_AsciiString::EmptyString());

  //! Destroys all resources attached to the class
  Standard_EXPORT ~WNT_WClass();

  //! Returns address of window procedure.
  void* WndProc() const { return myWndProc; }

  //! Returns a class name.
  const TCollection_AsciiString& Name() const { return myClassName; }

  //! Returns a program instance handle.
  Aspect_Handle Instance() const { return myAppInstance; }

protected:
  TCollection_AsciiString myClassName;
  Aspect_Handle           myAppInstance;
  void*                   myWndProc;
};

#endif // _WIN32
