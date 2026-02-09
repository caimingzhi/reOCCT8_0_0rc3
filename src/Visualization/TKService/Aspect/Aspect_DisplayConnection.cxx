

#include <Aspect_DisplayConnection.hpp>

#include <Aspect_DisplayConnectionDefinitionError.hpp>
#include <OSD_Environment.hpp>

#if defined(HAVE_XLIB)
  #include <X11/Xlib.h>
  #include <X11/Xutil.h>
#endif

IMPLEMENT_STANDARD_RTTIEXT(Aspect_DisplayConnection, Standard_Transient)

Aspect_DisplayConnection::Aspect_DisplayConnection()
{
#if defined(HAVE_XLIB)
  myDisplay       = nullptr;
  myDefVisualInfo = nullptr;
  myDefFBConfig   = nullptr;
  myIsOwnDisplay  = false;
  OSD_Environment anEnv("DISPLAY");
  myDisplayName = anEnv.Value();
  Init(nullptr);
#endif
}

Aspect_DisplayConnection::~Aspect_DisplayConnection()
{
#if defined(HAVE_XLIB)
  if (myDefVisualInfo != nullptr)
  {
    XFree(myDefVisualInfo);
  }
  if (myDisplay != nullptr && myIsOwnDisplay)
  {
    XCloseDisplay((Display*)myDisplay);
  }
#endif
}

Aspect_DisplayConnection::Aspect_DisplayConnection(const TCollection_AsciiString& theDisplayName)
    : myDisplay(nullptr),
      myDefVisualInfo(nullptr),
      myDefFBConfig(nullptr),
      myIsOwnDisplay(false)
{
  myDisplayName = theDisplayName;
  Init(nullptr);
}

Aspect_DisplayConnection::Aspect_DisplayConnection(Aspect_XDisplay* theDisplay)
    : myDisplay(nullptr),
      myDefVisualInfo(nullptr),
      myDefFBConfig(nullptr),
      myIsOwnDisplay(false)
{
  Init(theDisplay);
}

void Aspect_DisplayConnection::SetDefaultVisualInfo(Aspect_XVisualInfo* theVisual,
                                                    Aspect_FBConfig     theFBConfig)
{
  if (myDefVisualInfo != nullptr)
  {
#if defined(HAVE_XLIB)
    XFree(myDefVisualInfo);
#endif
  }
  myDefVisualInfo = theVisual;
  myDefFBConfig   = theFBConfig;
}

void Aspect_DisplayConnection::Init(Aspect_XDisplay* theDisplay)
{
#if defined(HAVE_XLIB)
  if (myDisplay != nullptr && myIsOwnDisplay)
  {
    XCloseDisplay((Display*)myDisplay);
  }
  myIsOwnDisplay = false;
  myAtoms.Clear();

  myDisplay =
    theDisplay != nullptr ? theDisplay : (Aspect_XDisplay*)XOpenDisplay(myDisplayName.ToCString());
  if (myDisplay == nullptr)
  {
    TCollection_AsciiString aMessage;
    aMessage += "Can not connect to the server \"";
    aMessage += myDisplayName + "\"";
    throw Aspect_DisplayConnectionDefinitionError(aMessage.ToCString());
  }
  else
  {
    myIsOwnDisplay = theDisplay == nullptr;
    myAtoms.Bind(Aspect_XA_DELETE_WINDOW,
                 (uint64_t)XInternAtom((Display*)myDisplay, "WM_DELETE_WINDOW", False));
  }
#else
  myDisplay      = theDisplay;
  myIsOwnDisplay = theDisplay == nullptr;
#endif
}
